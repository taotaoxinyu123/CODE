#include "boost/format.hpp"
#include <string>
#include "cocc_publish_common.h"
#include "cocc_publish_impl.h"
#include "cocc_publish_data.h"
#include "cocc_pb2cpp.h"
static void Log(const std::string& message)
{
    pubdata::singleton_coccpublish_impl::get_mutable_instance().logger().Log(message);
}
namespace pjson {
    bool GetJsonInt(rapidjson::Document& document, const std::string& name, int& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        val = iter->value.GetInt();
        return true;
    }
    bool GetJsonString(rapidjson::Document& document, const std::string& name, std::string& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        val = iter->value.GetString();
        return true;
    }
} // namespace pjson

namespace pclient
{
    void TrainBlockInfo(int& type, std::vector<char>& data)
    {
        std::string msg = boost::str(boost::format("��������������Ϣ:�г�������ϢTrainBlockInfo,msg_id[%s],data_size[%s]")
            % type
            % data.size());
        Log(msg);
        do
        {
            {
            }
            // ����protobuf������
            pbproto::post_train_block_info pb;
            pb.ParsePartialFromArray(&data.at(0), data.size());
            pubdata::post_train_block_info cpp;
            PB2CPPTrianBlockInfo(pb, cpp);
            // ҵ����
            pbus::BusTrainBlockInfo(cpp);
        } while (false);
    }
    void CbtcTrainIndicationInit(int& type, std::vector<char>& data)
    {

        std::string msg = boost::str(boost::format("��������������Ϣ:�г���Ϣȫ����ϢCbtcTrainIndicationInit,msg_id[%s],data_size[%s]")
            % type
            % data.size());
        Log(msg);
        do
        {
            // ����protobuf������
            pbproto::post_cbtc_train_indication_init pb;
            pb.ParsePartialFromArray(&data.at(0), data.size());
            pubdata::post_cbtc_train_indication_init cpp;
            PB2CPPTrianIndicationInit(pb, cpp);
            // ҵ����
            pbus::BusCbtcTrainIndicationInit(cpp);
        } while (false);
    }

}

namespace pbus {
    void BusTrainBlockInfo(pubdata::post_train_block_info& trian_block_info)
    {
        pubdata::CoccPublishImpl& pi = pubdata::singleton_coccpublish_impl::get_mutable_instance();
        std::map<std::string, int> trip_id_lst;
        pi.get_trip_id_lst_imp(trip_id_lst);
        for (auto it_train : trian_block_info.data.train) 
        {
            bool is_exit = false;
            std::string train_id = it_train.train_id;
            for (auto it_id : trip_id_lst)
            {
                if (train_id == it_id.first)
                {
                    is_exit = true;
                    break;
                }
            }
            if (is_exit) 
            {
                pi.update_discern_imp(train_id, true); // �����ݸ��£�����������ЧΪtrue
                pi.update_block_flag_imp(train_id, it_train.block_flag);
            }
            else 
            {
                Log("�г�������Ϣtrain_id�������������ݱ��У�" + train_id);
            }
        }
    }
    void BusCbtcTrainIndicationInit(pubdata::post_cbtc_train_indication_init& train_indication_init) 
    {
        pubdata::CoccPublishImpl& pi = pubdata::singleton_coccpublish_impl::get_mutable_instance();
        std::map<std::string, int> trip_id_lst;
        pi.get_trip_id_lst_imp(trip_id_lst);
        for (auto it_train : train_indication_init.data.train)
        {
            bool is_exit = false;
            std::string train_id = it_train.train_id;
            for (auto it_id : trip_id_lst)
            {
                if (train_id == it_id.first)
                {
                    is_exit = true;
                    break;
                }
            }
            if (is_exit)
            {
                pi.update_discern_imp(train_id, true);
                pi.update_line_id_imp(train_id, train_indication_init.data.line_id);
                pi.update_section_id_of_head_imp(train_id, it_train.section_id_of_head);
                pi.update_section_id_of_tail_imp(train_id, it_train.section_id_of_tail);
            }
            else
            {
                Log("�г�ȫ����Ϣtrain_id�������������ݱ��У�" + train_id);
            }
        }
    }
}