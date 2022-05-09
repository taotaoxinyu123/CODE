#pragma once
#include <thread>
#include "sin_entity_imp.h"
namespace sin_entity
{	
	// 记录日志
	static void log(const std::string& message)
	{
		sin_entity::singleton_entity_impl::get_mutable_instance().logger().Log(message);
	}
	// 获取g_qiut
	static bool GetQuit()
	{
		sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // 获取单例对象
		return ei.get_entity_quit();
	}
	void do_entity_svc()
	{
		log("entity_manager:do_entity_svc");
		while (true) 
		{
			// do-something（如果内容很多则新建一个文件）
			sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // 获取单例对象

			// 当g_quit为true的时候，线程退出
			if (GetQuit())
			{
				log("sin_entity_thread exit");
				break;
			}
		}
	}
}
void StartEntityThread()
{
	std::thread* entity_thread = new std::thread(&sin_entity::do_entity_svc); // 创建线程
}