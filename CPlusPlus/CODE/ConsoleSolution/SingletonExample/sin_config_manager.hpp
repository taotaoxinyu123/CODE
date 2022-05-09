#pragma once
#include <thread>
#include "sin_entity_imp.h"
namespace sin_config
{
	// 记录日志
	static void log(const std::string& message)
	{
		sin_entity::singleton_entity_impl::get_mutable_instance().logger().Log(message);
	}
	void do_config(std::string& ip, std::string& port)
	{
		log("sin_config_manager: do_config");
		// 获取配置 do someting
	}
}
void GetConfig(std::string& ip, std::string& port)
{
	sin_config::do_config(ip, port);
}