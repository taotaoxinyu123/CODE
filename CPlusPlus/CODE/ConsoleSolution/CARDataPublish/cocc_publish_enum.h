#ifndef COCC_PUBLISH_ENUM_H
#define COCC_PUBLISH_ENUM_H
namespace pubdata {
	enum real_data_type {
		MESSAGE_POLLING = 1,               //心跳消息
		NETWORK_ALIVE_STATUS = 2,          //线路ATS与接口服务器连接状态
		LOAD_DEVICE_STATUS = 3,            //ATS信息请求
		DEVICE_STATUS_BITMAP = 4,          //全体设备状态
		DEVICE_STATUS_CHANGE = 5,          //设备状态变化
		SIGNAL_ROUTE_STATUS = 6,           //自动/人工进路模式
		DEPOT_PLAN = 7,                    //出入库派班计划
		TRAIN_RECORD = 8,                 //列车报点消息
		TRAIN_BLOCK_INFO = 50,           //列车阻塞消息
		CBTC_TRAIN_INDICATION_INIT = 51,   //列车信息全体消息
		CBTC_TRAIN_INDICATION_UPDATE = 52, //列车信息更新消息
		CBTC_TRAIN_INDICATION_REMOVE = 53, //列车信息删除消息
		INUSED_SCHEDULE_PARAMETER = 54,   //当天计划运行图参数消息
		ALARM_MSG = 55                    //实时报警事件消息
	};
}
#endif