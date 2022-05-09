#pragma once
#pragma once
#include <string>
#include <mutex>
namespace sin_entity
{
	class OtherContainer
	{
	public:
		OtherContainer()
		{
			t_qiut_ = false;
		}
	public:
		void set_other(std::string name, std::string age)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			name_ = name;
			age_ = age;
		}
		std::string get_name()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return name_;
		}
		std::string get_age()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return age_;
		}
	public:
		// t_qiut
		void set_t_qiut(bool t_qiut)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			t_qiut_ = t_qiut;
		}
		bool get_t_qiut()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return t_qiut_;
		}
	private:
		std::mutex mutex_;  // 数据互斥锁
		std::string name_;
		std::string age_;
	private:
		bool t_qiut_; // other退出标志

	};
} // sin_config