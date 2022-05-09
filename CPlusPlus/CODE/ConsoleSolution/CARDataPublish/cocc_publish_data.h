#ifndef COCC_PUBLISH_DATA_H
#define COCC_PUBLISH_DATA_H
#include <string>
#include <list>
namespace pubdata {
	// 
	class recv_data 
	{
	public:
		int msg_id;
		std::string data;
	};

	//心跳
	class package_header_t {
	public:
		int time;
		int version;
		int msg_id;
	public:
		package_header_t()
		{
			this->clear();
		}
		void clear() 
		{
			time = 0;
			msg_id = -1;
			version = 0;
		}
	};
	//线路ATS服务器连接状态
	class connection_status_t {
	public:
		int line_id;
		int status;
	public:
		connection_status_t()
		{
			line_id = 0;
			status = 0;
		}
	};
	class post_connection_status {
	public:
		package_header_t header;
		connection_status_t data;
	};

	//设备状态全体消息
	class dev_prop_t {
	public:
		std::string dev_name;
		int status;
		int spare;
	public:
		dev_prop_t()
		{
			status = 0;
			spare = 0;
		}
	};
	class devices_t {
	public:
		int _type;
		std::list<dev_prop_t> dev_prop;
	public:
		devices_t()
		{
			_type = 0;
		}
	};
	class device_status_bitmap_t {
	public:
		int line_id;
		int ist_id;
		std::list<devices_t> devices;
	public:
		device_status_bitmap_t()
		{
			line_id = 0;
			ist_id = 0;
		}
	};
	class post_device_status_bitmap {
	public:
		package_header_t header;
		device_status_bitmap_t data;
	};

	//列车信息全体消息
	class cbtc_train_indication_init_train_t {
	public:
		int section_id_of_head;
		int offset_in_section_of_head;
		int section_id_of_tail;
		int offset_in_section_of_tail;
		int dev_type;
		std::string dev_name;
		std::string pvid;
		std::string train_id;
		std::string trip_id;
		std::string destination_id;
		int rollingstock;
		std::string driver_id;
		int otp_time;
		int mode;
		std::string arrive_time;
		std::string depart_time;
		int rate;
		int speed;
		int spare;
	public:
		cbtc_train_indication_init_train_t()
		{
			this->clear();
		}
		void clear()
		{
			section_id_of_head = 0;
			offset_in_section_of_head = 0;
			section_id_of_tail = 0;
			offset_in_section_of_tail = 0;
			dev_type = 0;
			rollingstock = 0;
			otp_time = 0;
			mode = 0;
			rate = 0;
			speed = 0;
			spare = 0;
		}
	};
	class cbtc_train_indication_init_t{
	public:
		int line_id;
		int ist_id;
		std::list<cbtc_train_indication_init_train_t> train;
	public:
		cbtc_train_indication_init_t()
		{
			this->clear();
		}
		void clear() 
		{
			line_id = 0;
			ist_id = 0;
			train.clear();
		}
	};
	class post_cbtc_train_indication_init {
	public:
		package_header_t header;
		cbtc_train_indication_init_t data;
	public:
		post_cbtc_train_indication_init() 
		{
			this->clear();
		}
		void clear() 
		{
			header.clear();
			data.clear();
		}
	};

	//当天出入库派班计划消息
	class schedule_t {
	public:
		int depot_station;
		std::string pvid;
		std::string driver_id;
		int out_flag;
		int out_schedule;
		std::string out_time;
		int out_station;
		int out_side;
		std::string out_name;
		std::string out_trainid;
		int out_destination;
		std::string out_tripid;
		int out_localsubid = 0;
		int in_flag;
		int in_schedule;
		std::string in_time;
		int in_station;
		int in_side;
		std::string in_name;
		std::string in_trainid;
		int in_destination;
		std::string in_tripid;
		int in_localsubid;
	public:
		schedule_t()
		{
			depot_station = 0;
			out_flag = 0;
			out_schedule = 0;
			out_station = 0;
			out_side = 0;
			out_destination = 0;
			out_localsubid = 0;
			in_flag = 0;
			in_schedule = 0;
			in_station = 0;
			in_side = 0;
			in_destination = 0;
			in_localsubid = 0;
		}
	};
	class depot_plan_t {
	public:
		int line_id;
		std::string date;
		std::list<schedule_t>schedule;
	public:
		depot_plan_t()
		{
			line_id = 0;
		}
	};
	class post_depot_plan {
	public:
		package_header_t header;
		depot_plan_t data;
	};

	//列车阻塞消息
	class train_block_info_train_t {
	public:
		std::string pvid;
		std::string train_id;
		int direction;
		int station_id_in_up_side;
		int station_id_in_down_side;
		int ist_id;
		int dev_type;
		std::string dev_name;
		int block_flag;
	public:
		train_block_info_train_t()
		{
			this->clear();
		}
		void clear()
		{
			direction = 0;
			station_id_in_up_side = 0;
			station_id_in_down_side = 0;
			ist_id = 0;
			dev_type = 0;
			block_flag = 66;
		}
	};
	class train_block_info_t {
	public:
		int line_id = 0;
		std::list<train_block_info_train_t> train;
	public:
		train_block_info_t()
		{
			this->clear();
		}
		void clear()
		{
			line_id = 0;
		}
	};
	class post_train_block_info {
	public:
		package_header_t header;
		train_block_info_t data;
	public:
		post_train_block_info() 
		{
			this->clear();
		}
		void clear() 
		{
			header.clear();
			data.clear();
		}
	};

	//当天计划运行图参数消息
	class inused_schedule_parameter_t {
	public:
		int line_id;
		std::string date;
		int valid;
		std::string inused_schedule_name;
		std::string spare
			;
	public:
		inused_schedule_parameter_t()
		{
			line_id = 0;
			valid = 0;
		}
	};
	class post_inused_schedule_parameter {
	public:
		package_header_t header;
		inused_schedule_parameter_t data;
	};

	//自动/人工进路模式消息
	class route_t {
	public:
		std::string route_name;
		int route_status;
	};
	class routes_t {
	public:
		std::string signal_name;
		std::list<route_t> route;
	};
	class route_mode_t {
	public:
		int line_id;
		int ist_id;
		std::list<routes_t> routes;
	public:
		route_mode_t()
		{
			line_id = 0;
			ist_id = 0;
		}
	};
	class post_route_mode {
	public:
		package_header_t header;
		route_mode_t data;
	};

	//设备状态变化消息
	class device_status_change_t {
	public:
		int line_id;
		int ist_id;
		int _type;
		std::string dev_name;
		int dev_status;
		int spare;
	public:
		device_status_change_t()
		{
			line_id = 0;
			ist_id = 0;
			_type = 0;
			dev_status = 0;
			spare = 0;
		}
	};
	class post_device_status_change {
	public:
		package_header_t header;
		device_status_change_t data;
	};

	//列车报点消息
	class train_record_t {
	public:
		int line_id;
		std::string train_id;
		std::string trip_id;
		int first_last_id;
		std::string pvid;
		int destination_id;
		int train_type;
		int dir;
		int station_id;
		int side_id;
		std::string track_name;
		int record_type;
		std::string record_time;
		std::string reserved;
	public:
		train_record_t()
		{
			line_id = 0;
			first_last_id = 0;
			destination_id = 0;
			train_type = 0;
			dir = 0;
			station_id = 0;
			side_id = 0;
			record_type = 0;
		}
	};
	class post_train_record {
	public:
		package_header_t header;
		train_record_t data;
	};

	//列车信息更新消息[增加/更新]
	class cbtc_train_indication_update_t {
	public:
		int line_id;
		int _type;
		int ist_id;
		int section_id_of_head;
		int offset_in_section_of_head;
		int section_id_of_tail;
		int offset_in_section_of_tail;
		int dev_type;
		std::string dev_name;
		std::string pvid;
		std::string train_id;
		std::string trip_id;
		std::string destination_id;
		int rollingstock;
		std::string driver_id;
		int route_id;
		int otp_time;
		int mode;
		std::string arrive_time;
		std::string depart_time;
		int rate;
		int speed;
		std::string reserved;
	public:
		cbtc_train_indication_update_t()
		{
			line_id = 0;
			_type = 0;
			ist_id = 0;
			section_id_of_head = 0;
			offset_in_section_of_head = 0;
			section_id_of_tail = 0;
			offset_in_section_of_tail = 0;
			dev_type = 0;
			rollingstock = 0;
			route_id = 0;
			otp_time = 0;
			mode = 0;
			rate = 0;
			speed = 0;
		}
	};
	class post_cbtc_train_indication_update {
	public:
		package_header_t header;
		cbtc_train_indication_update_t data;
	};

	//列车信息删除
	class cbtc_train_indication_remove_t {
	public:
		int line_id;
		int ist_id;
		int section_id_of_head;
		int offset_in_section_of_head;
		int section_id_of_tail;
		int offset_in_section_of_tail;
		int dev_type;
		std::string dev_name;
		std::string pvid;
	public:
		cbtc_train_indication_remove_t()
		{
			line_id = 0;
			ist_id = 0;
			section_id_of_head = 0;
			offset_in_section_of_head = 0;
			section_id_of_tail = 0;
			offset_in_section_of_tail = 0;
			dev_type = 0;
		}
	};
	class post_cbtc_train_indication_remove {
	public:
		package_header_t header;
		cbtc_train_indication_remove_t datda;
	};

	//实时报警
	class train_alarm_t {
	public:
		int line_id;
		int level;
		int class_;//待确定
		int sub_class;
		std::string gen_time;
		std::string source;
		int ist_id;
		int tag_id;
		std::string alarm_content;
	public:
		train_alarm_t()
		{
			line_id = 0;
			level = 0;
			class_ = 0;
			sub_class = 0;
			ist_id = 0;
			tag_id = 0;
		}
	};
	class post_train_alarm {
	public:
		package_header_t header;
		train_alarm_t data;
	};

}
#endif // !BS_PUB_FILEDRV_CLASS_H