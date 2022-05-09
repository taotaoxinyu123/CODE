#ifndef COCC_HIS_ENUM_H
#define COCC_HIS_ENUM_H
namespace hdata {
	// 消息ID
	enum his_data_type {
		E_TYPE_NOT_SET = 0x0000,  // 未设值
		E_REPORT_ASK = 0x0012, // 统计信息查询
		E_GROUP_RUNNING_REPORT = 0x0013, // 车组运行里程报告
		E_DRIVER_DISTANCE_REPORT = 0x0014, // 司机驾驶里程报告
		E_DISPATCHER_REPORT = 0x0015, // 调度日志报告
		E_GROUP_BAK_REPORT = 0x0016, // 存备车报告
		E_GROUP_STATUS_REPORT = 0x0017, // 列车整备状态报告
		E_ALARM_ACK = 0x0018, // 事件及告警信息请求
		E_ACTION_REPORT = 0x0019, // 操作命令消息
		E_ALARM_REPORT = 0x0020, // 列车信息、系统事件
		E_LOAD_HISTORY_TG_DATA = 0x0021, // 运行图申请
		E_INUSED_SCHEDULE = 0x0022, // 计划列车运行图消息
		E_HISTORY_SCHEDULE = 0x0023,  // 实际列车运行图消息
		E_REPORT_NACK = 0x0027, // 查询无结果消息	
		E_REPORT_BEGIN = 0x0028, // 查询结果开始消息
		E_REPORT_END = 0x0029, // 查询结果结束消息
		E_TICK_TOCK = 0x00FF // 心跳信息
	};
	// 报告类型
	enum statistics_report_type {
		E_REPORT_NOT_SET = 0x00,  // 未设值
		E_GROUP_RUNNING = 0x01, // 车组运行里程
		E_DRIVER_DISTANCE = 0x02, // 司机驾驶里程
		E_DISPATHCHER = 0x03, // 调度日志
		E_GROUP_BAK = 0x04, // 存备车
		E_GROUP_STATUS = 0x05, // 列车整备状态
		E_ACTION = 0x06, // 操作命令
		E_ALARM = 0x07 // 系统事件报警
	};
	// 存车状态
	enum driver_storge_status {
		E_DRIVER_STORGE_NOT_SET = 0x00,  // 未设值
		E_DRIVER_STORGE_ONLINE = 0x01,  // 上线运营
		E_DRIVER_STORGE_STORGE = 0x02,  // 备车
		E_DRIVER_STORGE_REPAIR = 0x03 // 上维修
	};
	// 列车所处位置
	enum driver_location {
		E_DRIVER_LOCATION_NOT_SET = 0x00,  // 未设值
		E_DRIVER_LOCATION_DEPOT_ONE = 0x01,  // 车辆段1
		E_DRIVER_LOCATION_PARKING_ONE = 0x02,  // 停车场1
		E_DRIVER_LOCATION_DEPOT_TWO = 0x04,  // 车辆段2
		E_DRIVER_LOCATION_PARKING_TWO = 0x08,  // 停车场2
	};
	// 整备状态列车位置
	enum driver_ready_location {
		E_DRIVER_RAEDY_NOT_SET = 0x00,  // 未设值
		E_DRIVER_RAEDY_ONLINE = 0x01,  // 车辆段/停车场
		E_DRIVER_RAEDY_STORGE = 0x02,  // 正线
	};
	// 事件及其报警
	enum action_msg_type {
		E_ACTION_NOT_SET = 0x00,  // 未设值
		E_ACTION_MSG = 0x01, // 操作命令
		E_ALARM_MSG = 0x02 // 系统事件报警
	};
	// 命令位置类型
	enum order_location_type {
		E_ORDER_NOT_SET = 0x00,  // 未知
		E_ORDER_STATION = 0x01, // 车站
		E_ORDER_CENTER = 0x02 // 中心
	};
	// 操作类型
	enum operation_type {
		E_OPERATION_NOT_SET = 0x00,  // 未设值
		E_OPERATION_ROUTE_CONTROL = 0x01, // 进路控制
		E_OPERATION_SIGNAL_CONTROL = 0x02, // 信号控制
		E_OPERATION_DRIVER_MANAGER = 0x03, // 列车管理
		E_OPERATION_SCHEDUAL_MANAGER = 0x04, // 计划管理
		E_OPERATION_OTHER_ORDER= 0x05 // 其他命令
	};
	// 报警类型
	enum alarm_type {
		E_ALALRM_NOT_SET = 0x00,  // 未设值
		E_ALARM_ORDER = 0x01, // 进路控制
		E_ALARM_SIGNAL = 0x02, // 信号控制
		E_ALARM_ROUTE = 0x03, // 列车管理
		E_ALARM_DRIVER = 0x04, // 计划管理
		E_ALARM_SYSTEM= 0x05 // 其他命令
	};
	// 运行图类型
	enum tg_msg_type {
		E_TG_NOT_SET = 0x00,  // 未设值
		E_TG_PLAN = 0x01, // 计划图
		E_TG_ACTUAL = 0x02 // 实际图
	};
	// 列车运行标记
	enum tg_driver_type {
		E_TG_DRIVER_NOT_SET = 0x0000,  // 未设值
		E_TG_DRIVER_START = 0x0001, // 开始
		E_TG_DRIVER_RUNNING = 0x0002, // 运行中
		E_TG_DRIVER_END = 0x0003 // 结束
	};
	// 运行上下行标记
	enum tg_flag_type {
		E_TG_FLAG_NOT_SET = 0x00,  // 未知
		E_TG_DRIVER_DOWN = 0x01, // 下行
		E_TG_DRIVER_UP = 0x02 // 上行
	};
	// 计划车和非计划车类型
	enum tg_plan_type {
		E_TG_PLAN_NOT_SET = 0x00,  // 未知
		E_TG_DRIVER_PLAN = 0x01, // 计划车
		E_TG_DRIVER_UNPLAN = 0x02 // 非计划车
	};
	// 查询无结果原因
	enum ask_nack 
	{
		E_ASK_NO_RESULT = 0x00,  // 查询无结果
		E_ASK_OVERFLOW = 0x01, // 查询结果超过10000条
		E_ASK_BREAK = 0x02, // 信息源中断
		E_ASK_ERROR = 0x03 // 查询异常
	};
} 

#endif