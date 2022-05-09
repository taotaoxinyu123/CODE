#ifndef COCC_HIS_ENUM_H
#define COCC_HIS_ENUM_H
namespace hdata {
	// ��ϢID
	enum his_data_type {
		E_TYPE_NOT_SET = 0x0000,  // δ��ֵ
		E_REPORT_ASK = 0x0012, // ͳ����Ϣ��ѯ
		E_GROUP_RUNNING_REPORT = 0x0013, // ����������̱���
		E_DRIVER_DISTANCE_REPORT = 0x0014, // ˾����ʻ��̱���
		E_DISPATCHER_REPORT = 0x0015, // ������־����
		E_GROUP_BAK_REPORT = 0x0016, // �汸������
		E_GROUP_STATUS_REPORT = 0x0017, // �г�����״̬����
		E_ALARM_ACK = 0x0018, // �¼����澯��Ϣ����
		E_ACTION_REPORT = 0x0019, // ����������Ϣ
		E_ALARM_REPORT = 0x0020, // �г���Ϣ��ϵͳ�¼�
		E_LOAD_HISTORY_TG_DATA = 0x0021, // ����ͼ����
		E_INUSED_SCHEDULE = 0x0022, // �ƻ��г�����ͼ��Ϣ
		E_HISTORY_SCHEDULE = 0x0023,  // ʵ���г�����ͼ��Ϣ
		E_REPORT_NACK = 0x0027, // ��ѯ�޽����Ϣ	
		E_REPORT_BEGIN = 0x0028, // ��ѯ�����ʼ��Ϣ
		E_REPORT_END = 0x0029, // ��ѯ���������Ϣ
		E_TICK_TOCK = 0x00FF // ������Ϣ
	};
	// ��������
	enum statistics_report_type {
		E_REPORT_NOT_SET = 0x00,  // δ��ֵ
		E_GROUP_RUNNING = 0x01, // �����������
		E_DRIVER_DISTANCE = 0x02, // ˾����ʻ���
		E_DISPATHCHER = 0x03, // ������־
		E_GROUP_BAK = 0x04, // �汸��
		E_GROUP_STATUS = 0x05, // �г�����״̬
		E_ACTION = 0x06, // ��������
		E_ALARM = 0x07 // ϵͳ�¼�����
	};
	// �泵״̬
	enum driver_storge_status {
		E_DRIVER_STORGE_NOT_SET = 0x00,  // δ��ֵ
		E_DRIVER_STORGE_ONLINE = 0x01,  // ������Ӫ
		E_DRIVER_STORGE_STORGE = 0x02,  // ����
		E_DRIVER_STORGE_REPAIR = 0x03 // ��ά��
	};
	// �г�����λ��
	enum driver_location {
		E_DRIVER_LOCATION_NOT_SET = 0x00,  // δ��ֵ
		E_DRIVER_LOCATION_DEPOT_ONE = 0x01,  // ������1
		E_DRIVER_LOCATION_PARKING_ONE = 0x02,  // ͣ����1
		E_DRIVER_LOCATION_DEPOT_TWO = 0x04,  // ������2
		E_DRIVER_LOCATION_PARKING_TWO = 0x08,  // ͣ����2
	};
	// ����״̬�г�λ��
	enum driver_ready_location {
		E_DRIVER_RAEDY_NOT_SET = 0x00,  // δ��ֵ
		E_DRIVER_RAEDY_ONLINE = 0x01,  // ������/ͣ����
		E_DRIVER_RAEDY_STORGE = 0x02,  // ����
	};
	// �¼����䱨��
	enum action_msg_type {
		E_ACTION_NOT_SET = 0x00,  // δ��ֵ
		E_ACTION_MSG = 0x01, // ��������
		E_ALARM_MSG = 0x02 // ϵͳ�¼�����
	};
	// ����λ������
	enum order_location_type {
		E_ORDER_NOT_SET = 0x00,  // δ֪
		E_ORDER_STATION = 0x01, // ��վ
		E_ORDER_CENTER = 0x02 // ����
	};
	// ��������
	enum operation_type {
		E_OPERATION_NOT_SET = 0x00,  // δ��ֵ
		E_OPERATION_ROUTE_CONTROL = 0x01, // ��·����
		E_OPERATION_SIGNAL_CONTROL = 0x02, // �źſ���
		E_OPERATION_DRIVER_MANAGER = 0x03, // �г�����
		E_OPERATION_SCHEDUAL_MANAGER = 0x04, // �ƻ�����
		E_OPERATION_OTHER_ORDER= 0x05 // ��������
	};
	// ��������
	enum alarm_type {
		E_ALALRM_NOT_SET = 0x00,  // δ��ֵ
		E_ALARM_ORDER = 0x01, // ��·����
		E_ALARM_SIGNAL = 0x02, // �źſ���
		E_ALARM_ROUTE = 0x03, // �г�����
		E_ALARM_DRIVER = 0x04, // �ƻ�����
		E_ALARM_SYSTEM= 0x05 // ��������
	};
	// ����ͼ����
	enum tg_msg_type {
		E_TG_NOT_SET = 0x00,  // δ��ֵ
		E_TG_PLAN = 0x01, // �ƻ�ͼ
		E_TG_ACTUAL = 0x02 // ʵ��ͼ
	};
	// �г����б��
	enum tg_driver_type {
		E_TG_DRIVER_NOT_SET = 0x0000,  // δ��ֵ
		E_TG_DRIVER_START = 0x0001, // ��ʼ
		E_TG_DRIVER_RUNNING = 0x0002, // ������
		E_TG_DRIVER_END = 0x0003 // ����
	};
	// ���������б��
	enum tg_flag_type {
		E_TG_FLAG_NOT_SET = 0x00,  // δ֪
		E_TG_DRIVER_DOWN = 0x01, // ����
		E_TG_DRIVER_UP = 0x02 // ����
	};
	// �ƻ����ͷǼƻ�������
	enum tg_plan_type {
		E_TG_PLAN_NOT_SET = 0x00,  // δ֪
		E_TG_DRIVER_PLAN = 0x01, // �ƻ���
		E_TG_DRIVER_UNPLAN = 0x02 // �Ǽƻ���
	};
	// ��ѯ�޽��ԭ��
	enum ask_nack 
	{
		E_ASK_NO_RESULT = 0x00,  // ��ѯ�޽��
		E_ASK_OVERFLOW = 0x01, // ��ѯ�������10000��
		E_ASK_BREAK = 0x02, // ��ϢԴ�ж�
		E_ASK_ERROR = 0x03 // ��ѯ�쳣
	};
} 

#endif