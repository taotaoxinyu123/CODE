#ifndef COCC_HIS_IMP_H
#define COCC_HIS_IMP_H
#include <mutex>
#include <thread>
#include "boost/serialization/singleton.hpp"
#include "cocc_logger.h"
#include "cocc_his_container.hpp"
#include "cocc_config_container.hpp"
#include "cocc_mid_container.hpp"
namespace hdata {
	class CoccHisImp
	{
	public:
		CoccHisImp();
		~CoccHisImp();
	public:  // API 
		int start();
	
	public:  // 配置数据API
		hconfig::Config config();
	public: // 中间容器数据API
		// report_group_running
		void get_report_group_running_impl(std::list<hdata::ReportGroupRunning>& report_group_running);
		void push_report_group_running_impl(hdata::ReportGroupRunning report_group_running_item);
		void clear_report_group_running_impl();
		// report_driver_distance
		void get_report_driver_distance_impl(std::list<hdata::ReportDriverDistance>& report_driver_distance);
		void push_report_driver_distance_impl(hdata::ReportDriverDistance report_driver_distance_item);
		void clear_report_driver_distance_impl();
		// report_dispatcher
		void get_report_dispatcher_impl(std::list<hdata::ReportDisPatcher>& report_dispatcher);
		void push_report_dispatcher_impl(hdata::ReportDisPatcher report_dispatcher_item);
		void clear_report_dispatcher_impl();
		// report_group_bak
		void get_report_group_bak_impl(std::list<hdata::ReportGroupBak>& report_group_bak);
		void push_report_group_bak_impl(hdata::ReportGroupBak report_group_bak_item);
		void clear_report_group_bak_impl();
		// report_group_status
		void get_report_group_status_impl(std::list<hdata::ReportGroupStatus>& report_group_status);
		void push_report_group_status_impl(hdata::ReportGroupStatus report_group_status_item);
		void clear_report_group_status_impl();
		// report_action
		void get_report_action_impl(std::list<hdata::ReportAction>& report_action);
		void push_report_action_impl(hdata::ReportAction report_action_item);
		void clear_report_action_impl();
		// report_alarm
		void get_report_alarm_impl(std::list<hdata::ReportAlarm>& report_alarm);
		void push_report_alarm_impl(hdata::ReportAlarm report_alarm_item);
		void clear_report_alarm_impl();
		// schedual_inused
		void get_schedual_inused_impl(std::list<hdata::ScheduleInused>& schedual_inused);
		void push_schedual_inused_impl(hdata::ScheduleInused schedual_inused_item);
		void clear_schedual_inused_impl();
		// schedual_actual
		void get_schedual_actual_impl(std::list<hdata::SchedulActual>& schedual_actual);
		void push_schedual_actual_impl(hdata::SchedulActual schedual_actual_item);
		void clear_schedual_actual_impl();
		// flag and crc
		void set_mid_data_flag_impl(hdata::his_data_type type, bool flag);
		void set_mid_data_crc_impl(hdata::his_data_type type, std::string crc);
		void get_mid_data_flag_impl(hdata::his_data_type type, bool& flag);
		void get_mid_data_crc_impl(hdata::his_data_type type, std::string& crc);
		// data string
		void push_mid_data_string_impl(hdata::his_data_type type, std::string item_data);
		void get_mid_data_string_impl(hdata::his_data_type type, std::string& all_data);
	public: // 容器数据API
		// report_group_running
		void get_report_group_running_his(std::list<hdata::ReportGroupRunning>& report_group_running);
		void set_report_group_running_his(std::list<hdata::ReportGroupRunning> report_group_running);
		void clear_report_group_running_his();
		// report_driver_distance
		void get_report_driver_distance_his(std::list<hdata::ReportDriverDistance>& report_driver_distance);
		void set_report_driver_distance_his(std::list<hdata::ReportDriverDistance> report_driver_distance);
		void clear_report_driver_distance_his();
		// report_dispatcher
		void get_report_dispatcher_his(std::list<hdata::ReportDisPatcher>& report_dispatcher);
		void set_report_dispatcher_his(std::list<hdata::ReportDisPatcher> report_dispatcher);
		void clear_report_dispatcher_his();
		// report_group_bak
		void get_report_group_bak_his(std::list<hdata::ReportGroupBak>& report_group_bak);
		void set_report_group_bak_his(std::list<hdata::ReportGroupBak> report_group_bak);
		void clear_report_group_bak_his();
		// report_group_status
		void get_report_group_status_his(std::list<hdata::ReportGroupStatus>& report_group_status);
		void set_report_group_status_his(std::list<hdata::ReportGroupStatus> report_group_status);
		void clear_report_group_status_his();
		// report_action
		void get_report_action_his(std::list<hdata::ReportAction>& report_action);
		void set_report_action_his(std::list<hdata::ReportAction> report_action);
		void clear_report_action_his();
		// report_alarm
		void get_report_alarm_his(std::list<hdata::ReportAlarm>& report_alarm);
		void set_report_alarm_his(std::list<hdata::ReportAlarm> report_alarm);
		void clear_report_alarm_his();
		// schedual_inused
		void get_schedual_inused_his(std::list<hdata::ScheduleInused>& schedual_inused);
		void set_schedual_inused_his(std::list<hdata::ScheduleInused> schedual_inused);
		void clear_schedual_inused_his();
		// schedual_actual
		void get_schedual_actual_his(std::list<hdata::SchedulActual>& schedual_actual);
		void set_schedual_actual_his(std::list<hdata::SchedulActual> schedual_actual);
		void clear_schedual_actual_his();

		// request_tunnel
		void get_request_group_running_tunnel_his(bool& flag, std::string& line_id);
		void set_request_group_running_tunnel_his(bool flag, std::string line_id);
		void get_request_driver_distance_tunnel_his(bool& flag, std::string& line_id);
		void set_request_driver_distance_tunnel_his(bool flag, std::string line_id);
		void get_request_dispatcher_tunnel_his(bool& flag, std::string& line_id);
		void set_request_dispatcher_tunnel_his(bool flag, std::string line_id);
		void get_request_group_bak_tunnel_his(bool& flag, std::string& line_id);
		void set_request_group_bak_tunnel_his(bool flag, std::string line_id);
		void get_request_group_status_tunnel_his(bool& flag, std::string& line_id);
		void set_request_group_status_tunnel_his(bool flag, std::string line_id);
		void get_request_action_tunnel_his(bool& flag, std::string& line_id, std::string& start_time, std::string& end_time);
		void set_request_action_tunnel_his(bool flag, std::string line_id, std::string start_time, std::string end_time);
		void get_request_alarm_tunnel_his(bool& flag, std::string& line_id, std::string& start_time, std::string& end_time);
		void set_request_alarm_tunnel_his(bool flag, std::string line_id, std::string start_time, std::string end_time);
		void get_request_schedual_inused_tunnel_his(bool& flag, std::string& line_id, std::string& date);
		void set_request_schedual_inused_tunnel_his(bool flag, std::string& line_id, std::string& date);
		void get_request_schedual_actual_tunnel_his(bool& flag, std::string& line_id, std::string& date);
		void set_request_schedual_actual_tunnel_his(bool flag, std::string& line_id, std::string& date);
	public:
		void set_request_flag_his(hdata::his_data_type type, bool flag);
		void get_request_flag_his(hdata::his_data_type type, bool& flag);
		void set_request_line_id_his(hdata::his_data_type type, std::string line_id);
		void get_request_line_id_his(hdata::his_data_type type, std::string& line_id);
		void set_is_doing_his(hdata::his_data_type type, bool flag);
		void get_is_doing_his(hdata::his_data_type type, bool& flag);
		void set_done_his(hdata::his_data_type type, bool flag);
		void get_done_his(hdata::his_data_type type, bool& flag);
		void set_do_false_his(hdata::his_data_type type, bool flag);
		void get_do_false_his(hdata::his_data_type type, bool& flag);
	public:
		void set_update_time_his(hdata::his_data_type type, boost::posix_time::ptime time);
		void get_update_time_his(hdata::his_data_type type, boost::posix_time::ptime& time);
	public:
		hlogger::Logger& logger() { return logger_; }
	private:
		hdata::DataContainer data_container_;  // 容器数据
		hconfig::ConfigContainer config_container_; // 配置数据
		mdata::MidContainer mid_container_; // 中间容器数据
		hlogger::Logger logger_;  // 日志对象
	};

	typedef boost::serialization::singleton<CoccHisImp> singleton_cocchis_impl;  // 单例
} // end namespace
#endif