#ifndef COCC_PUBLISH_IMPL_H
#define COCC_PUBLISH_IMPL_H
#include "cocc_publish_container.hpp"
#include <thread>
#include "boost/serialization/singleton.hpp"
#include "cocc_config_container.hpp"
#include "cocc_logger.h"
namespace pubdata {
	class CoccPublishImpl {
	public:
		CoccPublishImpl();
		~CoccPublishImpl();
	public:
		int start();
		void init_iplat_data();
	public:  // 配置数据API
		pconfig::Config config();
		plogger::Logger& logger() { return logger_; }
	public:  // to iplat
		void init_pb_data_imp(const std::string key, const PublishIplat pub_data);
		void update_discern_imp(const std::string key, const int value);
		void update_block_flag_imp(const std::string key, const int value);
		void update_line_id_imp(const std::string key, const int value);
		void update_section_id_of_head_imp(const std::string key, const int value);
		void update_section_id_of_tail_imp(const std::string key, const int value);
		void get_pub_iplat_imp(std::map<std::string, PublishIplat>& pub_iplat);
		void get_trip_id_lst_imp(std::map<std::string, int>& trip_id_lst);
		void set_trip_id_lst_imp(std::map<std::string, int> trip_id_lst);
		void get_pub_iplat_switch_imp(bool& pub_iplat_switch);
		void set_pub_iplat_switch_imp(const bool pub_iplat_switch);
	private:
		PublishContainer publish_container_; // 发布容器
		pconfig::ConfigContainer config_container_; // 配置容器
		plogger::Logger logger_;  // 日志对象
	};

	typedef boost::serialization::singleton<CoccPublishImpl> singleton_coccpublish_impl;  // 单例
} // namespace


#endif