#include <iostream>
#include "cocc_his_impl.h"
#include "cocc_error_code.h"

static void Log(const std::string& message)
{
    hdata::singleton_cocchis_impl::get_mutable_instance().logger().Log(message);
}

int main()
{
    Log("Start COCC NoReal Time Deal!");
    hdata::CoccHisImp& ci = hdata::singleton_cocchis_impl::get_mutable_instance();
    int ret = ci.start();
    if (COCC_SUCCESS != ret) 
    {
        return 0;
    }
    Log("程序已启动");
	std::string quit;
	while (true)
	{

		std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(100));
		// 处理键盘输入
		quit.clear();
		std::getline(std::cin, quit, '\n');
		if (quit.empty()) continue;

		if (quit.front() == 'Q' || quit.front() == 'q')
		{
			Log("程序收到退出指令");
			break;  // #End
		}
	}

}
