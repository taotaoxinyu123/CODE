#ifndef COCC_HIS_DATA_H
#define COCC_HIS_DATA_H
#include <string>
#include <list>
#include <vector>
#include "cocc_his_enum.h"
namespace hdata{
	// 心跳
	class TickTock
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string content;
	};
	// 报告模板
	class ReportBase
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string report_id;
		int total_message;
		int message_sequence;
		int count;
	};
	// 统计信息查询
	class ReportAsk 
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string report_id;
		hdata::statistics_report_type msg_flag;
	};
	// 消息回复开始
	class ReportBegin 
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string report_id;
		hdata::statistics_report_type report_type;
		std::string crc;
	};
	// 消息回复结束
	class ReportEnd
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string report_id;
		hdata::statistics_report_type report_type;
	};
	// 车组运行里程报告
	class GroupRunningData 
	{
	public:
		std::string pvid;
		std::string total_running;
		std::string month_repair;
		std::string self_repair;
		std::string period_repair;
		std::string factory_repair;
	};
	class ReportGroupRunning :public ReportBase
	{
	public:
		std::list<hdata::GroupRunningData> group_running_data;
	};
	//  司机驾驶里程报告
	class DriverDistanceData 
	{
	public:
		std::string date;
		std::string driver_id;
		std::string distance;
	};
	class ReportDriverDistance :public ReportBase
	{
	public:
		std::list<hdata::DriverDistanceData> driver_distance_data;
	};
	//  调度日志报告
	class DisPatcherData
	{
	public:
		std::string report_time;
		std::string user_name;
		std::string log_item;
	};
	class ReportDisPatcher :public ReportBase
	{
	public:
		std::list<hdata::DisPatcherData> dispatcher_data;
	};
	//  存备车报告
	class GroupBakData
	{
	public:
		std::string pvid;
		hdata::driver_storge_status status;
		hdata::driver_location depot;
		std::string track_name;
	};
	class ReportGroupBak :public ReportBase
	{
	public:
		std::list<hdata::GroupBakData> group_bak_data;
	};
	//  列车整备状态报告
	class GroupStatusData
	{
	public:
		std::string pvid;
		std::string status;
		hdata::driver_ready_location depot;
	};
	class ReportGroupStatus :public ReportBase
	{
	public:
		std::list<hdata::GroupStatusData> group_status_data;
	};
	// 事件及告警信息请求
	class AlarmAsk
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string report_id;
		hdata::action_msg_type msg_type;
		std::string start_time;
		std::string end_time;
	};
	//  操作命令消息
	class ActionData
	{
	public:
		hdata::order_location_type action_site;
		std::string action_siteid;
		std::string action_name;
		std::string action_time;
		std::string action_user;
		hdata::operation_type	action_type;
		std::string	action_sub_type;
		std::string	action_len;
		std::string	action_content;
	};
	class ReportAction :public ReportBase
	{
	public:
		std::list<hdata::ActionData> action_data;
	};
	//  报警消息
	class AlarmData
	{
	public:
		hdata::order_location_type alarm_site;
		std::string alarm_siteid;
		std::string alarm_name;
		std::string alarm_time;
		hdata::alarm_type	alarm_type;
		std::string	alarm_sub_type;
		std::string	alarm_len;
		std::string	alarm_content;
		std::string	alarm_ack_siteid;
		std::string	alarm_ack_site;
		std::string	alarm_ack_name;
		std::string	alarm_ack_time;
	};
	class ReportAlarm :public ReportBase
	{
	public:
		std::list<hdata::AlarmData> alarm_data;
	};
	// 运行图申请
	class ScheduleAsk
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string report_id;
		std::string date;
		hdata::tg_msg_type tg_type;
	};
	// 计划列车运行图
	class InusedStation 
	{
	public:
		std::string station_id;
		std::string platform_id;
		std::string a_time;
		std::string d_time;
		hdata::tg_flag_type flag;
		std::string spare;
	};
	class InusedData
	{
	public:
		std::string trip_id;
		std::string pvid;
		std::string destination_id;
		std::string station_cnt;	// repair
		std::list<InusedStation> stations;
	};
	class ScheduleInused
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string date;
		hdata::tg_driver_type sub_id;
		std::string train_id;
		std::string trip_cnt; // repair
		std::list<hdata::InusedData> inused_data;
	};
	// 实际列车运行图
	class ActualdData
	{
	public:
		std::string station_id;
		std::string platform_id;
		std::string a_time;
		std::string d_time;
		hdata::tg_flag_type flag;
		std::string train_id;
		std::string destination_id;
		hdata::tg_plan_type type;
		std::string spare;
	};
	class SchedulActual
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string date;
		hdata::tg_driver_type sub_id;
		std::string pvid;
		std::string station_cnt; // repair
		std::list<hdata::ActualdData> actual_data;
	};
	// 运行图开始
	class SchedulBegin 
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string date;
		hdata::tg_driver_type sub_id;
		std::string crc;
	};
	// 运行图结束
	class SchedulEnd
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string date;
		hdata::tg_driver_type sub_id;
	};
	// 查询无结果
	class AskNoNack 
	{
	public:
		std::string time;
		hdata::his_data_type msg_id;
		std::string version;
		std::string line_id;
		std::string report_id;
		hdata::ask_nack result;
		std::string content;
	};
}
#endif