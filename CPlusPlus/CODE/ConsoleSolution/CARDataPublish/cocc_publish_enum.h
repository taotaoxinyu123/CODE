#ifndef COCC_PUBLISH_ENUM_H
#define COCC_PUBLISH_ENUM_H
namespace pubdata {
	enum real_data_type {
		MESSAGE_POLLING = 1,               //������Ϣ
		NETWORK_ALIVE_STATUS = 2,          //��·ATS��ӿڷ���������״̬
		LOAD_DEVICE_STATUS = 3,            //ATS��Ϣ����
		DEVICE_STATUS_BITMAP = 4,          //ȫ���豸״̬
		DEVICE_STATUS_CHANGE = 5,          //�豸״̬�仯
		SIGNAL_ROUTE_STATUS = 6,           //�Զ�/�˹���·ģʽ
		DEPOT_PLAN = 7,                    //������ɰ�ƻ�
		TRAIN_RECORD = 8,                 //�г�������Ϣ
		TRAIN_BLOCK_INFO = 50,           //�г�������Ϣ
		CBTC_TRAIN_INDICATION_INIT = 51,   //�г���Ϣȫ����Ϣ
		CBTC_TRAIN_INDICATION_UPDATE = 52, //�г���Ϣ������Ϣ
		CBTC_TRAIN_INDICATION_REMOVE = 53, //�г���Ϣɾ����Ϣ
		INUSED_SCHEDULE_PARAMETER = 54,   //����ƻ�����ͼ������Ϣ
		ALARM_MSG = 55                    //ʵʱ�����¼���Ϣ
	};
}
#endif