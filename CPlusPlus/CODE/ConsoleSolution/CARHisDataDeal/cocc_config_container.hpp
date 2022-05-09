#ifndef COCC_CONFIG_CONTAINER_HPP
#define COCC_CONFIG_CONTAINER_HPP

#include <mutex>
#include <string>
#include <list>

namespace hconfig {
	class UpperMachine {
	public:
		UpperMachine()
		{
			port = 0;
		}
	public:
		std::string ip;
		int port;
	};
	class LowerMachine {
	public:
		LowerMachine()
		{
			port = 0;
			client_max_num = 1;
		}
	public:
		std::string ip;
		int port;
		int client_max_num;
	};
	class Config {
	public:
		UpperMachine cocc_upper_recv; // 内部配置
		UpperMachine cocc_upper_send; // 内部配置
		LowerMachine cocc_lower; // 外部配置
	};
	class ConfigContainer {
	public:
		void set(const Config& config)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			config_ = config;
		}
		Config get()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return config_;
		}
	private:
		std::mutex mutex_;  // 互斥锁
		Config config_;  // XML配置
	};
}

#endif

