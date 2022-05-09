#pragma once
#include <thread>
#include "sin_entity_imp.h"
// 记录日志
static void log(const std::string& message)
{
	sin_entity::singleton_entity_impl::get_mutable_instance().logger().Log(message);
}
namespace sin_entity
{
	// 获取g_qiut
	static bool GetOtherQuit()
	{
		sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // 获取单例对象
		return ei.get_other_quit();
	}
	void do_other_svc()
	{
		log("other_manager:do_other_svc");
		while (true) 
		{
			// do-something（如果内容很多则新建一个文件）
			sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // 获取单例对象

			// 当g_quit为true的时候，线程退出
			if (GetOtherQuit())
			{
				log("sin_other_thread exit");
				break;
			}
		}
	}
}
void StartOtherThread()
{
	std::thread* other_thread = new std::thread(&sin_entity::do_other_svc); // 创建线程
}