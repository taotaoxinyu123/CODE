#include "cocc_database.h"
#include "cocc_his_impl.h"
#include "cocc_frame.hpp"
#include "../OperateDatabase/con_api.h"

namespace hdatabase {
	// 记录日志
	static void Log(const std::string& message)
	{
		hdata::singleton_cocchis_impl::get_mutable_instance().logger().Log(message);
	}
	class InsertTime 
	{
	public:
		boost::posix_time::ptime report_group_running_t;
		boost::posix_time::ptime report_driver_distance_t;
		boost::posix_time::ptime report_dispatcher_t;
		boost::posix_time::ptime report_group_bak_t;
		boost::posix_time::ptime report_group_status_t;
		boost::posix_time::ptime report_action_t;
		boost::posix_time::ptime report_alarm_t;
		boost::posix_time::ptime schedual_inused_t;
		boost::posix_time::ptime schedual_actual_t;
	};

	// 初始化
	void init_insert_time(InsertTime& insert_time)
	{
		hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
		ci.get_update_time_his(hdata::his_data_type::E_GROUP_RUNNING_REPORT, insert_time.report_group_running_t);
		ci.get_update_time_his(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, insert_time.report_driver_distance_t);
		ci.get_update_time_his(hdata::his_data_type::E_DISPATCHER_REPORT, insert_time.report_dispatcher_t);
		ci.get_update_time_his(hdata::his_data_type::E_GROUP_BAK_REPORT, insert_time.report_group_bak_t);
		ci.get_update_time_his(hdata::his_data_type::E_GROUP_STATUS_REPORT, insert_time.report_group_status_t);
		ci.get_update_time_his(hdata::his_data_type::E_ACTION_REPORT, insert_time.report_action_t);
		ci.get_update_time_his(hdata::his_data_type::E_ALARM_REPORT, insert_time.report_alarm_t);
		ci.get_update_time_his(hdata::his_data_type::E_INUSED_SCHEDULE, insert_time.schedual_inused_t);
		ci.get_update_time_his(hdata::his_data_type::E_HISTORY_SCHEDULE, insert_time.schedual_actual_t);
	}
	void do_insert_data() 
	{
		InsertTime pre_insert_time;
		init_insert_time(pre_insert_time);
		while (true)
		{
			// sleep 1000ms
			InsertTime sub_insert_time;
			std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1000));
			hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
			std::list<std::string> transfer_lst;
			std::string str_buf;
			// 车组运行里程报告
			ci.get_update_time_his(hdata::his_data_type::E_GROUP_RUNNING_REPORT, sub_insert_time.report_group_running_t);
			if (sub_insert_time.report_group_running_t != pre_insert_time.report_group_running_t) 
			{
				Log("插入车组运行里程报告数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::ReportGroupRunning> report_group_running;
				ci.get_report_group_running_his(report_group_running);
				std::list<hdata::ReportGroupRunning>::const_iterator iter;
				for (iter = report_group_running.begin(); iter != report_group_running.end(); ++iter)
				{
					str_buf = hframe::frame_running_group_report(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->group_running_data).pack();
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_GROUP_RUNNING_REPORT, transfer_lst);
				if (0 != err) 
				{
					Log("插入车组运行里程报告数据到数据库出错");
				}
				pre_insert_time.report_group_running_t = sub_insert_time.report_group_running_t;
			}
			// 司机驾驶里程报告
			ci.get_update_time_his(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, sub_insert_time.report_driver_distance_t);
			if (sub_insert_time.report_driver_distance_t != pre_insert_time.report_driver_distance_t)
			{
				Log("插入车司机驾驶里程报告数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::ReportDriverDistance> report_driver_distance;
				ci.get_report_driver_distance_his(report_driver_distance);
				std::list<hdata::ReportDriverDistance>::const_iterator iter;
				for (iter = report_driver_distance.begin(); iter != report_driver_distance.end(); ++iter)
				{
					str_buf = hframe::frame_driver_distance_report(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->driver_distance_data).pack();
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_DRIVER_DISTANCE_REPORT, transfer_lst);
				if (0 != err)
				{
					Log("插入车司机驾驶里程报告数据到数据库出错");
				}
				pre_insert_time.report_driver_distance_t = sub_insert_time.report_driver_distance_t;
			}
			// 调度日志报告
			ci.get_update_time_his(hdata::his_data_type::E_DISPATCHER_REPORT, sub_insert_time.report_dispatcher_t);
			if (sub_insert_time.report_dispatcher_t != pre_insert_time.report_dispatcher_t)
			{
				Log("插入调度日志报告数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::ReportDisPatcher> report_dispatcher_t;
				ci.get_report_dispatcher_his(report_dispatcher_t);
				std::list<hdata::ReportDisPatcher>::const_iterator iter;
				for (iter = report_dispatcher_t.begin(); iter != report_dispatcher_t.end(); ++iter)
				{
					str_buf = hframe::frame_dispatcher_report(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->dispatcher_data).pack();
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_DISPATCHER_REPORT, transfer_lst);
				if (0 != err)
				{
					Log("插入调度日志报告数据到数据库出错");
				}
				pre_insert_time.report_dispatcher_t = sub_insert_time.report_dispatcher_t;
			}
			// 存备车报告
			ci.get_update_time_his(hdata::his_data_type::E_GROUP_BAK_REPORT, sub_insert_time.report_group_bak_t);
			if (sub_insert_time.report_group_bak_t != pre_insert_time.report_group_bak_t)
			{
				Log("插入存备车报告数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::ReportGroupBak> report_group_bak;
				ci.get_report_group_bak_his(report_group_bak);
				std::list<hdata::ReportGroupBak>::const_iterator iter;
				for (iter = report_group_bak.begin(); iter != report_group_bak.end(); ++iter)
				{
					str_buf = hframe::framegroup_bak_report(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->group_bak_data).pack();
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_GROUP_BAK_REPORT, transfer_lst);
				if (0 != err)
				{
					Log("插入存备车报告数据到数据库出错");
				}
				pre_insert_time.report_group_bak_t = sub_insert_time.report_group_bak_t;
			}
			// 列车整备状态报告
			ci.get_update_time_his(hdata::his_data_type::E_GROUP_STATUS_REPORT, sub_insert_time.report_group_status_t);
			if (sub_insert_time.report_group_status_t != pre_insert_time.report_group_status_t)
			{
				Log("插入列车整备状态报告数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::ReportGroupStatus> report_group_status;
				ci.get_report_group_status_his(report_group_status);
				std::list<hdata::ReportGroupStatus>::const_iterator iter;
				for (iter = report_group_status.begin(); iter != report_group_status.end(); ++iter)
				{
					str_buf = hframe::frame_group_status_report(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->group_status_data).pack();
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_GROUP_STATUS_REPORT, transfer_lst);
				if (0 != err)
				{
					Log("插入列车整备状态报告数据到数据库出错");
				}
				pre_insert_time.report_group_status_t = sub_insert_time.report_group_status_t;
			}
			// 操作命令消息
			ci.get_update_time_his(hdata::his_data_type::E_ACTION_REPORT, sub_insert_time.report_action_t);
			if (sub_insert_time.report_action_t != pre_insert_time.report_action_t)
			{
				Log("插入操作命令消息数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::ReportAction> report_action;
				ci.get_report_action_his(report_action);
				std::list<hdata::ReportAction>::const_iterator iter;
				for (iter = report_action.begin(); iter != report_action.end(); ++iter)
				{
					str_buf = hframe::frame_action_report(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->action_data).pack();
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_ACTION_REPORT, transfer_lst);
				if (0 != err)
				{
					Log("插入操作命令消息数据到数据库出错");
				}
				pre_insert_time.report_action_t = sub_insert_time.report_action_t;
			}
			// 报警消息
			ci.get_update_time_his(hdata::his_data_type::E_ALARM_REPORT , sub_insert_time.report_alarm_t);
			if (sub_insert_time.report_alarm_t != pre_insert_time.report_alarm_t)
			{
				Log("插入车报警消息数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::ReportAlarm> report_alarm;
				ci.get_report_alarm_his(report_alarm);
				std::list<hdata::ReportAlarm>::const_iterator iter;
				for (iter = report_alarm.begin(); iter != report_alarm.end(); ++iter)
				{
					str_buf = hframe::frame_alarm_report(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->report_id, iter->total_message, iter->message_sequence, iter->count, iter->alarm_data).pack();;
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_ALARM_REPORT, transfer_lst);
				if (0 != err)
				{
					Log("插入车报警消息数据到数据库出错");
				}
				pre_insert_time.report_alarm_t = sub_insert_time.report_alarm_t;
			}
			// 计划列车运行图
			ci.get_update_time_his(hdata::his_data_type::E_INUSED_SCHEDULE, sub_insert_time.schedual_inused_t);
			if (sub_insert_time.schedual_inused_t != pre_insert_time.schedual_inused_t)
			{
				Log("插入计划列车运行图数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::ScheduleInused> schedual_inused;
				ci.get_schedual_inused_his(schedual_inused);
				std::list<hdata::ScheduleInused>::const_iterator iter;
				for (iter = schedual_inused.begin(); iter != schedual_inused.end(); ++iter)
				{
					str_buf = hframe::frame_schedul_inused(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->date, iter->sub_id, iter->train_id, iter->trip_cnt, iter->inused_data).pack();
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_INUSED_SCHEDULE, transfer_lst);
				if (0 != err)
				{
					Log("插入计划列车运行图数据到数据库出错");
				}
				pre_insert_time.schedual_inused_t = sub_insert_time.schedual_inused_t;
			}
			// 实际列车运行图
			ci.get_update_time_his(hdata::his_data_type::E_HISTORY_SCHEDULE, sub_insert_time.schedual_actual_t);
			if (sub_insert_time.schedual_actual_t != pre_insert_time.schedual_actual_t)
			{
				Log("插入车组运行里程报告数据到数据库");
				transfer_lst.clear();
				str_buf.clear();
				std::list<hdata::SchedulActual> schedual_actual;
				ci.get_schedual_actual_his(schedual_actual);
				std::list<hdata::SchedulActual>::const_iterator iter;
				for (iter = schedual_actual.begin(); iter != schedual_actual.end(); ++iter)
				{
					str_buf = hframe::frame_schedul_actual(
						iter->time, iter->msg_id, iter->version, iter->line_id, iter->date, iter->sub_id, iter->pvid, iter->station_cnt, iter->actual_data).pack();
					transfer_lst.push_back(str_buf);
				}
				long err = CON_API_TRANSFER(hdata::his_data_type::E_HISTORY_SCHEDULE, transfer_lst);
				if (0 != err)
				{
					Log("插入车组运行里程报告数据到数据库出错");
				}
				pre_insert_time.schedual_actual_t = sub_insert_time.schedual_actual_t;
			}

		} // while

	}
}

void start_insert_database() 
{
	std::thread* database_thread = new std::thread(&hdatabase::do_insert_data);
}