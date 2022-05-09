#ifndef COCC_CONTAINER_HPP
#define COCC_CONTAINER_HPP
#include <map>
#include <string>
#include <list>
#include <mutex>
#include "bs_pub_filedrv.h"
namespace pubdata {
	class PublishContainer {
	public:
		PublishContainer()
		{
			pub_iplat_switch_ = false;
		}
	public:
		void init_pb_data(const std::string key, const PublishIplat pub_data)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat_[key] = pub_data;
		}
		void update_discern(const std::string key, const int discern)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat_[key].discern = discern;
		}
		void update_block_flag(const std::string key, const int block_flag)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat_[key].bolck_flag = block_flag;
		}
		void update_line_id(const std::string key, const int line_id)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat_[key].line_id = line_id;
		}
		void update_section_id_of_head(const std::string key, const int section_id_of_head)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat_[key].section_id_of_head = section_id_of_head;
		}
		void update_section_id_of_tail(const std::string key, const int section_id_of_tail)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat_[key].section_id_of_tail = section_id_of_tail;
		}
		void get_pub_iplat(std::map<std::string, PublishIplat>& pub_iplat)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat = pub_iplat_;
		}
		void get_trip_id_lst(std::map<std::string, int>& trip_id_lst)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			trip_id_lst = trip_id_lst_;
		}
		void set_trip_id_lst(std::map<std::string, int> trip_id_lst)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			trip_id_lst_ = trip_id_lst;
		}
		void get_pub_iplat_switch(bool& pub_iplat_switch)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat_switch = pub_iplat_switch_;
		}
		void set_pub_iplat_switch(bool pub_iplat_switch)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			pub_iplat_switch_ = pub_iplat_switch;
		}
	private:
		std::mutex mutex_;  // 数据互斥锁
		std::map<std::string, int> trip_id_lst_; // 车辆标记集合：若插入数据trip_id不在集合中，则抛弃。左边是center给的（string）右边API到iplat是（int）
		bool pub_iplat_switch_; // 是否写入iplat开关
		std::map<std::string, PublishIplat> pub_iplat_; // to iplat data
	};


} // namespaces


#endif
