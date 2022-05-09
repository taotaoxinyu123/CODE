#ifndef CON_STRUCT_HPP
#define CON_STRUCT_HPP
namespace cmysql {

	const char* sz_time = "fd_time";  
	const char* sz_msg_id = "fd_msg_id";
	const char* sz_content = "fd_content";
	const char* sz_spare = "fd_spare";


	//// common
	//const char* sz_time = "fd_time";  
	//const char* sz_msg_id = "fd_msg_id";
	//const char* sz_version = "fd_version";
	//const char* sz_line_id = "fd_line_id";
	//// report_common
	//const char* sz_report_id = "fd_report_id";
	//const char* sz_total_message = "fd_total_message";
	//const char* sz_message_sequence = "fd_message_sequence";
	//const char* sz_count = "fd_count";
	//// 车组运行里程报告
	//namespace group_running 
	//{
	//	const char* sz_pvid = "fd_pvid";
	//	const char* sz_total_running = "fd_total_running";
	//	const char* sz_month_repair = "fd_month_repair";
	//	const char* sz_self_repair = "fd_self_repair";
	//	const char* sz_period_repair = "fd_period_repair";
	//	const char* sz_factory_repair = "fd_factory_repair";
	//	const char* sz_spare = "fd_spare";
	//}
	//// 司机驾驶里程报告
	//namespace driver_distance
	//{
	//	const char* sz_date = "fd_date";
	//	const char* sz_driver_id = "fd_driver_id";
	//	const char* sz_distance = "fd_distance";
	//	const char* sz_factory_repair = "fd_spare";
	//	const char* sz_spare = "fd_spare";
	//}
	//// 调度日志报告
	//namespace dispatcher
	//{
	//	const char* sz_report_time = "fd_report_time";
	//	const char* sz_user_name = "fd_user_name";
	//	const char* sz_log_item = "fd_log_item";
	//	const char* sz_spare = "fd_spare";
	//}
	//// 存备车报告
	//namespace group_bak
	//{
	//	const char* sz_pvid = "fd_pvid";
	//	const char* sz_status = "fd_status";
	//	const char* sz_depot = "fd_depot";
	//	const char* sz_trace_name = "fd_trace_name";
	//	const char* sz_spare = "fd_spare";
	//}
	//// 列车整备状态报告
	//namespace group_status
	//{
	//	const char* sz_pvid = "fd_pvid";
	//	const char* sz_status = "fd_status";
	//	const char* sz_depot = "fd_depot";
	//	const char* sz_spare = "fd_spare";
	//}
	//// 操作命令消息
	//namespace action
	//{
	//	const char* sz_action_site = "fd_action_site";
	//	const char* sz_action_siteid = "fd_action_siteid";
	//	const char* sz_action_name = "fd_action_name";
	//	const char* sz_action_time = "fd_action_time";
	//	const char* sz_action_user = "fd_fd_action_user";
	//	const char* sz_action_type = "fd_action_type";
	//	const char* sz_action_sub_type = "fd_action_sub_type";
	//	const char* sz_action_len = "fd_action_len";
	//	const char* sz_action_content = "fd_action_content";
	//	const char* sz_spare = "fd_spare";
	//}
	//// 操作命令消息
	//namespace alarm
	//{
	//	const char* sz_alarm_site = "fd_alarm_site";
	//	const char* sz_alarm_siteid = "fd_alarm_siteid";
	//	const char* sz_alarm_name = "fd_alarm_name";
	//	const char* sz_alarm_time = "fd_alarm_time";
	//	const char* sz_alarm_type = "fd_alarm_type";
	//	const char* sz_alarm_sub_type = "fd_alarm_sub_type";
	//	const char* sz_alarm_len = "fd_alarm_len";
	//	const char* sz_alarm_content = "fd_alarm_content";
	//	const char* sz_alarm_ack_siteid = "fd_alarm_ack_siteid";
	//	const char* sz_alarm_ack_site = "fd_alarm_ack_siteid";
	//	const char* sz_alarm_ack_name = "fd_alarm_ack_name";
	//	const char* sz_alarm_ack_time = "fd_alarm_ack_time";
	//	const char* sz_spare = "fd_spare";
	//}
	//// 计划列车运行图
	//namespace inused_schedule
	//{
	//	const char* sz_date = "fd_date";
	//	const char* sz_sub_id = "fd_sub_id";
	//	const char* sz_train_id = "fd_train_id";
	//	const char* sz_trip_cnt = "fd_trip_cnt";
	//	const char* sz_trip_id = "fd_trip_id";
	//	const char* sz_pvid = "fd_pvid";
	//	const char* sz_destination_id = "fd_destination_id";
	//	const char* sz_station_cnt = "fd_station_cnt";
	//	const char* sz_station_id = "fd_station_id";
	//	const char* sz_platform_id = "fd_platform_id";
	//	const char* sz_a_time = "fd_a_time";
	//	const char* sz_d_time = "fd_d_time";
	//	const char* sz_flag = "fd_flag";
	//	const char* sz_spare = "fd_spare";
	//}
	//// 实际列车运行图
	//namespace history_schedule
	//{
	//	const char* sz_date = "fd_date";
	//	const char* sz_sub_id = "fd_sub_id";
	//	const char* sz_pvid = "fd_pvid";
	//	const char* sz_station_cnt = "fd_station_cnt";
	//	const char* sz_station_id = "fd_station_id";
	//	const char* sz_platform_id = "fd_platform_id";
	//	const char* sz_a_time = "fd_a_time";
	//	const char* sz_d_time = "fd_d_time";
	//	const char* sz_flag = "fd_flag";
	//	const char* sz_train_id = "fd_train_id";
	//	const char* sz_destination_id = "fd_destination_id";
	//	const char* sz_type = "fd_type";
	//	const char* sz_spare = "fd_spare";
	//}
}

#endif
