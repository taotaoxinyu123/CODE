#ifndef COCC_HIS_CONTAINER_HPP
#define COCC_HIS_CONTAINER_HPP
#include <mutex>
#include <string>
#include <list>
#include <vector>
#include "cocc_his_data.h"
#include "boost/date_time/posix_time/posix_time.hpp"
namespace hdata {
	// 业务更新时间:上一次最近更新时间
	class UTime {
	public:
		UTime()
		{
			update_report_group_running_ = boost::posix_time::second_clock::local_time();
			update_report_driver_distance_ = boost::posix_time::second_clock::local_time();
			update_report_dispatcher_ = boost::posix_time::second_clock::local_time();
			update_report_group_bak_ = boost::posix_time::second_clock::local_time();
			update_report_group_status_ = boost::posix_time::second_clock::local_time();
			update_report_action_ = boost::posix_time::second_clock::local_time();
			update_report_alarm_ = boost::posix_time::second_clock::local_time();
			update_schedual_inused_ = boost::posix_time::second_clock::local_time();
			update_schedual_actual_ = boost::posix_time::second_clock::local_time();
		}
	public:
		boost::posix_time::ptime update_report_group_running_; 
		boost::posix_time::ptime update_report_driver_distance_;
		boost::posix_time::ptime update_report_dispatcher_;
		boost::posix_time::ptime update_report_group_bak_;
		boost::posix_time::ptime update_report_group_status_;
		boost::posix_time::ptime update_report_action_;
		boost::posix_time::ptime update_report_alarm_;
		boost::posix_time::ptime update_schedual_inused_;
		boost::posix_time::ptime update_schedual_actual_;
	private:
		static const int kTimeout;  // 重新请求业务更新时间间隔
	};

	class RequestReport {
	public:
		RequestReport()
		{
			request_flag_ = false;
			is_doing_ = false;
			done_ = false;
		}
	public:
		void set(bool request_flag, std::string line_id) 
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag_ = request_flag;
			line_id_ = line_id;
		}
		void get(bool& request_flag, std::string& line_id) 
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag = request_flag_;
			line_id = line_id_;
		}
		void set_request_flag(bool request_flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag_ = request_flag;
		}
		bool get_request_flag() 
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return request_flag_;
		}
		void set_request_line_id(std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			line_id_ = line_id;
		}
		std::string get_request_line_id()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return line_id_;
		}
		void set_is_doing(bool is_doing)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			is_doing_ = is_doing;
		}
		bool get_is_doing()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return is_doing_;
		}
		void set_done(bool done)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			done_ = done;
		}
		bool get_done()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return done_;
		}
		void set_do_false(bool do_false)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			do_false_ = do_false;
		}
		bool get_do_false()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return do_false_;
		}
	private:
		std::mutex mutex_;  // 数据互斥锁
		bool request_flag_; // 请求数据标志
		std::string line_id_;
		bool is_doing_;	// 是否正在做？
		bool done_; // 是否做完？
		bool do_false_; // 数据错误
	};

	class RequestAction {
	public:
		RequestAction()
		{
			request_flag_ = false;
			is_doing_ = false;
			done_ = false;
		}
	public:
		void set(bool request_flag, std::string line_id, std::string start_time, std::string end_time)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag_ = request_flag;
			line_id_ = line_id;
			start_time_ = start_time;
			end_time_ = end_time;
		}
		void get(bool& request_flag, std::string& line_id, std::string& start_time, std::string& end_time)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag = request_flag_;
			line_id = line_id_;
			start_time = start_time_;
			end_time = end_time_;
		}
		void set_request_flag(bool request_flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag_ = request_flag;
		}
		bool get_request_flag()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return request_flag_;
		}
		void set_request_line_id(std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			line_id_ = line_id;
		}
		std::string get_request_line_id()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return line_id_;
		}
		void set_is_doing(bool is_doing)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			is_doing_ = is_doing;
		}
		bool get_is_doing()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return is_doing_;
		}
		void set_done(bool done)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			done_ = done;
		}
		bool get_done()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return done_;
		}
		void set_do_false(bool do_false)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			do_false_ = do_false;
		}
		bool get_do_false()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return do_false_;
		}
	private:
		std::mutex mutex_;  // 数据互斥锁
		bool request_flag_;
		std::string line_id_;
		std::string start_time_;
		std::string end_time_;
		bool is_doing_;	
		bool done_;
		bool do_false_; 
	};

	class RequestSchedual {
	public:
		RequestSchedual()
		{
			request_flag_ = false;
			is_doing_ = false;
			done_ = false;
		}
	public:
		void set(bool request_flag, std::string line_id, std::string date)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag_ = request_flag;
			line_id_ = line_id;
			date_ = date;
		}
		void get(bool& request_flag, std::string& line_id, std::string& date)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag = request_flag_;
			line_id = line_id_;
			date = date_;
		}
		void set_request_flag(bool request_flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_flag_ = request_flag;
		}
		bool get_request_flag()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return request_flag_;
		}
		void set_request_line_id(std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			line_id_ = line_id;
		}
		std::string get_request_line_id()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return line_id_;
		}
		void set_is_doing(bool is_doing)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			is_doing_ = is_doing;
		}
		bool get_is_doing()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return is_doing_;
		}
		void set_done(bool done)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			done_ = done;
		}
		bool get_done()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return done_;
		}
		void set_do_false(bool do_false)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			do_false_ = do_false;
		}
		bool get_do_false()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return do_false_;
		}
	private:
		std::mutex mutex_;  // 数据互斥锁
		bool request_flag_;
		std::string line_id_;
		std::string date_;
		bool is_doing_;	
		bool done_;
		bool do_false_; 
	};

	class DataContainer 
	{
	public:
		DataContainer()
		{
		}
	public:
		// report_group_running
		void get_report_group_running(std::list<hdata::ReportGroupRunning>& report_group_running)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_running = report_group_running_;
		}
		void set_report_group_running(std::list<hdata::ReportGroupRunning> report_group_running)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_running_ = report_group_running;
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
		void set_report_driver_distance(std::list<hdata::ReportDriverDistance> report_driver_distance)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_driver_distance_ = report_driver_distance;
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
		void set_report_dispatcher(std::list<hdata::ReportDisPatcher> report_dispatcher)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_dispatcher_ = report_dispatcher;
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
		void set_report_group_bak(std::list<hdata::ReportGroupBak> report_group_bak)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_bak_ = report_group_bak;
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
		void set_report_group_status(std::list<hdata::ReportGroupStatus> report_group_status)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_group_status_ = report_group_status;
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
		void set_report_action(std::list<hdata::ReportAction> report_action)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_action_ = report_action;
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
		void set_report_alarm(std::list<hdata::ReportAlarm> report_alarm)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			report_alarm_ = report_alarm;
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
		void set_schedual_inused(std::list<hdata::ScheduleInused> schedual_inused)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_inused_ = schedual_inused;
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
		void set_schedual_actual(std::list<hdata::SchedulActual> schedual_actual)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_actual_ = schedual_actual;
		}
		void clear_schedual_actual()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			schedual_actual_.clear();
		}
	public:
		void set_update_time(hdata::his_data_type type, boost::posix_time::ptime time)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type) 
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				update_time_.update_report_group_running_ = time;
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				update_time_.update_report_driver_distance_ = time;
				break;
			case hdata::E_DISPATCHER_REPORT:
				update_time_.update_report_dispatcher_ = time;
				break;
			case hdata::E_GROUP_BAK_REPORT:
				update_time_.update_report_group_bak_ = time;
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				update_time_.update_report_group_status_ = time;
				break;
			case hdata::E_ACTION_REPORT:
				update_time_.update_report_action_ = time;
				break;
			case hdata::E_ALARM_REPORT:
				update_time_.update_report_alarm_ = time;
				break;
			case hdata::E_INUSED_SCHEDULE:
				update_time_.update_schedual_inused_ = time;
				break;
			case hdata::E_HISTORY_SCHEDULE:
				update_time_.update_schedual_actual_ = time;
				break;
			default:
				break;
			}
		}
		void get_update_time(hdata::his_data_type type, boost::posix_time::ptime& time)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				time = update_time_.update_report_group_running_;
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				time = update_time_.update_report_driver_distance_;
				break;
			case hdata::E_DISPATCHER_REPORT:
				time = update_time_.update_report_dispatcher_;
				break;
			case hdata::E_GROUP_BAK_REPORT:
				time = update_time_.update_report_group_bak_;
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				time = update_time_.update_report_group_status_;
				break;
			case hdata::E_ACTION_REPORT:
				time = update_time_.update_report_action_;
				break;
			case hdata::E_ALARM_REPORT:
				time = update_time_.update_report_alarm_;
				break;
			case hdata::E_INUSED_SCHEDULE:
				time = update_time_.update_schedual_inused_;
				break;
			case hdata::E_HISTORY_SCHEDULE:
				time = update_time_.update_schedual_actual_;
				break;
			default:
				break;
			}
		}
	public:
		void get_request_group_running_tunnel(bool& request_group_running_tunnel, std::string& line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_group_running_tunnel_.get(request_group_running_tunnel, line_id);
		}
		void set_request_group_running_tunnel(bool request_group_running_tunnel, std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_group_running_tunnel_.set(request_group_running_tunnel, line_id);
		}
		void get_request_driver_distance_tunnel(bool& request_group_running_tunnel, std::string& line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_driver_distance_tunnel_.get(request_group_running_tunnel, line_id);
		}
		void set_request_driver_distance_tunnel(bool request_driver_distance_tunnel, std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_driver_distance_tunnel_.set(request_driver_distance_tunnel, line_id);
		}
		void get_request_dispatcher_tunnel(bool& request_group_running_tunnel, std::string& line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_dispatcher_tunnel_.get(request_group_running_tunnel, line_id);
		}
		void set_request_dispatcher_tunnel(bool request_dispatcher_tunnel, std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_dispatcher_tunnel_.set(request_dispatcher_tunnel, line_id);
		}
		void get_request_group_bak_tunnel(bool& request_group_running_tunnel, std::string& line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_group_bak_tunnel_.get(request_group_running_tunnel, line_id);
		}
		void set_request_group_bak_tunnel(bool request_group_bak_tunnel, std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_group_bak_tunnel_.set(request_group_bak_tunnel, line_id);
		}
		void get_request_group_status_tunnel(bool& request_group_running_tunnel, std::string& line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_group_status_tunnel_.get(request_group_running_tunnel, line_id);
		}
		void set_request_group_status_tunnel(bool request_group_status_tunnel, std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_group_status_tunnel_.set(request_group_status_tunnel, line_id);
		}
		void get_request_action_tunnel(bool& request_action_tunnel, std::string& line_id, std::string& start_time, std::string& end_time)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_action_tunnel_.get(request_action_tunnel, line_id, start_time, end_time);
		}
		void set_request_action_tunnel(bool request_action_tunnel, std::string line_id, std::string start_time, std::string end_time)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_action_tunnel_.set(request_action_tunnel, line_id, start_time, end_time);
		}
		void get_request_alarm_tunnel(bool& request_alram_tunnel, std::string& line_id, std::string& start_time, std::string& end_time)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_alarm_tunnel_.get(request_alram_tunnel, line_id, start_time, end_time);
		}
		void set_request_alarm_tunnel(bool request_alram_tunnel, std::string line_id, std::string start_time, std::string end_time)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_alarm_tunnel_.set(request_alram_tunnel, line_id, start_time, end_time);
		}
		void get_request_schedual_inused_tunnel(bool& request_schedual_inused_tunnel, std::string& line_id, std::string& date)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_schedual_inused_tunnel_.get(request_schedual_inused_tunnel, line_id, date);
		}
		void set_request_schedual_inused_tunnel(bool request_schedual_inused_tunnel, std::string line_id, std::string& date)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_schedual_inused_tunnel_.set(request_schedual_inused_tunnel, line_id, date);
		}
		void get_request_schedual_actual_tunnel(bool& request_schedual_actual_tunnel, std::string& line_id, std::string& date)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_schedual_actual_tunnel_.get(request_schedual_actual_tunnel, line_id, date);
		}
		void set_request_schedual_actual_tunnel(bool request_schedual_actual_tunnel, std::string& line_id, std::string& date)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			request_schedual_actual_tunnel_.set(request_schedual_actual_tunnel, line_id, date);
		}
	public: //switch
		void set_request_flag(hdata::his_data_type type, bool flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				request_group_running_tunnel_.set_request_flag(flag);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				request_driver_distance_tunnel_.set_request_flag(flag);
				break;
			case hdata::E_DISPATCHER_REPORT:
				request_dispatcher_tunnel_.set_request_flag(flag);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				request_group_bak_tunnel_.set_request_flag(flag);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				request_group_status_tunnel_.set_request_flag(flag);
				break;
			case hdata::E_ACTION_REPORT:
				request_action_tunnel_.set_request_flag(flag);
				break;
			case hdata::E_ALARM_REPORT:
				request_alarm_tunnel_.set_request_flag(flag);
				break;
			case hdata::E_INUSED_SCHEDULE:
				request_schedual_inused_tunnel_.set_request_flag(flag);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				request_schedual_actual_tunnel_.set_request_flag(flag);
				break;
			default:
				break;
			}
		}
		void get_request_flag(hdata::his_data_type type, bool& flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				flag = request_group_running_tunnel_.get_request_flag();
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				flag = request_driver_distance_tunnel_.get_request_flag();
				break;
			case hdata::E_DISPATCHER_REPORT:
				flag = request_dispatcher_tunnel_.get_request_flag();
				break;
			case hdata::E_GROUP_BAK_REPORT:
				flag = request_group_bak_tunnel_.get_request_flag();
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				flag = request_group_status_tunnel_.get_request_flag();
				break;
			case hdata::E_ACTION_REPORT:
				flag = request_action_tunnel_.get_request_flag();
				break;
			case hdata::E_ALARM_REPORT:
				flag = request_alarm_tunnel_.get_request_flag();
				break;
			case hdata::E_INUSED_SCHEDULE:
				flag = request_schedual_inused_tunnel_.get_request_flag();
				break;
			case hdata::E_HISTORY_SCHEDULE:
				flag = request_schedual_actual_tunnel_.get_request_flag();
				break;
			default:
				break;
			}
		}
		void set_request_line_id(hdata::his_data_type type, std::string line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				request_group_running_tunnel_.set_request_line_id(line_id);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				request_driver_distance_tunnel_.set_request_line_id(line_id);
				break;
			case hdata::E_DISPATCHER_REPORT:
				request_dispatcher_tunnel_.set_request_line_id(line_id);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				request_group_bak_tunnel_.set_request_line_id(line_id);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				request_group_status_tunnel_.set_request_line_id(line_id);
				break;
			case hdata::E_ACTION_REPORT:
				request_action_tunnel_.set_request_line_id(line_id);
				break;
			case hdata::E_ALARM_REPORT:
				request_alarm_tunnel_.set_request_line_id(line_id);
				break;
			case hdata::E_INUSED_SCHEDULE:
				request_schedual_inused_tunnel_.set_request_line_id(line_id);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				request_schedual_actual_tunnel_.set_request_line_id(line_id);
				break;
			default:
				break;
			}
		}
		void get_request_line_id(hdata::his_data_type type, std::string& line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				line_id = request_group_running_tunnel_.get_request_line_id();
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				line_id = request_driver_distance_tunnel_.get_request_line_id();
				break;
			case hdata::E_DISPATCHER_REPORT:
				line_id = request_dispatcher_tunnel_.get_request_line_id();
				break;
			case hdata::E_GROUP_BAK_REPORT:
				line_id = request_group_bak_tunnel_.get_request_line_id();
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				line_id = request_group_status_tunnel_.get_request_line_id();
				break;
			case hdata::E_ACTION_REPORT:
				line_id = request_action_tunnel_.get_request_line_id();
				break;
			case hdata::E_ALARM_REPORT:
				line_id = request_alarm_tunnel_.get_request_line_id();
				break;
			case hdata::E_INUSED_SCHEDULE:
				line_id = request_schedual_inused_tunnel_.get_request_line_id();
				break;
			case hdata::E_HISTORY_SCHEDULE:
				line_id = request_schedual_actual_tunnel_.get_request_line_id();
				break;
			default:
				break;
			}
		}
		void set_is_doing(hdata::his_data_type type, bool flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				request_group_running_tunnel_.set_is_doing(flag);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				request_driver_distance_tunnel_.set_is_doing(flag);
				break;
			case hdata::E_DISPATCHER_REPORT:
				request_dispatcher_tunnel_.set_is_doing(flag);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				request_group_bak_tunnel_.set_is_doing(flag);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				request_group_status_tunnel_.set_is_doing(flag);
				break;
			case hdata::E_ACTION_REPORT:
				request_action_tunnel_.set_is_doing(flag);
				break;
			case hdata::E_ALARM_REPORT:
				request_alarm_tunnel_.set_is_doing(flag);
				break;
			case hdata::E_INUSED_SCHEDULE:
				request_schedual_inused_tunnel_.set_is_doing(flag);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				request_schedual_actual_tunnel_.set_is_doing(flag);
				break;
			default:
				break;
			}
		}
		void get_is_doing(hdata::his_data_type type, bool& flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				flag = request_group_running_tunnel_.get_is_doing();
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				flag = request_driver_distance_tunnel_.get_is_doing();
				break;
			case hdata::E_DISPATCHER_REPORT:
				flag = request_dispatcher_tunnel_.get_is_doing();
				break;
			case hdata::E_GROUP_BAK_REPORT:
				flag = request_group_bak_tunnel_.get_is_doing();
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				flag = request_group_status_tunnel_.get_is_doing();
				break;
			case hdata::E_ACTION_REPORT:
				flag = request_action_tunnel_.get_is_doing();
				break;
			case hdata::E_ALARM_REPORT:
				flag = request_alarm_tunnel_.get_is_doing();
				break;
			case hdata::E_INUSED_SCHEDULE:
				flag = request_schedual_inused_tunnel_.get_is_doing();
				break;
			case hdata::E_HISTORY_SCHEDULE:
				flag = request_schedual_actual_tunnel_.get_is_doing();
				break;
			default:
				break;
			}
		}
		void set_done(hdata::his_data_type type, bool flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				request_group_running_tunnel_.set_done(flag);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				request_driver_distance_tunnel_.set_done(flag);
				break;
			case hdata::E_DISPATCHER_REPORT:
				request_dispatcher_tunnel_.set_done(flag);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				request_group_bak_tunnel_.set_done(flag);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				request_group_status_tunnel_.set_done(flag);
				break;
			case hdata::E_ACTION_REPORT:
				request_action_tunnel_.set_done(flag);
				break;
			case hdata::E_ALARM_REPORT:
				request_alarm_tunnel_.set_done(flag);
				break;
			case hdata::E_INUSED_SCHEDULE:
				request_schedual_inused_tunnel_.set_done(flag);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				request_schedual_actual_tunnel_.set_done(flag);
				break;
			default:
				break;
			}
		}
		void get_done(hdata::his_data_type type, bool& flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				flag = request_group_running_tunnel_.get_done();
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				flag = request_driver_distance_tunnel_.get_done();
				break;
			case hdata::E_DISPATCHER_REPORT:
				flag = request_dispatcher_tunnel_.get_done();
				break;
			case hdata::E_GROUP_BAK_REPORT:
				flag = request_group_bak_tunnel_.get_done();
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				flag = request_group_status_tunnel_.get_done();
				break;
			case hdata::E_ACTION_REPORT:
				flag = request_action_tunnel_.get_done();
				break;
			case hdata::E_ALARM_REPORT:
				flag = request_alarm_tunnel_.get_done();
				break;
			case hdata::E_INUSED_SCHEDULE:
				flag = request_schedual_inused_tunnel_.get_done();
				break;
			case hdata::E_HISTORY_SCHEDULE:
				flag = request_schedual_actual_tunnel_.get_done();
				break;
			default:
				break;
			}
		}
		void set_do_false(hdata::his_data_type type, bool flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				request_group_running_tunnel_.set_do_false(flag);
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				request_driver_distance_tunnel_.set_do_false(flag);
				break;
			case hdata::E_DISPATCHER_REPORT:
				request_dispatcher_tunnel_.set_do_false(flag);
				break;
			case hdata::E_GROUP_BAK_REPORT:
				request_group_bak_tunnel_.set_do_false(flag);
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				request_group_status_tunnel_.set_do_false(flag);
				break;
			case hdata::E_ACTION_REPORT:
				request_action_tunnel_.set_do_false(flag);
				break;
			case hdata::E_ALARM_REPORT:
				request_alarm_tunnel_.set_do_false(flag);
				break;
			case hdata::E_INUSED_SCHEDULE:
				request_schedual_inused_tunnel_.set_do_false(flag);
				break;
			case hdata::E_HISTORY_SCHEDULE:
				request_schedual_actual_tunnel_.set_do_false(flag);
				break;
			default:
				break;
			}
		}
		void get_do_false(hdata::his_data_type type, bool& flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			switch (type)
			{
			case hdata::E_GROUP_RUNNING_REPORT:
				flag = request_group_running_tunnel_.get_do_false();
				break;
			case hdata::E_DRIVER_DISTANCE_REPORT:
				flag = request_driver_distance_tunnel_.get_do_false();
				break;
			case hdata::E_DISPATCHER_REPORT:
				flag = request_dispatcher_tunnel_.get_do_false();
				break;
			case hdata::E_GROUP_BAK_REPORT:
				flag = request_group_bak_tunnel_.get_do_false();
				break;
			case hdata::E_GROUP_STATUS_REPORT:
				flag = request_group_status_tunnel_.get_do_false();
				break;
			case hdata::E_ACTION_REPORT:
				flag = request_action_tunnel_.get_do_false();
				break;
			case hdata::E_ALARM_REPORT:
				flag = request_alarm_tunnel_.get_do_false();
				break;
			case hdata::E_INUSED_SCHEDULE:
				flag = request_schedual_inused_tunnel_.get_do_false();
				break;
			case hdata::E_HISTORY_SCHEDULE:
				flag = request_schedual_actual_tunnel_.get_do_false();
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
		RequestReport request_group_running_tunnel_; // 请求组运行里程通道数据
		RequestReport request_driver_distance_tunnel_;
		RequestReport request_dispatcher_tunnel_;
		RequestReport request_group_bak_tunnel_;
		RequestReport request_group_status_tunnel_;
		RequestAction request_action_tunnel_;	// 请求事件通道数据
		RequestAction request_alarm_tunnel_;
		RequestSchedual request_schedual_inused_tunnel_; // 请求计划运行图通道数据
		RequestSchedual request_schedual_actual_tunnel_;
	private:
		UTime update_time_; // 上一次业务查询时间
	};
}
#endif