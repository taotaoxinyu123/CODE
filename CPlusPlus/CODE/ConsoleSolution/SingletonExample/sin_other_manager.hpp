#pragma once
#include <thread>
#include "sin_entity_imp.h"
// ��¼��־
static void log(const std::string& message)
{
	sin_entity::singleton_entity_impl::get_mutable_instance().logger().Log(message);
}
namespace sin_entity
{
	// ��ȡg_qiut
	static bool GetOtherQuit()
	{
		sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // ��ȡ��������
		return ei.get_other_quit();
	}
	void do_other_svc()
	{
		log("other_manager:do_other_svc");
		while (true) 
		{
			// do-something��������ݺܶ����½�һ���ļ���
			sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // ��ȡ��������

			// ��g_quitΪtrue��ʱ���߳��˳�
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
	std::thread* other_thread = new std::thread(&sin_entity::do_other_svc); // �����߳�
}