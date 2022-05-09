#include <iostream>
#include "cocc_publish_impl.h"
static void Log(const std::string& message)
{
	pubdata::singleton_coccpublish_impl::get_mutable_instance().logger().Log(message);
}

int main()
{
	Log("Start COCC Real Data Deal!");
	pubdata::CoccPublishImpl& pi = pubdata::singleton_coccpublish_impl::get_mutable_instance();
	int ret = pi.start();
	if (0 != ret)
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