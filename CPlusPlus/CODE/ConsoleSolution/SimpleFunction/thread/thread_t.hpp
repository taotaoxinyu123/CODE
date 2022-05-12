#pragma once
#include <thread>
#include <iostream>
#include <string>

/**
* 1.ȫ�ݱ�����ʹ�ã������и��ط������������籾�ľ�����main.cpp�ж����gQiut_tock��gQiut_tick
* 2.��������ļ���Ҫʹ�����ȫ�ֱ���������Ҫ������ſ���ʹ�ã������·���
* 3.һ������²�����ʹ��ȫ�ֱ���
*/
extern bool gQiut_tock;
extern bool gQiut_tick;

namespace thread_ns {	

	void do_Tock(std::string name)
	{
		std::cout << "do_Tock �������ݣ�" << name << std::endl;
		while (true) 
		{
			// sleep 1000ms
			std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1000));

			//do something

			// ����ȫ�ֱ����˳��߳�
			if (gQiut_tock)
			{
				break;  
			}
		}
		
	}

	void do_Tick()
	{
		while (true)
		{
			// sleep 1000ms
			std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1000));
			if (gQiut_tick)
			{
				break; 
			}
		}
	}
}
//interface�������ṩ�����߳̽ӿ�
void StartTockThread()
{
	std::thread* tock_check_thread = new std::thread(&thread_ns::do_Tock, "tock");
}
void StartTickThread()
{
	std::thread* tock_check_thread = new std::thread(&thread_ns::do_Tick);
}

