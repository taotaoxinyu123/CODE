#include "boost/format.hpp"
#include <string>
#include <boost/lexical_cast.hpp>
#include "cocc_his_impl.h"
#include "cocc_common.h"
#include "cocc_common_json.h"
#include "cocc_his_data.h"
#include "cocc_frame.hpp"

static void Log(const std::string& message)
{
	hdata::singleton_cocchis_impl::get_mutable_instance().logger().Log(message);
}
namespace hcommon
{
    void String2FlatBuffer(const std::string& str, boost::beast::flat_buffer& buf)
    {
        if (!str.empty())
        {
            std::size_t size = str.size();
            // ���ݷ���flat_buffer
            buf.max_size(size);
            auto b = buf.prepare(size);
            char* const p = static_cast<char* const>(b.data());
            memcpy(p, str.c_str(), size);
            buf.commit(size);  // #End
        }
    }
    std::string SimpleTime()
    {
        // �˴�ʱ�侫�ȣ��뼶
        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

        struct tm pt_tm = boost::posix_time::to_tm(now);
        int milliseconds = now.time_of_day().total_milliseconds() % 1000;
        std::string str_now = boost::str(boost::format("%04d%02d%02d%02d%02d%02d")
            % (1900 + pt_tm.tm_year)
            % (1 + pt_tm.tm_mon)
            % pt_tm.tm_mday
            % pt_tm.tm_hour
            % pt_tm.tm_min
            % pt_tm.tm_sec);
        // YYYYMMDDHHmmSS
        return str_now;
    }
}

namespace hclient {
    void TickTock(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::TickTock tick_tock;
            int msg_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", tick_tock.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", tick_tock.version)) break;
            if (!hcommon::GetJsonString(document_read, "content", tick_tock.content)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:������ϢTickTock,time[%s],msg_id[%d],version[%s],content[%s]")
                    % tick_tock.time
                    % msg_id_i
                    % tick_tock.version
                    % tick_tock.content);
                Log(msg);
            }
        } while (false);
    }
    void ReportBegin(rapidjson::Document& document_read) 
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportBegin recevie_report_begin;
            int msg_id_i = -1, report_type_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", recevie_report_begin.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", recevie_report_begin.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", recevie_report_begin.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", recevie_report_begin.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "report_type", report_type_i)) break;
            if (!hcommon::GetJsonString(document_read, "crc", recevie_report_begin.crc)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:��Ϣ���Ϳ�ʼReportBegin,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],report_type[%d],crc[%s]")
                    % recevie_report_begin.time
                    % msg_id_i
                    % recevie_report_begin.version
                    % recevie_report_begin.line_id
                    % recevie_report_begin.report_id
                    % report_type_i
                    % recevie_report_begin.crc);
                Log(msg);
            }
            // ö��ת��
            recevie_report_begin.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            recevie_report_begin.report_type = static_cast<hdata::statistics_report_type>(report_type_i);
            // ���ݴ���
            if (hdata::statistics_report_type::E_GROUP_RUNNING == recevie_report_begin.report_type)
            {
                ci.clear_report_group_running_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_GROUP_RUNNING_REPORT, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_GROUP_RUNNING_REPORT, recevie_report_begin.crc);
            }
            else if (hdata::statistics_report_type::E_DRIVER_DISTANCE == recevie_report_begin.report_type)
            {
                ci.clear_report_driver_distance_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, recevie_report_begin.crc);
            }
            else if (hdata::statistics_report_type::E_DISPATHCHER == recevie_report_begin.report_type)
            {
                ci.clear_report_dispatcher_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_DISPATCHER_REPORT, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_DISPATCHER_REPORT, recevie_report_begin.crc);
            }
            else if (hdata::statistics_report_type::E_GROUP_BAK == recevie_report_begin.report_type)
            {
                ci.clear_report_group_bak_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_GROUP_BAK_REPORT, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_GROUP_BAK_REPORT, recevie_report_begin.crc);
            }
            else if (hdata::statistics_report_type::E_GROUP_STATUS == recevie_report_begin.report_type)
            {
                ci.clear_report_group_status_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_GROUP_STATUS_REPORT, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_GROUP_STATUS_REPORT, recevie_report_begin.crc);
            }
            else if (hdata::statistics_report_type::E_ACTION == recevie_report_begin.report_type)
            {
                ci.clear_report_action_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_ACTION_REPORT, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_ACTION_REPORT, recevie_report_begin.crc);
            }
            else if (hdata::statistics_report_type::E_ALARM == recevie_report_begin.report_type)
            {
                ci.clear_report_alarm_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_ALARM_REPORT, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_ALARM_REPORT, recevie_report_begin.crc);
            }
            else 
            {
                Log("ReportBegin type error:" + std::to_string(recevie_report_begin.report_type));
            }
        } while (false);
    }
	void ReportGroupRunning(rapidjson::Document& document_read) 
	{
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportGroupRunning recevie_group_running;
            int msg_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", recevie_group_running.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", recevie_group_running.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", recevie_group_running.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", recevie_group_running.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "total_message", recevie_group_running.total_message)) break;
            if (!hcommon::GetJsonInt(document_read, "message_sequence", recevie_group_running.message_sequence)) break;
            if (!hcommon::GetJsonInt(document_read, "count", recevie_group_running.count)) break;
            if (!hcommon::GetJsonGroupRunning(document_read, "data", recevie_group_running.group_running_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:����������̱���ReportGroupRunning,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],total_message[%d],message_sequence[%d],count[%d],group_running_data_size[%d]")
                    % recevie_group_running.time
                    % msg_id_i
                    % recevie_group_running.version
                    % recevie_group_running.line_id
                    % recevie_group_running.report_id
                    % recevie_group_running.total_message
                    % recevie_group_running.message_sequence
                    % recevie_group_running.count
                    % recevie_group_running.group_running_data.size());
                Log(msg);
            }
            // ö��ת��
            recevie_group_running.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_GROUP_RUNNING_REPORT, flag);
            if (flag)
            {
                Log("��ӳ���������̱��浽������");
                ci.push_report_group_running_impl(recevie_group_running);
            }
            else
            {
                Log("ERROR:�յ�����������̱���");
            }
        } while (false);
    }
    void ReportDriverDistance(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportDriverDistance driver_distance;
            int msg_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", driver_distance.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", driver_distance.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", driver_distance.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", driver_distance.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "total_message", driver_distance.total_message)) break;
            if (!hcommon::GetJsonInt(document_read, "message_sequence", driver_distance.message_sequence)) break;
            if (!hcommon::GetJsonInt(document_read, "count", driver_distance.count)) break;
            if (!hcommon::GetJsonDriverDistance(document_read, "data", driver_distance.driver_distance_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:˾����ʻ��̱���ReportDriverDistance,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],total_message[%d],message_sequence[%d],count[%d],driver_distance_data_size[%d]")
                    % driver_distance.time
                    % msg_id_i
                    % driver_distance.version
                    % driver_distance.line_id
                    % driver_distance.report_id
                    % driver_distance.total_message
                    % driver_distance.message_sequence
                    % driver_distance.count
                    % driver_distance.driver_distance_data.size());
                Log(msg);
            }
            // ö��ת��
            driver_distance.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, flag);
            if (flag)
            {
                Log("���˾����ʻ��̱��浽������");
                ci.push_report_driver_distance_impl(driver_distance);
            }
            else
            {
                Log("ERROR:�յ�˾����ʻ��̱���");
            }
        } while (false);
    }
    void ReportDisPatcher(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportDisPatcher dispatcher;
            int msg_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", dispatcher.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", dispatcher.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", dispatcher.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", dispatcher.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "total_message", dispatcher.total_message)) break;
            if (!hcommon::GetJsonInt(document_read, "message_sequence", dispatcher.message_sequence)) break;
            if (!hcommon::GetJsonInt(document_read, "count", dispatcher.count)) break;
            if (!hcommon::GetJsonDisPatcher(document_read, "data", dispatcher.dispatcher_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:������־����ReportDisPatcher,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],total_message[%d],message_sequence[%d],count[%d],dispatcher_data_size[%d]")
                    % dispatcher.time
                    % msg_id_i
                    % dispatcher.version
                    % dispatcher.line_id
                    % dispatcher.report_id
                    % dispatcher.total_message
                    % dispatcher.message_sequence
                    % dispatcher.count
                    % dispatcher.dispatcher_data.size());
                Log(msg);
            }
            // ö��ת��
            dispatcher.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_DISPATCHER_REPORT, flag);
            if (flag)
            {
                Log("��ӵ�����־���浽������");
                ci.push_report_dispatcher_impl(dispatcher);
            }
            else
            {
                Log("ERROR:�յ�������־����");
            }
        } while (false);
    }
    void ReportGroupBak(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportGroupBak group_bak;
            int msg_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", group_bak.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", group_bak.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", group_bak.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", group_bak.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "total_message", group_bak.total_message)) break;
            if (!hcommon::GetJsonInt(document_read, "message_sequence", group_bak.message_sequence)) break;
            if (!hcommon::GetJsonInt(document_read, "count", group_bak.count)) break;
            if (!hcommon::GetJsonGroupBak(document_read, "data", group_bak.group_bak_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:�汸������ReportGroupBak,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],total_message[%d],message_sequence[%d],count[%d],group_bak_data_size[%d]")
                    % group_bak.time
                    % msg_id_i
                    % group_bak.version
                    % group_bak.line_id
                    % group_bak.report_id
                    % group_bak.total_message
                    % group_bak.message_sequence
                    % group_bak.count
                    % group_bak.group_bak_data.size());
                Log(msg);
            }
            // ö��ת��
            group_bak.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_GROUP_BAK_REPORT, flag);
            if (flag)
            {
                Log("��Ӵ汸�����浽������");
                ci.push_report_group_bak_impl(group_bak);
            }
            else
            {
                Log("ERROR:�յ��汸������");
            }
        } while (false);
    }
    void ReportGroupStatus(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportGroupStatus group_status;
            int msg_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", group_status.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", group_status.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", group_status.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", group_status.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "total_message", group_status.total_message)) break;
            if (!hcommon::GetJsonInt(document_read, "message_sequence", group_status.message_sequence)) break;
            if (!hcommon::GetJsonInt(document_read, "count", group_status.count)) break;
            if (!hcommon::GetJsonGroupStatus(document_read, "data", group_status.group_status_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:�г�����״̬����ReportGroupStatus,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],total_message[%d],message_sequence[%d],count[%d],group_status_size[%d]")
                    % group_status.time
                    % msg_id_i
                    % group_status.version
                    % group_status.line_id
                    % group_status.report_id
                    % group_status.total_message
                    % group_status.message_sequence
                    % group_status.count
                    % group_status.group_status_data.size());
                Log(msg);
            }
            // ö��ת��
            group_status.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_GROUP_STATUS_REPORT, flag);
            if (flag)
            {
                Log("����г�����״̬���浽������");
                ci.push_report_group_status_impl(group_status);
            }
            else
            {
                Log("ERROR:�յ��г�����״̬����");
            }
        } while (false);
    }
    void ReportAction(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportAction atcion;
            int msg_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", atcion.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", atcion.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", atcion.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", atcion.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "total_message", atcion.total_message)) break;
            if (!hcommon::GetJsonInt(document_read, "message_sequence", atcion.message_sequence)) break;
            if (!hcommon::GetJsonInt(document_read, "count", atcion.count)) break;
            if (!hcommon::GetJsonAction(document_read, "data", atcion.action_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:����������ϢReportAction,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],total_message[%d],message_sequence[%d],count[%d],action_size[%d]")
                    % atcion.time
                    % msg_id_i
                    % atcion.version
                    % atcion.line_id
                    % atcion.report_id
                    % atcion.total_message
                    % atcion.message_sequence
                    % atcion.count
                    % atcion.action_data.size());
                Log(msg);
            }
            // ö��ת��
            atcion.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_ACTION_REPORT, flag);
            if (flag)
            {
                Log("��Ӳ���������Ϣ��������");
                ci.push_report_action_impl(atcion);
            }
            else
            {
                Log("ERROR:�յ�����������Ϣ");
            }
        } while (false);
    }
    void ReportAlarm(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportAlarm alarm;
            int msg_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", alarm.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", alarm.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", alarm.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", alarm.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "total_message", alarm.total_message)) break;
            if (!hcommon::GetJsonInt(document_read, "message_sequence", alarm.message_sequence)) break;
            if (!hcommon::GetJsonInt(document_read, "count", alarm.count)) break;
            if (!hcommon::GetJsonAlarm(document_read, "data", alarm.alarm_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:�г���Ϣ��ϵͳ�¼�ReportAlarm,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],total_message[%d],message_sequence[%d],message_sequence[%d],alarm_size[%d]")
                    % alarm.time
                    % msg_id_i
                    % alarm.version
                    % alarm.line_id
                    % alarm.report_id
                    % alarm.total_message
                    % alarm.message_sequence
                    % alarm.count
                    % alarm.alarm_data.size());
                Log(msg);
            }
            // ö��ת��
            alarm.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_ALARM_REPORT, flag);
            if (flag)
            {
                Log("����г���Ϣ��ϵͳ�¼���������");
                ci.push_report_alarm_impl(alarm);
            }
            else
            {
                Log("ERROR:�յ��г���Ϣ��ϵͳ�¼�");
            }
        } while (false);
    }
    void ScheduleInused(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ScheduleInused schedule_inused;
            int msg_id_i = -1, sub_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", schedule_inused.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", schedule_inused.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", schedule_inused.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "date", schedule_inused.date)) break;
            if (!hcommon::GetJsonInt(document_read, "sub_id", sub_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "train_id", schedule_inused.train_id)) break;
            if (!hcommon::GetJsonString(document_read, "trip_cnt", schedule_inused.trip_cnt)) break;
            if (!hcommon::GetJsonScheduleInused(document_read, "inused_data", schedule_inused.inused_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:�ƻ��г�����ͼ��ϢScheduleInused,time[%s],msg_id[%d],version[%s],line_id[%s],date[%s],sub_id_i[%d],train_id[%s],trip_cnt[%s],inused_data_size[%d]")
                    % schedule_inused.time
                    % msg_id_i
                    % schedule_inused.version
                    % schedule_inused.line_id
                    % schedule_inused.date
                    % sub_id_i
                    % schedule_inused.train_id
                    % schedule_inused.trip_cnt
                    % schedule_inused.inused_data.size());
                Log(msg);
            }
            // ö��ת��
            schedule_inused.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_INUSED_SCHEDULE, flag);
            if (flag)
            {
                Log("��Ӽƻ��г�����ͼ��Ϣ��������");
                ci.push_schedual_inused_impl(schedule_inused);
            }
            else
            {
                Log("ERROR:�յ��ƻ��г�����ͼ��Ϣ");
            }
        } while (false);
    }
    void SchedulActual(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::SchedulActual schedule_actual;
            int msg_id_i = -1, sub_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", schedule_actual.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", schedule_actual.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", schedule_actual.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "date", schedule_actual.date)) break;
            if (!hcommon::GetJsonInt(document_read, "sub_id", sub_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "pvid", schedule_actual.pvid)) break;
            if (!hcommon::GetJsonString(document_read, "station_cnt", schedule_actual.station_cnt)) break;
            if (!hcommon::GetJsonSchedulActual(document_read, "actual_data", schedule_actual.actual_data)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:����������ϢSchedulActual,time[%s],msg_id[%d],version[%s],line_id[%s],date[%s],sub_id_i[%d],pvid[%s],station_cnt[%s],actual_data_size[%d]")
                    % schedule_actual.time
                    % msg_id_i
                    % schedule_actual.version
                    % schedule_actual.line_id
                    % schedule_actual.date
                    % sub_id_i
                    % schedule_actual.pvid
                    % schedule_actual.station_cnt
                    % schedule_actual.actual_data.size());
                Log(msg);
            }
            // ö��ת��
            schedule_actual.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            // ���ݴ���
            bool flag = false;
            ci.get_mid_data_flag_impl(hdata::his_data_type::E_HISTORY_SCHEDULE, flag);
            if (flag)
            {
                Log("���ʵ���г�����ͼ��Ϣ������");
                ci.push_schedual_actual_impl(schedule_actual);
            }
            else
            {
                Log("ERROR:�յ�ʵ���г�����ͼ��Ϣ��Ϣ");
            }
        } while (false);
    }
    void ScheduleBegin(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::SchedulBegin schedul_begin;
            int msg_id_i = -1, sub_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", schedul_begin.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", schedul_begin.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", schedul_begin.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "date", schedul_begin.date)) break;
            if (!hcommon::GetJsonInt(document_read, "sub_id", sub_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "crc", schedul_begin.crc)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:����ͼ���Ϳ�ʼScheduleBegin,time[%s],msg_id[%d],version[%s],line_id[%s],date[%s],sub_id[%d],crc[%s]")
                    % schedul_begin.time
                    % msg_id_i
                    % schedul_begin.version
                    % schedul_begin.line_id
                    % schedul_begin.date
                    % sub_id_i
                    % schedul_begin.crc);
                Log(msg);
            }
            // ö��ת��
            schedul_begin.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            schedul_begin.sub_id = static_cast<hdata::tg_driver_type>(sub_id_i);
            // ���ݴ���
            if (hdata::his_data_type::E_INUSED_SCHEDULE == schedul_begin.msg_id)
            {
                ci.clear_schedual_inused_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_INUSED_SCHEDULE, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_INUSED_SCHEDULE, schedul_begin.crc);
            }
            else if (hdata::his_data_type::E_HISTORY_SCHEDULE == schedul_begin.msg_id)
            {
                ci.clear_schedual_actual_impl();
                ci.set_mid_data_flag_impl(hdata::his_data_type::E_HISTORY_SCHEDULE, true);
                ci.set_mid_data_crc_impl(hdata::his_data_type::E_HISTORY_SCHEDULE, schedul_begin.crc);
            }
            else
            {
                Log("ScheduleBegin type error:" + std::to_string(schedul_begin.msg_id));
            }
        } while (false);
    }
    void ScheduleEnd(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::SchedulEnd schedul_end;
            int msg_id_i = -1, sub_id_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", schedul_end.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", schedul_end.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", schedul_end.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "date", schedul_end.date)) break;
            if (!hcommon::GetJsonInt(document_read, "sub_id", sub_id_i)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:��Ϣ���ͽ���SchedulEnd,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],sub_id[%d]")
                    % schedul_end.time
                    % msg_id_i
                    % schedul_end.version
                    % schedul_end.line_id
                    % schedul_end.date
                    % sub_id_i);
                Log(msg);
            }
            // ö��ת��
            schedul_end.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            schedul_end.sub_id = static_cast<hdata::tg_driver_type>(sub_id_i);
            boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
            // ���ݴ���
            if (hdata::his_data_type::E_INUSED_SCHEDULE == schedul_end.msg_id)
            {
                if (Judge_CRC(hdata::his_data_type::E_INUSED_SCHEDULE))
                {
                    std::list<hdata::ScheduleInused> scheduel_inused;
                    ci.get_schedual_inused_impl(scheduel_inused);
                    ci.set_schedual_inused_his(scheduel_inused);
                    ci.set_done_his(hdata::his_data_type::E_INUSED_SCHEDULE, true);
                    ci.set_update_time_his(hdata::his_data_type::E_INUSED_SCHEDULE, now);
                    Log("�ƻ��г�����ͼ����CRCУ����һ�£����ݻ������");
                }
                else
                {
                    ci.set_do_false_his(hdata::his_data_type::E_INUSED_SCHEDULE, true);
                    Log("�ƻ��г�����ͼ����CRCУ���벻һ��");
                }
            }
            else if (hdata::his_data_type::E_HISTORY_SCHEDULE == schedul_end.msg_id)
            {
                if (Judge_CRC(hdata::his_data_type::E_HISTORY_SCHEDULE))
                {
                    std::list<hdata::SchedulActual> scheduel_actual;
                    ci.get_schedual_actual_impl(scheduel_actual);
                    ci.set_schedual_actual_his(scheduel_actual);
                    ci.set_done_his(hdata::his_data_type::E_HISTORY_SCHEDULE, true);
                    ci.set_update_time_his(hdata::his_data_type::E_HISTORY_SCHEDULE, now);
                    Log("ʵ���г�����ͼ����CRCУ����һ�£����ݻ������");
                }
                else
                {
                    ci.set_do_false_his(hdata::his_data_type::E_HISTORY_SCHEDULE, true);
                    Log("ʵ���г�����ͼ����CRCУ���벻һ��");
                }
            }
            else
            {
                Log("ScheduleEnd type error:" + std::to_string(schedul_end.msg_id));
            }
        } while (false);
    }
    void ReportEnd(rapidjson::Document& document_read) 
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportEnd recevie_report_end;
            int msg_id_i = -1, report_type_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", recevie_report_end.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", recevie_report_end.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", recevie_report_end.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", recevie_report_end.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "report_type", report_type_i)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:��Ϣ���ͽ���ReportEnd,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],report_type[%d]")
                    % recevie_report_end.time
                    % msg_id_i
                    % recevie_report_end.version
                    % recevie_report_end.line_id
                    % recevie_report_end.report_id
                    % report_type_i);
                Log(msg);
            }
            // ö��ת��
            recevie_report_end.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            recevie_report_end.report_type = static_cast<hdata::statistics_report_type>(report_type_i);
            // ���ݴ���
            boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
            if (hdata::statistics_report_type::E_GROUP_RUNNING == recevie_report_end.report_type)
            {
                if (Judge_CRC(hdata::his_data_type::E_GROUP_RUNNING_REPORT))
                {
                    std::list<hdata::ReportGroupRunning> report_group_running;
                    ci.get_report_group_running_impl(report_group_running);
                    ci.set_report_group_running_his(report_group_running); // ���ݴ��м�����--->������
                    ci.set_done_his(hdata::his_data_type::E_GROUP_RUNNING_REPORT, true);
                    ci.set_update_time_his(hdata::his_data_type::E_GROUP_RUNNING_REPORT, now);
                    Log("����������̱�������CRCУ����һ�£����ݻ������");
                }
                else 
                {
                    ci.set_do_false_his(hdata::his_data_type::E_GROUP_RUNNING_REPORT, true);
                    Log("����������̱�������CRCУ���벻һ��");
                }
            }
            else if (hdata::statistics_report_type::E_DRIVER_DISTANCE == recevie_report_end.report_type)
            {
                if (Judge_CRC(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT))
                {
                    std::list<hdata::ReportDriverDistance> report_driver_distance;
                    ci.get_report_driver_distance_impl(report_driver_distance);
                    ci.set_report_driver_distance_his(report_driver_distance);
                    ci.set_done_his(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, true);
                    ci.set_update_time_his(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, now);
                    Log("˾����ʻ��̱�������CRCУ����һ�£����ݻ������");
                }
                else
                {
                    ci.set_do_false_his(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, true);
                    Log("˾����ʻ��̱�������CRCУ���벻һ��");
                }
            }
            else if (hdata::statistics_report_type::E_DISPATHCHER == recevie_report_end.report_type)
            {
                if (Judge_CRC(hdata::his_data_type::E_DISPATCHER_REPORT))
                {
                    std::list<hdata::ReportDisPatcher> report_dispatcher;
                    ci.get_report_dispatcher_impl(report_dispatcher);
                    ci.set_report_dispatcher_his(report_dispatcher);
                    ci.set_done_his(hdata::his_data_type::E_DISPATCHER_REPORT, true);
                    ci.set_update_time_his(hdata::his_data_type::E_DISPATCHER_REPORT, now);
                    Log("������־��������CRCУ����һ�£����ݻ������");
                }
                else
                {
                    ci.set_do_false_his(hdata::his_data_type::E_DISPATCHER_REPORT, true);
                    Log("������־��������CRCУ���벻һ��");
                }
            }
            else if (hdata::statistics_report_type::E_GROUP_BAK == recevie_report_end.report_type)
            {
                if (Judge_CRC(hdata::his_data_type::E_GROUP_BAK_REPORT))
                {
                    std::list<hdata::ReportGroupBak> report_group_bak;
                    ci.get_report_group_bak_impl(report_group_bak);
                    ci.set_report_group_bak_his(report_group_bak);
                    ci.set_done_his(hdata::his_data_type::E_GROUP_BAK_REPORT, true);
                    ci.set_update_time_his(hdata::his_data_type::E_GROUP_BAK_REPORT, now);
                    Log("�汸����������CRCУ����һ�£����ݻ������");
                }
                else
                {
                    ci.set_do_false_his(hdata::his_data_type::E_GROUP_BAK_REPORT, true);
                    Log("�汸����������CRCУ���벻һ��");
                }
            }
            else if (hdata::statistics_report_type::E_GROUP_STATUS == recevie_report_end.report_type)
            {
                if (Judge_CRC(hdata::his_data_type::E_GROUP_STATUS_REPORT))
                {
                    std::list<hdata::ReportGroupStatus> report_group_status;
                    ci.get_report_group_status_impl(report_group_status);
                    ci.set_report_group_status_his(report_group_status);
                    ci.set_done_his(hdata::his_data_type::E_GROUP_STATUS_REPORT, true);
                    ci.set_update_time_his(hdata::his_data_type::E_GROUP_STATUS_REPORT, now);
                    Log("�г�����״̬��������CRCУ����һ�£����ݻ������");
                }
                else
                {
                    ci.set_do_false_his(hdata::his_data_type::E_GROUP_STATUS_REPORT, true);
                    Log("�г�����״̬��������CRCУ���벻һ��");
                }
            }
            else if (hdata::statistics_report_type::E_ACTION == recevie_report_end.report_type)
            {
                if (Judge_CRC(hdata::his_data_type::E_ACTION_REPORT))
                {
                    std::list<hdata::ReportAction> report_action;
                    ci.get_report_action_impl(report_action);
                    ci.set_report_action_his(report_action);
                    ci.set_done_his(hdata::his_data_type::E_ACTION_REPORT, true);
                    ci.set_update_time_his(hdata::his_data_type::E_ACTION_REPORT, now);
                    Log("����������Ϣ����CRCУ����һ�£����ݻ������");
                }
                else
                {
                    ci.set_do_false_his(hdata::his_data_type::E_ACTION_REPORT, true);
                    Log("����������Ϣ����CRCУ���벻һ��");
                }
            }
            else if (hdata::statistics_report_type::E_ALARM == recevie_report_end.report_type)
            {
                if (Judge_CRC(hdata::his_data_type::E_ALARM_REPORT))
                {
                    std::list<hdata::ReportAlarm> report_alarm;
                    ci.get_report_alarm_impl(report_alarm);
                    ci.set_report_alarm_his(report_alarm);
                    ci.set_done_his(hdata::his_data_type::E_ALARM_REPORT, true);
                    ci.set_update_time_his(hdata::his_data_type::E_ALARM_REPORT, now);
                    Log("�г���Ϣ��ϵͳ�¼�����CRCУ����һ�£����ݻ������");
                }
                else
                {
                    ci.set_do_false_his(hdata::his_data_type::E_ALARM_REPORT, true);
                    Log("�г���Ϣ��ϵͳ�¼�����CRCУ���벻һ��");
                }
            }
            else
            {
                Log("ReportEnd type error:" + std::to_string(recevie_report_end.report_type));
            }
        } while (false);
    }
    void ReportNoNack(rapidjson::Document& document_read)
    {
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::AskNoNack ask_no_nack;
            int msg_id_i = -1, result_i = -1;
            if (!hcommon::GetJsonString(document_read, "time", ask_no_nack.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", ask_no_nack.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", ask_no_nack.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", ask_no_nack.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "result", result_i)) break;
            if (!hcommon::GetJsonString(document_read, "content", ask_no_nack.content)) break;
            {
                std::string msg = boost::str(boost::format("����ͨ���ظ�:��Ϣ���Ͳ�ѯ�޽��ReportNoNack,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],result[%d], content[%s]")
                    % ask_no_nack.time
                    % msg_id_i
                    % ask_no_nack.version
                    % ask_no_nack.line_id
                    % ask_no_nack.report_id
                    % result_i
                    % ask_no_nack.content);
                Log(msg);
            }
            // ö��ת��
            ask_no_nack.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            ask_no_nack.result = static_cast<hdata::ask_nack>(result_i);
            // ���ݴ���
            if ("01" == ask_no_nack.report_id) 
            {
                ci.set_do_false_his(hdata::his_data_type::E_GROUP_RUNNING_REPORT, true);
            }
            else if ("02" == ask_no_nack.report_id) 
            {
                ci.set_do_false_his(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, true);
            }
            else if ("03" == ask_no_nack.report_id)
            {
                ci.set_do_false_his(hdata::his_data_type::E_DISPATCHER_REPORT, true);
            }
            else if ("04" == ask_no_nack.report_id)
            {
                ci.set_do_false_his(hdata::his_data_type::E_GROUP_BAK_REPORT, true);
            }
            else if ("05" == ask_no_nack.report_id)
            {
                ci.set_do_false_his(hdata::his_data_type::E_GROUP_STATUS_REPORT, true);
            }
            else if ("06" == ask_no_nack.report_id)
            {
                ci.set_do_false_his(hdata::his_data_type::E_ACTION_REPORT, true);
            }
            else if ("07" == ask_no_nack.report_id)
            {
                ci.set_do_false_his(hdata::his_data_type::E_ALARM_REPORT, true);
            }
            else if ("08" == ask_no_nack.report_id)
            {
                ci.set_do_false_his(hdata::his_data_type::E_INUSED_SCHEDULE, true);
            }
            else if ("09" == ask_no_nack.report_id)
            {
                ci.set_do_false_his(hdata::his_data_type::E_HISTORY_SCHEDULE, true);
            }
            else 
            {
                Log("��Ϣ���Ͳ�ѯ�޽��ReportNoNack��report_id����");
            }
        } while (false);
    }
    uint32_t GetCrc32(const std::string& my_string) {
        boost::crc_32_type result;
        result.process_bytes(my_string.data(), my_string.length());
        return result.checksum();
    }
    bool Judge_CRC(hdata::his_data_type type) 
    {
        bool nRet = false;
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        // ��ʼ��־λ��Ϊfalse
        ci.set_mid_data_flag_impl(type, false);
        // �ж�CRCһ���ԣ�һ�£�������ʵ�������У���һ�£���ӡ������־�����ݲ�����
        std::string crc1, crc2;
        uint32_t crc2_;
        ci.get_mid_data_crc_impl(type, crc1);
        // TODO����ȡreport_group_running��CRCУ����--crc2
        std::string data_s;
        ci.get_mid_data_string_impl(type, data_s);
        crc2_ = GetCrc32(data_s);
        std::cout << crc2_;
        crc2 = std::to_string(crc2_);
        if (crc1 == crc2) nRet = true;
        return nRet;
    }
}	// namespace hclient

namespace hserver {
    void ReportAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write)
    {
        boost::ignore_unused(buffer_write);
        std::string str_write;
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ReportAsk report_ask;
            int msg_id_i = 0, msg_flag_i = 0;
            if (!hcommon::GetJsonString(document_read, "time", report_ask.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", report_ask.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", report_ask.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", report_ask.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_flag", msg_flag_i)) break;
            {
                std::string msg = boost::str(boost::format("���Ե���������:ͳ����Ϣ��ѯReportAsk,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],msg_flag[%d]")
                    % report_ask.time
                    % msg_id_i
                    % report_ask.version
                    % report_ask.line_id
                    % report_ask.report_id
                    % msg_flag_i);
                Log(msg);
            }
            // ö��ת��
            report_ask.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            report_ask.msg_flag = static_cast<hdata::statistics_report_type>(msg_flag_i);
            // ���ݴ���
            if (hdata::statistics_report_type::E_GROUP_RUNNING == report_ask.msg_flag) 
            {
                Log("ͳ����Ϣ��ѯ:�����������");
                if (!RepeatQuery(hdata::his_data_type::E_GROUP_RUNNING_REPORT)) // �Ƿ��ظ���ѯ
                {
                    judge_is_doing(hdata::his_data_type::E_GROUP_RUNNING_REPORT); // �Ƿ��ѯͬһ�����ͣ�true��������У�false��ֱ�Ӳ�ѯ��TODO�д�����
                    ci.set_is_doing_his(hdata::his_data_type::E_GROUP_RUNNING_REPORT, true);
                    ci.set_request_group_running_tunnel_his(true, report_ask.line_id);
                    DealReportBlock(hdata::his_data_type::E_GROUP_RUNNING_REPORT, hdata::statistics_report_type::E_GROUP_RUNNING, buffer_write);
                }
                else 
                {
                    SendReportData(hdata::his_data_type::E_GROUP_RUNNING_REPORT, hdata::statistics_report_type::E_GROUP_RUNNING, buffer_write);
                }
            }
            else if (hdata::statistics_report_type::E_DRIVER_DISTANCE == report_ask.msg_flag)
            {
                Log("ͳ����Ϣ��ѯ:˾����ʻ���");
                if (!RepeatQuery(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT))
                {
                    judge_is_doing(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT);
                    ci.set_is_doing_his(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, true);
                    ci.set_request_driver_distance_tunnel_his(true, report_ask.line_id);
                    DealReportBlock(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, hdata::statistics_report_type::E_DRIVER_DISTANCE, buffer_write);
                }
                else
                {
                    SendReportData(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, hdata::statistics_report_type::E_DRIVER_DISTANCE, buffer_write);
                }
            }
            else if (hdata::statistics_report_type::E_DISPATHCHER == report_ask.msg_flag)
            {
                Log("ͳ����Ϣ��ѯ:������־");
                if (!RepeatQuery(hdata::his_data_type::E_DISPATCHER_REPORT))
                {
                    judge_is_doing(hdata::his_data_type::E_DISPATCHER_REPORT);
                    ci.set_is_doing_his(hdata::his_data_type::E_DISPATCHER_REPORT, true);
                    ci.set_request_dispatcher_tunnel_his(true, report_ask.line_id);
                    DealReportBlock(hdata::his_data_type::E_DISPATCHER_REPORT, hdata::statistics_report_type::E_DISPATHCHER, buffer_write);
                }
                else
                {
                    SendReportData(hdata::his_data_type::E_DISPATCHER_REPORT, hdata::statistics_report_type::E_DISPATHCHER, buffer_write);
                }
            }
            else if (hdata::statistics_report_type::E_GROUP_BAK == report_ask.msg_flag)
            {
                Log("ͳ����Ϣ��ѯ:�汸��");
                if (!RepeatQuery(hdata::his_data_type::E_GROUP_BAK_REPORT))
                {
                    judge_is_doing(hdata::his_data_type::E_GROUP_BAK_REPORT);
                    ci.set_is_doing_his(hdata::his_data_type::E_GROUP_BAK_REPORT, true);
                    ci.set_request_group_bak_tunnel_his(true, report_ask.line_id);
                    DealReportBlock(hdata::his_data_type::E_GROUP_BAK_REPORT, hdata::statistics_report_type::E_GROUP_BAK, buffer_write);
                }
                else
                {
                    SendReportData(hdata::his_data_type::E_GROUP_BAK_REPORT, hdata::statistics_report_type::E_GROUP_BAK, buffer_write);
                }
            }
            else if (hdata::statistics_report_type::E_GROUP_STATUS == report_ask.msg_flag)
            {
                Log("ͳ����Ϣ��ѯ:�г�����״̬");
                if (!RepeatQuery(hdata::his_data_type::E_GROUP_STATUS_REPORT))
                {
                    judge_is_doing(hdata::his_data_type::E_GROUP_STATUS_REPORT);
                    ci.set_is_doing_his(hdata::his_data_type::E_GROUP_STATUS_REPORT, true);
                    ci.set_request_group_status_tunnel_his(true, report_ask.line_id);
                    DealReportBlock(hdata::his_data_type::E_GROUP_STATUS_REPORT, hdata::statistics_report_type::E_GROUP_STATUS, buffer_write);
                }
                else
                {
                    SendReportData(hdata::his_data_type::E_GROUP_STATUS_REPORT, hdata::statistics_report_type::E_GROUP_STATUS, buffer_write);
                }
            }
            else 
            {
                Log("ͳ����Ϣ��ѯ:δ�ҵ���Ӧ�Ĳ�ѯ����");
            }
        } while (false);
    }
    void AlarmAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write)
    {
        boost::ignore_unused(buffer_write);
        std::string str_write;
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::AlarmAsk alarm_ask;
            int msg_id_i = 0, msg_type_i = 0;
            if (!hcommon::GetJsonString(document_read, "time", alarm_ask.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", alarm_ask.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", alarm_ask.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", alarm_ask.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_type", msg_type_i)) break;
            if (!hcommon::GetJsonString(document_read, "start_time", alarm_ask.start_time)) break;
            if (!hcommon::GetJsonString(document_read, "end_time", alarm_ask.end_time)) break;
            {
                std::string msg = boost::str(boost::format("���Ե���������:�¼����澯��ѯAlarmAsk,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],msg_type[%d],start_time[%s], end_time[%s]")
                    % alarm_ask.time
                    % msg_id_i
                    % alarm_ask.version
                    % alarm_ask.line_id
                    % alarm_ask.report_id
                    % msg_type_i
                    % alarm_ask.start_time
                    % alarm_ask.end_time);
                Log(msg);
            }
            // ö��ת��
            alarm_ask.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            alarm_ask.msg_type = static_cast<hdata::action_msg_type>(msg_type_i);
            // ���ݴ���
            if (hdata::action_msg_type::E_ACTION_MSG == alarm_ask.msg_type)
            {
                Log("�¼����澯��ѯ:��������");
                if (!RepeatQuery(hdata::his_data_type::E_ACTION_REPORT))
                {
                    judge_is_doing(hdata::his_data_type::E_ACTION_REPORT);
                    ci.set_is_doing_his(hdata::his_data_type::E_ACTION_REPORT, true);
                    ci.set_request_action_tunnel_his(true, alarm_ask.line_id, alarm_ask.start_time, alarm_ask.end_time);
                    DealReportBlock(hdata::his_data_type::E_ACTION_REPORT, hdata::statistics_report_type::E_ACTION, buffer_write);
                }
                else
                {
                    SendReportData(hdata::his_data_type::E_ACTION_REPORT, hdata::statistics_report_type::E_ACTION, buffer_write);
                }
            }
            else if (hdata::action_msg_type::E_ALARM_MSG == alarm_ask.msg_type)
            {
                Log("�¼����澯��ѯ:ϵͳ�¼�����");
                if (!RepeatQuery(hdata::his_data_type::E_ALARM_REPORT))
                {
                    judge_is_doing(hdata::his_data_type::E_ALARM_REPORT);
                    ci.set_is_doing_his(hdata::his_data_type::E_ALARM_REPORT, true);
                    ci.set_request_alarm_tunnel_his(true, alarm_ask.line_id, alarm_ask.start_time, alarm_ask.end_time);
                    DealReportBlock(hdata::his_data_type::E_ALARM_REPORT, hdata::statistics_report_type::E_ALARM, buffer_write);
                }
                else
                {
                    SendReportData(hdata::his_data_type::E_ALARM_REPORT, hdata::statistics_report_type::E_ALARM, buffer_write);
                }
            }
            else
            {
                Log("�¼����澯��ѯ:δ�ҵ���Ӧ�Ĳ�ѯ����");
            }
        } while (false);
    }
    void ScheduleAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write)
    {
        boost::ignore_unused(buffer_write);
        std::string str_write;
        // ��������
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        do
        {
            hdata::ScheduleAsk schedule_ask;
            int msg_id_i = 0, tg_type_i = 0;
            if (!hcommon::GetJsonString(document_read, "time", schedule_ask.time)) break;
            if (!hcommon::GetJsonInt(document_read, "msg_id", msg_id_i)) break;
            if (!hcommon::GetJsonString(document_read, "version", schedule_ask.version)) break;
            if (!hcommon::GetJsonString(document_read, "line_id", schedule_ask.line_id)) break;
            if (!hcommon::GetJsonString(document_read, "report_id", schedule_ask.report_id)) break;
            if (!hcommon::GetJsonInt(document_read, "tg_type", tg_type_i)) break;
            if (!hcommon::GetJsonString(document_read, "date", schedule_ask.date)) break;
            {
                std::string msg = boost::str(boost::format("���Ե���������:����ͼ��ѯScheduleAsk,time[%s],msg_id[%d],version[%s],line_id[%s],report_id[%s],tg_type[%d],date[%s]")
                    % schedule_ask.time
                    % msg_id_i
                    % schedule_ask.version
                    % schedule_ask.line_id
                    % schedule_ask.report_id
                    % tg_type_i
                    % schedule_ask.date);
                Log(msg);
            }
            // ö��ת��
            schedule_ask.msg_id = static_cast<hdata::his_data_type>(msg_id_i);
            schedule_ask.tg_type = static_cast<hdata::tg_msg_type>(tg_type_i);
            // ���ݴ���
            if (hdata::tg_msg_type::E_TG_PLAN == schedule_ask.tg_type)
            {
                Log("����ͼ��ѯ:�ƻ�����ͼ");
                if (!RepeatQuery(hdata::his_data_type::E_INUSED_SCHEDULE))
                {
                    judge_is_doing(hdata::his_data_type::E_INUSED_SCHEDULE);
                    ci.set_is_doing_his(hdata::his_data_type::E_INUSED_SCHEDULE, true);
                    ci.set_request_schedual_inused_tunnel_his(true, schedule_ask.line_id, schedule_ask.date);
                    DealScheduleBlock(hdata::his_data_type::E_INUSED_SCHEDULE, buffer_write);
                }
                else
                {
                    SendSchedulData(hdata::his_data_type::E_INUSED_SCHEDULE, buffer_write);
                }
            }
            else if (hdata::tg_msg_type::E_TG_ACTUAL == schedule_ask.tg_type)
            {
                Log("����ͼ��ѯ:ʵ������ͼ");
                if (!RepeatQuery(hdata::his_data_type::E_HISTORY_SCHEDULE))
                {
                    judge_is_doing(hdata::his_data_type::E_HISTORY_SCHEDULE);
                    ci.set_is_doing_his(hdata::his_data_type::E_HISTORY_SCHEDULE, true);
                    ci.set_request_schedual_actual_tunnel_his(true, schedule_ask.line_id, schedule_ask.date);
                    DealScheduleBlock(hdata::his_data_type::E_HISTORY_SCHEDULE, buffer_write);
                }
                else
                {
                    SendSchedulData(hdata::his_data_type::E_HISTORY_SCHEDULE, buffer_write);
                }
            }
            else
            {
                Log("����ͼ��ѯ:δ�ҵ���Ӧ�Ĳ�ѯ����");
            }
        } while (false);
    }

    void SendReportData(const hdata::his_data_type type, hdata::statistics_report_type report_type, std::list<boost::beast::flat_buffer>& buffer_write)
    {
        std::string str_buf;
        boost::beast::flat_buffer buf;
        std::string now = hcommon::SimpleTime();
        std::string version = "0.1";
        std::string line_id;
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        ci.get_request_line_id_his(type, line_id);
        // ��ʼ
        str_buf = hframe::frame_report_start_end(
                    now, hdata::his_data_type::E_REPORT_BEGIN, version, line_id, "01", report_type).pack();
        hcommon::String2FlatBuffer(str_buf, buf);
        buffer_write.push_back(buf);
        // ����
        if (hdata::his_data_type::E_GROUP_RUNNING_REPORT == type) 
        {
            std::list<hdata::ReportGroupRunning> report_data;
            ci.get_report_group_running_his(report_data);
            std::list<hdata::ReportGroupRunning>::const_iterator iter;
            for (iter = report_data.begin(); iter != report_data.end(); iter++)
            {
                str_buf = hframe::frame_running_group_report(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->group_running_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
        }
        else if (hdata::his_data_type::E_DRIVER_DISTANCE_REPORT == type)
        {
            std::list<hdata::ReportDriverDistance> report_data;
            ci.get_report_driver_distance_his(report_data);
            std::list<hdata::ReportDriverDistance>::const_iterator iter;
            for (iter = report_data.begin(); iter != report_data.end(); iter++)
            {
                str_buf = hframe::frame_driver_distance_report(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->driver_distance_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
        }
        else if (hdata::his_data_type::E_DISPATCHER_REPORT == type)
        {
            std::list<hdata::ReportDisPatcher> report_data;
            ci.get_report_dispatcher_his(report_data);
            std::list<hdata::ReportDisPatcher>::const_iterator iter;
            for (iter = report_data.begin(); iter != report_data.end(); iter++)
            {
                str_buf = hframe::frame_dispatcher_report(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->dispatcher_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
        }
        else if (hdata::his_data_type::E_GROUP_BAK_REPORT == type)
        {
            std::list<hdata::ReportGroupBak> report_data;
            ci.get_report_group_bak_his(report_data);
            std::list<hdata::ReportGroupBak>::const_iterator iter;
            for (iter = report_data.begin(); iter != report_data.end(); iter++)
            {
                str_buf = hframe::framegroup_bak_report(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->group_bak_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
        }
        else if (hdata::his_data_type::E_GROUP_STATUS_REPORT == type)
        {
            std::list<hdata::ReportGroupStatus> report_data;
            ci.get_report_group_status_his(report_data);
            std::list<hdata::ReportGroupStatus>::const_iterator iter;
            for (iter = report_data.begin(); iter != report_data.end(); iter++)
            {
                str_buf = hframe::frame_group_status_report(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->group_status_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
        }
        else if (hdata::his_data_type::E_ACTION_REPORT == type)
        {
            std::list<hdata::ReportAction> report_data;
            ci.get_report_action_his(report_data);
            std::list<hdata::ReportAction>::const_iterator iter;
            for (iter = report_data.begin(); iter != report_data.end(); iter++)
            {
                str_buf = hframe::frame_action_report(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->action_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
        }
        else if (hdata::his_data_type::E_ALARM_REPORT == type)
        {
            std::list<hdata::ReportAlarm> report_data;
            ci.get_report_alarm_his(report_data);
            std::list<hdata::ReportAlarm>::const_iterator iter;
            for (iter = report_data.begin(); iter != report_data.end(); iter++)
            {
                str_buf = hframe::frame_alarm_report(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->alarm_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
        }
        else 
        {
            Log("SendReportData:���ʹ���");
        }
        // ����
        str_buf = hframe::frame_report_start_end(
            now, hdata::his_data_type::E_REPORT_END, version, line_id, "01", report_type).pack();
        buf.clear();
        hcommon::String2FlatBuffer(str_buf, buf);
        buffer_write.push_back(buf);
    }
    void SendSchedulData(const hdata::his_data_type type, std::list<boost::beast::flat_buffer>& buffer_write)
    {
        std::string str_buf;
        boost::beast::flat_buffer buf;
        std::string now = hcommon::SimpleTime();
        std::string version = "0.1";
        std::string line_id;
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        ci.get_request_line_id_his(type, line_id);
        if (hdata::his_data_type::E_INUSED_SCHEDULE == type)
        {
            // ��ʼ
            str_buf = hframe::frame_schedul_start_end(
                now, hdata::his_data_type::E_INUSED_SCHEDULE, version, line_id, "date", hdata::tg_driver_type::E_TG_DRIVER_START).pack();
            hcommon::String2FlatBuffer(str_buf, buf);
            buffer_write.push_back(buf);
            // ����
            std::list<hdata::ScheduleInused> schedule_data;
            ci.get_schedual_inused_his(schedule_data);
            std::list<hdata::ScheduleInused>::const_iterator iter;
            for (iter = schedule_data.begin(); iter != schedule_data.end(); iter++)
            {
                str_buf = hframe::frame_schedul_inused(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->date, iter->sub_id, iter->train_id, iter->trip_cnt, iter->inused_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
            // ����
            str_buf = hframe::frame_schedul_start_end(
                now, hdata::his_data_type::E_INUSED_SCHEDULE, version, line_id, "date", hdata::tg_driver_type::E_TG_DRIVER_END).pack();
            buf.clear();
            hcommon::String2FlatBuffer(str_buf, buf);
            buffer_write.push_back(buf);
        }
        else if (hdata::his_data_type::E_HISTORY_SCHEDULE == type)
        {
            // ��ʼ
            str_buf = hframe::frame_schedul_start_end(
                now, hdata::his_data_type::E_HISTORY_SCHEDULE, version, line_id, "date", hdata::tg_driver_type::E_TG_DRIVER_START).pack();
            hcommon::String2FlatBuffer(str_buf, buf);
            buffer_write.push_back(buf);
            // ����
            std::list<hdata::SchedulActual> schedule_data;
            ci.get_schedual_actual_his(schedule_data);
            std::list<hdata::SchedulActual>::const_iterator iter;
            for (iter = schedule_data.begin(); iter != schedule_data.end(); iter++)
            {
                str_buf = hframe::frame_schedul_actual(
                    iter->time, iter->msg_id, iter->version, iter->line_id, iter->date, iter->sub_id, iter->pvid, iter->station_cnt, iter->actual_data).pack();
                buf.clear();
                hcommon::String2FlatBuffer(str_buf, buf);
                buffer_write.push_back(buf);
            }
            // ����
            str_buf = hframe::frame_schedul_start_end(
                now, hdata::his_data_type::E_HISTORY_SCHEDULE, version, line_id, "date", hdata::tg_driver_type::E_TG_DRIVER_END).pack();
            buf.clear();
            hcommon::String2FlatBuffer(str_buf, buf);
            buffer_write.push_back(buf);
        }
        else
        {
            Log("SendSchedulData:���ʹ���");
        }
    }
    void SendFalseData(const hdata::his_data_type type, std::list<boost::beast::flat_buffer>& buffer_write)
    {
        std::string str_buf;
        boost::beast::flat_buffer buf;
        std::string now = hcommon::SimpleTime();
        std::string version = "0.1";
        std::string line_id;
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        ci.get_request_line_id_his(type, line_id);
        str_buf = hframe::frame_false_t(
            now, type, version, line_id, "01", hdata::ask_nack::E_ASK_ERROR, "request error").pack();
        hcommon::String2FlatBuffer(str_buf, buf);
        buffer_write.push_back(buf);
    }

    bool RepeatQuery(hdata::his_data_type type) 
    {
        // �����Ƿ��ظ���ѯ
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        boost::posix_time::ptime latest_update_time;
        bool repeat_query = false;
        ci.get_update_time_his(type, latest_update_time);
        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        boost::posix_time::millisec_posix_time_system_config::time_duration_type duration = now - latest_update_time;
        if (duration.total_milliseconds() <= 5000)
        {
            repeat_query = true;
        }
        return repeat_query;
    }

    void DealReportBlock(hdata::his_data_type type, hdata::statistics_report_type report_type, std::list<boost::beast::flat_buffer>& buffer_write)
    {
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        // �����ȴ�
        bool flag = false;
        bool flag_f = false;
        while (true)
        {
            // sleep first
            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(10));
            ci.get_done_his(type, flag);
            if (flag) // �������ˣ�flag:true(��ѯ)-->true(���ݷ���������)
            {
                // ���������������
                Log("����������ȷ���ظ�����������" + std::to_string(type));
                SendReportData(type, report_type, buffer_write);
                ci.set_done_his(type, false);
                ci.set_is_doing_his(type, false);
                break;
            }
            ci.get_do_false_his(type, flag_f);
            if (flag_f) 
            {
                Log("�������ݴ��󣬻ظ�����������" + std::to_string(type));
                SendFalseData(type, buffer_write);
                ci.set_do_false_his(type, false);
                ci.set_is_doing_his(type, false);
                break;
            }
        }
    }
    void DealScheduleBlock(hdata::his_data_type type, std::list<boost::beast::flat_buffer>& buffer_write)
    {
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        // �����ȴ�
        bool flag = false;
        bool flag_f = false;
        while (true)
        {
            // sleep first
            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(10));
            ci.get_done_his(type, flag);
            if (flag) // �������ˣ�flag:true(��ѯ)-->false(���ݷ�������)
            {
                // ���������������
                Log("�ظ�����������" + std::to_string(type));
                SendSchedulData(type, buffer_write);
                ci.set_done_his(type, false);
                ci.set_is_doing_his(type, false);
                break;
            }
            ci.get_do_false_his(type, flag_f);
            if (flag_f)
            {
                Log("�������ݴ��󣬻ظ�����������" + std::to_string(type));
                SendFalseData(type, buffer_write);
                ci.set_do_false_his(type, false);
                ci.set_is_doing_his(type, false);
                break;
            }
        }
    }

    void judge_is_doing(hdata::his_data_type type)
    {
        hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
        // �Ŷӵȴ�
        bool is_doing = false;
        while (true)
        {
            // sleep first
            ci.get_is_doing_his(type, is_doing);
            if (!is_doing)
            {
                break;
            }
            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(10));
        }
    }

} //namespace hserver