#ifndef COCC_MID_CONTAINER_HPP
#define COCC_MID_CONTAINER_HPP
#include <mutex>
#include <string>
#include <list>
#include <vector>
#include "cocc_his_data.h"
namespace mdata {
	class MidData {
	public:
		MidData()
		{
			report_start_flag_ = false;
		}
	public:
		void get_report_start_flag(bool& report_start_flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_start_flag = report_start_flag_;

		}
		void set_report_start_flag(bool report_start_flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_start_flag_ = report_start_flag;
		}
		void get_report_start_crc(std::string& report_start_crc)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_start_crc = report_start_crc_;

		}
		void set_report_start_crc(std::string report_start_crc)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_start_crc_ = report_start_crc;
		}
		void push_mid_string_data(std::string data) 
		{
			std::lock_guard<std::mutex> guard(mutex_);
			mid_string_data_.push_back(data);
		}
		void get_mid_string_data(std::string& data) 
		{
			std::lock_guard<std::mutex> guard(mutex_);
			for (std::list<std::string>::const_iterator iter = mid_string_data_.begin();
				iter != mid_string_data_.end(); ++iter)
			{
				data = data + *iter;
			}
			mid_string_data_.clear(); // 清空数据
		}
	private:
		std::mutex mutex_;  // 数据互斥锁
		bool report_start_flag_; // 推送开始标志
		std::string  report_start_crc_; // 推送开始CRC校验码
		std::list<std::string> mid_string_data_; // 中间数据字符串
	};

	class MidContainer 
	{
	public:
		MidContainer()
		{

		}
	public:
		// report_group_running
		void get_report_group_running(std::list<hdata::ReportGroupRunning>& report_group_running)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_running = report_group_running_;
		}
		void push_report_group_running(hdata::ReportGroupRunning report_group_running_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_running_.push_back(report_group_running_item);
		}
		void clear_report_group_running()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_running_.clear();
		}
		// report_driver_distance
		void get_report_driver_distance(std::list<hdata::ReportDriverDistance>& report_driver_distance)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_driver_distance = report_driver_distance_;
		}
		void push_report_driver_distance(hdata::ReportDriverDistance report_driver_distance_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_driver_distance_.push_back(report_driver_distance_item);
		}
		void clear_report_driver_distance()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_driver_distance_.clear();
		}
		// report_dispatcher
		void get_report_dispatcher(std::list<hdata::ReportDisPatcher>& report_dispatcher)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_dispatcher = report_dispatcher_;
		}
		void push_report_dispatcher(hdata::ReportDisPatcher report_dispatcher_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_dispatcher_.push_back(report_dispatcher_item);
		}
		void clear_report_dispatcher()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_dispatcher_.clear();
		}
		// report_group_bak
		void get_report_group_bak(std::list<hdata::ReportGroupBak>& report_group_bak)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_bak = report_group_bak_;
		}
		void push_report_group_bak(hdata::ReportGroupBak report_group_bak_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_bak_.push_back(report_group_bak_item);
		}
		void clear_report_group_bak()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_bak_.clear();
		}
		// report_group_status
		void get_report_group_status(std::list<hdata::ReportGroupStatus>& report_group_status)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_status = report_group_status_;
		}
		void push_report_group_status(hdata::ReportGroupStatus report_group_status_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_status_.push_back(report_group_status_item);
		}
		void clear_report_group_status()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_status_.clear();
		}
		// report_action
		void get_report_action(std::list<hdata::ReportAction>& report_action)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_action = report_action_;
		}
		void push_report_action(hdata::ReportAction report_action_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_action_.push_back(report_action_item);
		}
		void clear_report_action()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_action_.clear();
		}
		// report_alarm
		void get_report_alarm(std::list<hdata::ReportAlarm>& report_alarm)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_alarm = report_alarm_;
		}
		void push_report_alarm(hdata::ReportAlarm report_alarm_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_alarm_.push_back(report_alarm_item);
		}
		void clear_report_alarm()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_alarm_.clear();
		}
		// schedual_inused
		void get_schedual_inused(std::list<hdata::ScheduleInused>& schedual_inused)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_inused = schedual_inused_;
		}
		void push_schedual_inused(hdata::ScheduleInused schedual_inused_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_inused_.push_back(schedual_inused_item);
		}
		void clear_schedual_inused()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_inused_.clear();
		}
		// schedual_actual
		void get_schedual_actual(std::list<hdata::SchedulActual>& schedual_actual)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_actual = schedual_actual_;
		}
		void push_schedual_actual(hdata::SchedulActual schedual_actual_item)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_actual_.push_back(schedual_actual_item);
		}
		void clear_schedual_actual()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_actual_.clear();
		}
	public:
		void set_mid_data_flag(hdata::his_data_type type, bool flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				report_group_running_f_.set_report_start_flag(flag);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				report_driver_distance_f_.set_report_start_flag(flag);
				break;
			case hdata::E_DISPATCHER_REPORT:
				report_dispatcher_f_.set_report_start_flag(flag);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				report_group_bak_f_.set_report_start_flag(flag);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				report_group_status_f_.set_report_start_flag(flag);
				break;
			case hdata::E_ACTION_REPORT:
				report_action_f_.set_report_start_flag(flag);
				break;
			case hdata::E_ALARM_REPORT:
				report_alarm_f_.set_report_start_flag(flag);
				break;
			case hdata::E_INUSED_SCHEDULE:
				schedual_inused_f_.set_report_start_flag(flag);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				schedual_actual_f_.set_report_start_flag(flag);
				break;
			default:
				break;
			}
		}
		void set_mid_data_crc(hdata::his_data_type type,std::string crc)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				report_group_running_f_.set_report_start_crc(crc);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				report_driver_distance_f_.set_report_start_crc(crc);
				break;
			case hdata::E_DISPATCHER_REPORT:
				report_dispatcher_f_.set_report_start_crc(crc);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				report_group_bak_f_.set_report_start_crc(crc);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				report_group_status_f_.set_report_start_crc(crc);
				break;
			case hdata::E_ACTION_REPORT:
				report_action_f_.set_report_start_crc(crc);
				break;
			case hdata::E_ALARM_REPORT:
				report_alarm_f_.set_report_start_crc(crc);
				break;
			case hdata::E_INUSED_SCHEDULE:
				schedual_inused_f_.set_report_start_crc(crc);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				schedual_actual_f_.set_report_start_crc(crc);
				break;
			default:
				break;
			}
		}
		void get_mid_data_flag(hdata::his_data_type type, bool& flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				report_group_running_f_.get_report_start_flag(flag);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				report_driver_distance_f_.get_report_start_flag(flag);
				break;
			case hdata::E_DISPATCHER_REPORT:
				report_dispatcher_f_.get_report_start_flag(flag);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				report_group_bak_f_.get_report_start_flag(flag);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				report_group_status_f_.get_report_start_flag(flag);
				break;
			case hdata::E_ACTION_REPORT:
				report_action_f_.get_report_start_flag(flag);
				break;
			case hdata::E_ALARM_REPORT:
				report_alarm_f_.get_report_start_flag(flag);
				break;
			case hdata::E_INUSED_SCHEDULE:
				schedual_inused_f_.get_report_start_flag(flag);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				schedual_actual_f_.get_report_start_flag(flag);
				break;
			default:
				break;
			}
		}
		void get_mid_data_crc(hdata::his_data_type type, std::string& crc)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				report_group_running_f_.get_report_start_crc(crc);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				report_driver_distance_f_.get_report_start_crc(crc);
				break;
			case hdata::E_DISPATCHER_REPORT:
				report_dispatcher_f_.get_report_start_crc(crc);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				report_group_bak_f_.get_report_start_crc(crc);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				report_group_status_f_.get_report_start_crc(crc);
				break;
			case hdata::E_ACTION_REPORT:
				report_action_f_.get_report_start_crc(crc);
				break;
			case hdata::E_ALARM_REPORT:
				report_alarm_f_.get_report_start_crc(crc);
				break;
			case hdata::E_INUSED_SCHEDULE:
				schedual_inused_f_.get_report_start_crc(crc);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				schedual_actual_f_.get_report_start_crc(crc);
				break;
			default:
				break;
			}
		}
		void push_mid_data_string(hdata::his_data_type type, std::string item_data)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				report_group_running_f_.push_mid_string_data(item_data);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				report_driver_distance_f_.push_mid_string_data(item_data);
				break;
			case hdata::E_DISPATCHER_REPORT:
				report_dispatcher_f_.push_mid_string_data(item_data);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				report_group_bak_f_.push_mid_string_data(item_data);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				report_group_status_f_.push_mid_string_data(item_data);
				break;
			case hdata::E_ACTION_REPORT:
				report_action_f_.push_mid_string_data(item_data);
				break;
			case hdata::E_ALARM_REPORT:
				report_alarm_f_.push_mid_string_data(item_data);
				break;
			case hdata::E_INUSED_SCHEDULE:
				schedual_inused_f_.push_mid_string_data(item_data);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				schedual_actual_f_.push_mid_string_data(item_data);
				break;
			default:
				break;
			}
		}
		void get_mid_data_string(hdata::his_data_type type, std::string& all_data)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				report_group_running_f_.get_mid_string_data(all_data);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				report_driver_distance_f_.get_mid_string_data(all_data);
				break;
			case hdata::E_DISPATCHER_REPORT:
				report_dispatcher_f_.get_mid_string_data(all_data);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				report_group_bak_f_.get_mid_string_data(all_data);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				report_group_status_f_.get_mid_string_data(all_data);
				break;
			case hdata::E_ACTION_REPORT:
				report_action_f_.get_mid_string_data(all_data);
				break;
			case hdata::E_ALARM_REPORT:
				report_alarm_f_.get_mid_string_data(all_data);
				break;
			case hdata::E_INUSED_SCHEDULE:
				schedual_inused_f_.get_mid_string_data(all_data);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				schedual_actual_f_.get_mid_string_data(all_data);
				break;
			default:
				break;
			}
		}
	private:
		std::mutex mutex_;  // 数据互斥锁
		std::list<hdata::ReportGroupRunning> report_group_running_;
		std::list<hdata::ReportDriverDistance> report_driver_distance_;
		std::list<hdata::ReportDisPatcher> report_dispatcher_;
		std::list<hdata::ReportGroupBak> report_group_bak_;
		std::list<hdata::ReportGroupStatus> report_group_status_;
		std::list<hdata::ReportAction> report_action_;
		std::list<hdata::ReportAlarm> report_alarm_;
		std::list<hdata::ScheduleInused> schedual_inused_;
		std::list<hdata::SchedulActual> schedual_actual_;
	private:
		mdata::MidData report_group_running_f_;
		mdata::MidData report_driver_distance_f_;
		mdata::MidData report_dispatcher_f_;
		mdata::MidData report_group_bak_f_;
		mdata::MidData report_group_status_f_;
		mdata::MidData report_action_f_;
		mdata::MidData report_alarm_f_;
		mdata::MidData schedual_inused_f_;
		mdata::MidData schedual_actual_f_;
	};
} 
#endif
