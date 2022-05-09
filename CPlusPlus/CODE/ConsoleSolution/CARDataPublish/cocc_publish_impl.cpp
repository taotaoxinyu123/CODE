#include "cocc_publish_impl.h"
#include "cocc_config_manager.hpp"
#include "cocc_publish_client.h"
#include "cocc_publish_write.h"
#include "cocc_load_databse.hpp"

static void Log(const std::string& message)
{
	pubdata::singleton_coccpublish_impl::get_mutable_instance().logger().Log(message);
}
namespace pubdata {
	CoccPublishImpl::CoccPublishImpl() : logger_("CARDataPublish")
	{

	}
	CoccPublishImpl::~CoccPublishImpl()
	{

	}
	int CoccPublishImpl::start()
	{
		Log("CARDataPublish START");
		int error_code = 0;
		// 加载配置:读取xml，然后写入config内存
		pconfig::Config config;
		std::string message = pconfig::Load(config);
		if (!message.empty())
		{
			error_code = -1;
			logger_.Log(message);
			return error_code;
		}
		config_container_.set(config);
		// 加载数据库配置
		pdatabase::load_static_data();
		// 初始化数据
		init_iplat_data();
		// 启动监听的线程
		start_publish();
		// 启动写入iplat的线程
		start_publish_write();
		return error_code;
	}
	void CoccPublishImpl::init_iplat_data()
	{
		std::map<std::string, int> trip_id_lst;
		publish_container_.get_trip_id_lst(trip_id_lst);
		for (auto it : trip_id_lst) 
		{
			PublishIplat init_pub_data;
			init_pub_data.discern = false;
			init_pub_data.train_id = it.second; // 只能初始化写train_id
			init_pub_data.line_id = 0;
			init_pub_data.section_id_of_head = 0;
			init_pub_data.section_id_of_tail = 0;
			init_pub_data.bolck_flag = 0;
		}
	}
	// 配置数据API
	pconfig::Config CoccPublishImpl::config()
	{
		return config_container_.get();
	}
	//  to iplat
	void CoccPublishImpl::init_pb_data_imp(const std::string key, const PublishIplat pub_data)
	{
		publish_container_.init_pb_data(key, pub_data);
	}
	void CoccPublishImpl::update_discern_imp(const std::string key, const int value)
	{
		publish_container_.update_discern(key, value);
	}
	void CoccPublishImpl::update_block_flag_imp(const std::string key, const int value)
	{
		publish_container_.update_block_flag(key, value);
	}
	void CoccPublishImpl::update_line_id_imp(const std::string key, const int value)
	{
		publish_container_.update_line_id(key, value);
	}
	void CoccPublishImpl::update_section_id_of_head_imp(const std::string key, const int value)
	{
		publish_container_.update_section_id_of_head(key, value);
	}
	void CoccPublishImpl::update_section_id_of_tail_imp(const std::string key, const int value)
	{
		publish_container_.update_section_id_of_tail(key, value);
	}
	void CoccPublishImpl::get_pub_iplat_imp(std::map<std::string, PublishIplat>& pub_iplat)
	{
		publish_container_.get_pub_iplat(pub_iplat);
	}
	void CoccPublishImpl::get_trip_id_lst_imp(std::map<std::string, int>& trip_id_lst)
	{
		publish_container_.get_trip_id_lst(trip_id_lst);
	}
	void CoccPublishImpl::set_trip_id_lst_imp(std::map<std::string, int> trip_id_lst)
	{
		publish_container_.set_trip_id_lst(trip_id_lst);
	}
	void CoccPublishImpl::get_pub_iplat_switch_imp(bool& pub_iplat_switch)
	{
		publish_container_.get_pub_iplat_switch(pub_iplat_switch);
	}
	void CoccPublishImpl::set_pub_iplat_switch_imp(const bool pub_iplat_switch)
	{
		publish_container_.set_pub_iplat_switch(pub_iplat_switch);
	}

} // namespace