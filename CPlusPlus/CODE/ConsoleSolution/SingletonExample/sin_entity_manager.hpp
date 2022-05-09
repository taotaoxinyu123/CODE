#pragma once
#include <thread>
#include "sin_entity_imp.h"
namespace sin_entity
{	
	// ��¼��־
	static void log(const std::string& message)
	{
		sin_entity::singleton_entity_impl::get_mutable_instance().logger().Log(message);
	}
	// ��ȡg_qiut
	static bool GetQuit()
	{
		sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // ��ȡ��������
		return ei.get_entity_quit();
	}
	void do_entity_svc()
	{
		log("entity_manager:do_entity_svc");
		while (true) 
		{
			// do-something��������ݺܶ����½�һ���ļ���
			sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // ��ȡ��������

			// ��g_quitΪtrue��ʱ���߳��˳�
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
	std::thread* entity_thread = new std::thread(&sin_entity::do_entity_svc); // �����߳�
}