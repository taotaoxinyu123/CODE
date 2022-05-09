#pragma once
#include <string>
#include <mutex>
namespace sin_config
{
	class ConfigContainer 
	{
	public:
		void set_config(std::string ip, std::string port) 
		{
			std::lock_guard<std::mutex> guard(mutex_);
			ip_ = ip;
			port_ = port;
		}
		std::string get_ip()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return ip_;
		}
		std::string get_port()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return port_;
		}
	private:
		std::mutex mutex_;  // Êý¾Ý»¥³âËø
		std::string ip_;
		std::string port_;

	};
} // sin_config