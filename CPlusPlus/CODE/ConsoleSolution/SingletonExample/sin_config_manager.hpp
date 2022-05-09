#pragma once
#include <thread>
#include "sin_entity_imp.h"
namespace sin_config
{
	// ��¼��־
	static void log(const std::string& message)
	{
		sin_entity::singleton_entity_impl::get_mutable_instance().logger().Log(message);
	}
	void do_config(std::string& ip, std::string& port)
	{
		log("sin_config_manager: do_config");
		// ��ȡ���� do someting
	}
}
void GetConfig(std::string& ip, std::string& port)
{
	sin_config::do_config(ip, port);
}