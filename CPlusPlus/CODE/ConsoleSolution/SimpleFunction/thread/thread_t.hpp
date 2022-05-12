#pragma once
#include <thread>
#include <iostream>
#include <string>

/**
* 1.全据变量的使用，必须有个地方定义它，例如本文就是在main.cpp中定义的gQiut_tock和gQiut_tick
* 2.如果其他文件需要使用这个全局变量，则需要声明后才可以使用，例如下方。
* 3.一般情况下不建议使用全局变量
*/
extern bool gQiut_tock;
extern bool gQiut_tick;

namespace thread_ns {	

	void do_Tock(std::string name)
	{
		std::cout << "do_Tock 参数传递：" << name << std::endl;
		while (true) 
		{
			// sleep 1000ms
			std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1000));

			//do something

			// 设置全局变量退出线程
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
//interface：对外提供启动线程接口
void StartTockThread()
{
	std::thread* tock_check_thread = new std::thread(&thread_ns::do_Tock, "tock");
}
void StartTickThread()
{
	std::thread* tock_check_thread = new std::thread(&thread_ns::do_Tick);
}

