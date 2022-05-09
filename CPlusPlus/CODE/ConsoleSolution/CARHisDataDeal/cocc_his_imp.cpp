#include "cocc_his_impl.h"
#include "cocc_config_manager.hpp"
#include "cocc_error_code.h"
#include "cocc_upper_client_recv.h"
#include "cocc_upper_client_send.h"
#include "cocc_lower_server.h"
#include "cocc_database.h"

static void Log(const std::string& message)
{
	hdata::singleton_cocchis_impl::get_mutable_instance().logger().Log(message);
}

namespace hdata{
	CoccHisImp::CoccHisImp() : logger_("CARHisDataDeal")
	{

	}
	CoccHisImp::~CoccHisImp()
	{

	}
	int CoccHisImp::start() 
	{
		Log("CARHisDataDeal START");
		int error_code = COCC_SUCCESS;
		// 加载配置:读取xml，然后写入config内存
		hconfig::Config config;
		std::string message = hconfig::Load(config);
		if (!message.empty())
		{
			error_code = COCC_ERROR_CONFIG;
			logger_.Log(message);
			return error_code;
		}
		config_container_.set(config);
		// 启动upper的线程
		start_upper_client_recv();
		start_upper_client_send();
		// 启动lower的线程
		start_lower_server();
		// 启动insert database线程
		start_insert_database();
		return error_code;
	}
	// 配置数据API
	hconfig::Config CoccHisImp::config()
	{
		return config_container_.get();
	}
	// 中间容器数据API
	// report_group_running
	void CoccHisImp::get_report_group_running_impl(std::list<hdata::ReportGroupRunning>& report_group_running)
	{
		mid_container_.get_report_group_running(report_group_running);
	}
	void CoccHisImp::push_report_group_running_impl(hdata::ReportGroupRunning report_group_running_item)
	{
		mid_container_.push_report_group_running(report_group_running_item);
	}
	void CoccHisImp::clear_report_group_running_impl()
	{
		mid_container_.clear_report_group_running();
	}
	// report_driver_distance
	void CoccHisImp::get_report_driver_distance_impl(std::list<hdata::ReportDriverDistance>& report_driver_distance)
	{
		mid_container_.get_report_driver_distance(report_driver_distance);
	}
	void CoccHisImp::push_report_driver_distance_impl(hdata::ReportDriverDistance report_driver_distance_item)
	{
		mid_container_.push_report_driver_distance(report_driver_distance_item);
	}
	void CoccHisImp::clear_report_driver_distance_impl()
	{
		mid_container_.clear_report_driver_distance();
	}
	// report_dispatcher
	void CoccHisImp::get_report_dispatcher_impl(std::list<hdata::ReportDisPatcher>& report_dispatcher)
	{
		mid_container_.get_report_dispatcher(report_dispatcher);
	}
	void CoccHisImp::push_report_dispatcher_impl(hdata::ReportDisPatcher report_dispatcher_item)
	{
		mid_container_.push_report_dispatcher(report_dispatcher_item);
	}
	void CoccHisImp::clear_report_dispatcher_impl()
	{
		mid_container_.clear_report_dispatcher();
	}
	// report_group_bak
	void CoccHisImp::get_report_group_bak_impl(std::list<hdata::ReportGroupBak>& report_group_bak)
	{
		mid_container_.get_report_group_bak(report_group_bak);
	}
	void CoccHisImp::push_report_group_bak_impl(hdata::ReportGroupBak report_group_bak_item)
	{
		mid_container_.push_report_group_bak(report_group_bak_item);
	}
	void CoccHisImp::clear_report_group_bak_impl()
	{
		mid_container_.clear_report_group_bak();
	}
	// report_group_status
	void CoccHisImp::get_report_group_status_impl(std::list<hdata::ReportGroupStatus>& report_group_status)
	{
		mid_container_.get_report_group_status(report_group_status);
	}
	void CoccHisImp::push_report_group_status_impl(hdata::ReportGroupStatus report_group_status_item)
	{
		mid_container_.push_report_group_status(report_group_status_item);
	}
	void CoccHisImp::clear_report_group_status_impl()
	{
		mid_container_.clear_report_group_status();
	}
	// report_action
	void CoccHisImp::get_report_action_impl(std::list<hdata::ReportAction>& report_action)
	{
		mid_container_.get_report_action(report_action);
	}
	void CoccHisImp::push_report_action_impl(hdata::ReportAction report_action_item)
	{
		mid_container_.push_report_action(report_action_item);
	}
	void CoccHisImp::clear_report_action_impl()
	{
		mid_container_.clear_report_action();
	}
	// report_alarm
	void CoccHisImp::get_report_alarm_impl(std::list<hdata::ReportAlarm>& report_alarm)
	{
		mid_container_.get_report_alarm(report_alarm);
	}
	void CoccHisImp::push_report_alarm_impl(hdata::ReportAlarm report_alarm_item)
	{
		mid_container_.push_report_alarm(report_alarm_item);
	}
	void CoccHisImp::clear_report_alarm_impl()
	{
		mid_container_.clear_report_alarm();
	}
	// schedual_inused
	void CoccHisImp::get_schedual_inused_impl(std::list<hdata::ScheduleInused>& schedual_inused)
	{
		mid_container_.get_schedual_inused(schedual_inused);
	}
	void CoccHisImp::push_schedual_inused_impl(hdata::ScheduleInused schedual_inused_item)
	{
		mid_container_.push_schedual_inused(schedual_inused_item);
	}
	void CoccHisImp::clear_schedual_inused_impl()
	{
		mid_container_.clear_schedual_inused();
	}
	// schedual_actual
	void CoccHisImp::get_schedual_actual_impl(std::list<hdata::SchedulActual>& schedual_actual)
	{
		mid_container_.get_schedual_actual(schedual_actual);
	}
	void CoccHisImp::push_schedual_actual_impl(hdata::SchedulActual schedual_actual_item)
	{
		mid_container_.push_schedual_actual(schedual_actual_item);
	}
	void CoccHisImp::clear_schedual_actual_impl()
	{
		mid_container_.clear_schedual_actual();
	}
	// flag and crc
	void CoccHisImp::set_mid_data_flag_impl(hdata::his_data_type type, bool flag)
	{
		mid_container_.set_mid_data_flag(type, flag);
	}
	void CoccHisImp::set_mid_data_crc_impl(hdata::his_data_type type, std::string crc)
	{
		mid_container_.set_mid_data_crc(type, crc);
	}
	void CoccHisImp::get_mid_data_flag_impl(hdata::his_data_type type, bool& flag)
	{
		mid_container_.get_mid_data_flag(type, flag);
	}
	void CoccHisImp::get_mid_data_crc_impl(hdata::his_data_type type, std::string& crc)
	{
		mid_container_.get_mid_data_crc(type, crc);
	}
	void CoccHisImp::push_mid_data_string_impl(hdata::his_data_type type, std::string item_data)
	{
		mid_container_.push_mid_data_string(type, item_data);
	}
	void CoccHisImp::get_mid_data_string_impl(hdata::his_data_type type, std::string& all_data) 
	{
		mid_container_.get_mid_data_string(type, all_data);
	}
	// 容器数据API
	// report_group_running
	void CoccHisImp::get_report_group_running_his(std::list<hdata::ReportGroupRunning>& report_group_running)
	{
		data_container_.get_report_group_running(report_group_running);
	}
	void CoccHisImp::set_report_group_running_his(std::list<hdata::ReportGroupRunning> report_group_running) 
	{
		data_container_.set_report_group_running(report_group_running);
	}
	void CoccHisImp::clear_report_group_running_his()
	{
		data_container_.clear_report_group_running();
	}
	// report_driver_distance
	void CoccHisImp::get_report_driver_distance_his(std::list<hdata::ReportDriverDistance>& report_driver_distance)
	{
		data_container_.get_report_driver_distance(report_driver_distance);
	}
	void CoccHisImp::set_report_driver_distance_his(std::list<hdata::ReportDriverDistance> report_driver_distance)
	{
		data_container_.set_report_driver_distance(report_driver_distance);
	}
	void CoccHisImp::clear_report_driver_distance_his()
	{
		data_container_.clear_report_driver_distance();
	}
	// report_dispatcher
	void CoccHisImp::get_report_dispatcher_his(std::list<hdata::ReportDisPatcher>& report_dispatcher)
	{
		data_container_.get_report_dispatcher(report_dispatcher);
	}
	void CoccHisImp::set_report_dispatcher_his(std::list<hdata::ReportDisPatcher> report_dispatcher)
	{
		data_container_.set_report_dispatcher(report_dispatcher);
	}
	void CoccHisImp::clear_report_dispatcher_his()
	{
		data_container_.clear_report_dispatcher();
	}
	// report_group_bak
	void CoccHisImp::get_report_group_bak_his(std::list<hdata::ReportGroupBak>& report_group_bak)
	{
		data_container_.get_report_group_bak(report_group_bak);
	}
	void CoccHisImp::set_report_group_bak_his(std::list<hdata::ReportGroupBak> report_group_bak)
	{
		data_container_.set_report_group_bak(report_group_bak);
	}
	void CoccHisImp::clear_report_group_bak_his()
	{
		data_container_.clear_report_group_bak();
	}
	// report_group_status
	void CoccHisImp::get_report_group_status_his(std::list<hdata::ReportGroupStatus>& report_group_status)
	{
		data_container_.get_report_group_status(report_group_status);
	}
	void CoccHisImp::set_report_group_status_his(std::list<hdata::ReportGroupStatus> report_group_status)
	{
		data_container_.set_report_group_status(report_group_status);
	}
	void CoccHisImp::clear_report_group_status_his()
	{
		data_container_.clear_report_group_status();
	}
	// report_action
	void CoccHisImp::get_report_action_his(std::list<hdata::ReportAction>& report_action)
	{
		data_container_.get_report_action(report_action);
	}
	void CoccHisImp::set_report_action_his(std::list<hdata::ReportAction> report_action)
	{
		data_container_.set_report_action(report_action);
	}
	void CoccHisImp::clear_report_action_his()
	{
		data_container_.clear_report_action();
	}
	// report_alarm
	void CoccHisImp::get_report_alarm_his(std::list<hdata::ReportAlarm>& report_alarm)
	{
		data_container_.get_report_alarm(report_alarm);
	}
	void CoccHisImp::set_report_alarm_his(std::list<hdata::ReportAlarm> report_alarm)
	{
		data_container_.set_report_alarm(report_alarm);
	}
	void CoccHisImp::clear_report_alarm_his()
	{
		data_container_.clear_report_alarm();
	}
	// schedual_inused
	void CoccHisImp::get_schedual_inused_his(std::list<hdata::ScheduleInused>& schedual_inused)
	{
		data_container_.get_schedual_inused(schedual_inused);
	}
	void CoccHisImp::set_schedual_inused_his(std::list<hdata::ScheduleInused> schedual_inused)
	{
		data_container_.set_schedual_inused(schedual_inused);
	}
	void CoccHisImp::clear_schedual_inused_his()
	{
		data_container_.clear_schedual_inused();
	}
	// schedual_actual
	void CoccHisImp::get_schedual_actual_his(std::list<hdata::SchedulActual>& schedual_actual)
	{
		data_container_.get_schedual_actual(schedual_actual);
	}
	void CoccHisImp::set_schedual_actual_his(std::list<hdata::SchedulActual> schedual_actual)
	{
		data_container_.set_schedual_actual(schedual_actual);
	}
	void CoccHisImp::clear_schedual_actual_his()
	{
		data_container_.clear_schedual_actual();
	}
	// request_tunnel
	void CoccHisImp::get_request_group_running_tunnel_his(bool& flag, std::string& line_id)
	{
		 data_container_.get_request_group_running_tunnel(flag, line_id);
	}
	void CoccHisImp::set_request_group_running_tunnel_his(bool flag, std::string line_id)
	{
		data_container_.set_request_group_running_tunnel(flag, line_id);
	}
	void CoccHisImp::get_request_driver_distance_tunnel_his(bool& flag, std::string& line_id)
	{
		 data_container_.get_request_driver_distance_tunnel(flag, line_id);
	}
	void CoccHisImp::set_request_driver_distance_tunnel_his(bool flag, std::string line_id)
	{
		data_container_.set_request_driver_distance_tunnel(flag, line_id);
	}
	void CoccHisImp::get_request_dispatcher_tunnel_his(bool& flag, std::string& line_id)
	{
		 data_container_.get_request_dispatcher_tunnel(flag, line_id);
	}
	void CoccHisImp::set_request_dispatcher_tunnel_his(bool flag, std::string line_id)
	{
		data_container_.set_request_dispatcher_tunnel(flag, line_id);
	}
	void CoccHisImp::get_request_group_bak_tunnel_his(bool& flag, std::string& line_id)
	{
		 data_container_.get_request_group_bak_tunnel(flag, line_id);
	}
	void CoccHisImp::set_request_group_bak_tunnel_his(bool flag, std::string line_id)
	{
		data_container_.set_request_group_bak_tunnel(flag, line_id);
	}
	void CoccHisImp::get_request_group_status_tunnel_his(bool& flag, std::string& line_id)
	{
		 data_container_.get_request_group_status_tunnel(flag, line_id);
	}
	void CoccHisImp::set_request_group_status_tunnel_his(bool flag, std::string line_id)
	{
		data_container_.set_request_group_status_tunnel(flag, line_id);
	}
	void CoccHisImp::get_request_action_tunnel_his(bool& flag, std::string& line_id, std::string& start_time, std::string& end_time)
	{
		 data_container_.get_request_action_tunnel(flag, line_id, start_time, end_time);
	}
	void CoccHisImp::set_request_action_tunnel_his(bool flag, std::string line_id, std::string start_time, std::string end_time)
	{
		data_container_.set_request_action_tunnel(flag, line_id, start_time, end_time);
	}
	void CoccHisImp::get_request_alarm_tunnel_his(bool& flag, std::string& line_id, std::string& start_time, std::string& end_time)
	{
		 data_container_.get_request_alarm_tunnel(flag, line_id, start_time, end_time);
	}
	void CoccHisImp::set_request_alarm_tunnel_his(bool flag, std::string line_id, std::string start_time, std::string end_time)
	{
		data_container_.set_request_alarm_tunnel(flag, line_id, start_time, end_time);
	}
	void CoccHisImp::get_request_schedual_inused_tunnel_his(bool& flag, std::string& line_id, std::string& date)
	{
		 data_container_.get_request_schedual_inused_tunnel(flag, line_id, date);
	}
	void CoccHisImp::set_request_schedual_inused_tunnel_his(bool flag, std::string& line_id, std::string& date)
	{
		data_container_.set_request_schedual_inused_tunnel(flag, line_id, date);
	}
	void CoccHisImp::get_request_schedual_actual_tunnel_his(bool& flag, std::string& line_id, std::string& date)
	{
		 data_container_.get_request_schedual_actual_tunnel(flag, line_id, date);
	}
	void CoccHisImp::set_request_schedual_actual_tunnel_his(bool flag, std::string& line_id, std::string& date)
	{
		data_container_.set_request_schedual_actual_tunnel(flag, line_id, date);
	}
	//
	void CoccHisImp::set_request_flag_his(hdata::his_data_type type, bool flag)
	{
		data_container_.set_request_flag(type, flag);
	}
	void CoccHisImp::get_request_flag_his(hdata::his_data_type type, bool& flag)
	{
		data_container_.get_request_flag(type, flag);
	}
	void CoccHisImp::set_request_line_id_his(hdata::his_data_type type, std::string line_id)
	{
		data_container_.set_request_line_id(type, line_id);
	}
	void CoccHisImp::get_request_line_id_his(hdata::his_data_type type, std::string& line_id)
	{
		data_container_.get_request_line_id(type, line_id);
	}
	void CoccHisImp::set_is_doing_his(hdata::his_data_type type, bool flag)
	{
		data_container_.set_is_doing(type, flag);
	}
	void CoccHisImp::get_is_doing_his(hdata::his_data_type type, bool& flag)
	{
		data_container_.get_is_doing(type, flag);
	}
	void CoccHisImp::set_done_his(hdata::his_data_type type, bool flag)
	{
		data_container_.set_done(type, flag);
	}
	void CoccHisImp::get_done_his(hdata::his_data_type type, bool& flag)
	{
		data_container_.get_done(type, flag);
	}
	void CoccHisImp::set_do_false_his(hdata::his_data_type type, bool flag)
	{
		data_container_.set_do_false(type, flag);
	}
	void CoccHisImp::get_do_false_his(hdata::his_data_type type, bool& flag)
	{
		data_container_.get_do_false(type, flag);
	}
	//
	void CoccHisImp::set_update_time_his(hdata::his_data_type type, boost::posix_time::ptime time)
	{
		data_container_.set_update_time(type, time);
	}
	void CoccHisImp::get_update_time_his(hdata::his_data_type type, boost::posix_time::ptime& time)
	{
		data_container_.get_update_time(type, time);
	}

} // end namespace