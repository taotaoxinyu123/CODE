#include "cocc_pb2cpp.h"
// header
static void PB2CPPHeader(const pbproto::package_header_t& pb, pubdata::package_header_t& cpp)
{
	cpp.time = pb.time();
	cpp.version = pb.version();
	cpp.msg_id = pb.msg_id();
}

static void PB2CPPCbtcTrainIndicationInitTrain(const pbproto::cbtc_train_indication_init_Train_t& pb, pubdata::cbtc_train_indication_init_train_t& cpp)
{
	cpp.section_id_of_head = pb.section_id_of_head();
	cpp.offset_in_section_of_head = pb.offset_in_section_of_head();
	cpp.section_id_of_tail = pb.section_id_of_tail();
	cpp.offset_in_section_of_tail = pb.offset_in_section_of_tail();
	cpp.dev_type = pb.dev_type();
	cpp.dev_name = pb.dev_name();
	cpp.pvid = pb.pvid();
	cpp.train_id = pb.train_id();
	cpp.trip_id = pb.trip_id();
	cpp.destination_id = pb.destination_id();
	cpp.rollingstock = pb.rollingstock();
	cpp.driver_id = pb.driver_id();
	cpp.otp_time = pb.otp_time();
	cpp.mode = pb.mode();
	cpp.arrive_time = pb.arrive_time();
	cpp.depart_time = pb.depart_time();
	cpp.rate = pb.rate();
	cpp.speed = pb.speed();
	cpp.spare = pb.spare();
}

static void PB2CPPCbtcTrainIndicationInit(const pbproto::cbtc_train_indication_init_t& pb, pubdata::cbtc_train_indication_init_t& cpp)
{
	cpp.line_id = pb.line_id();
	cpp.ist_id = pb.ist_id();
	for (auto i = 0; i < pb.train_size(); i++) 
	{
		pubdata::cbtc_train_indication_init_train_t temp;
		PB2CPPCbtcTrainIndicationInitTrain(pb.train(i), temp);
		cpp.train.push_back(temp);
	}
}
// 列车信息全体消息
void PB2CPPTrianIndicationInit(const pbproto::post_cbtc_train_indication_init& pb, pubdata::post_cbtc_train_indication_init& cpp)
{
	cpp.header.clear();
	PB2CPPHeader(pb.header(), cpp.header);
	PB2CPPCbtcTrainIndicationInit(pb.data(), cpp.data);

}


void PB2CPPTrianBlockInfoTrain(const pbproto::train_block_info_train_t& pb, pubdata::train_block_info_train_t& cpp)
{
	cpp.pvid = pb.pvid();
	cpp.train_id = pb.train_id();
	cpp.direction = pb.direction();
	cpp.station_id_in_up_side = pb.station_id_in_up_side();
	cpp.station_id_in_down_side = pb.station_id_in_down_side();
	cpp.ist_id = pb.ist_id();
	cpp.dev_type = pb.dev_type();
	cpp.dev_name = pb.dev_name();
	cpp.block_flag = pb.block_flag();
}

void PB2CPPTrianBlockInfoT(const pbproto::train_block_info_t& pb, pubdata::train_block_info_t& cpp)
{
	cpp.line_id = pb.line_id();
	for (auto i = 0; i < pb.train_size(); i++)
	{
		pubdata::train_block_info_train_t temp;
		PB2CPPTrianBlockInfoTrain(pb.train(i), temp);
		cpp.train.push_back(temp);
	}
}
// 列车阻塞消息
void PB2CPPTrianBlockInfo(const pbproto::post_train_block_info& pb, pubdata::post_train_block_info& cpp)
{
	cpp.header.clear();
	PB2CPPHeader(pb.header(), cpp.header);
	PB2CPPTrianBlockInfoT(pb.data(), cpp.data);
}