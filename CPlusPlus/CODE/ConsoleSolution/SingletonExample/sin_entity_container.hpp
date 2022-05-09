#pragma once
#include <mutex>
#include <string>
#include <list>
#include <vector>
#include "sin_entity_data.h"
namespace sin_entity {
	// 内部数据结构
	class InternalParam
	{
	public:
		std::string name;
		int status_tagout;
		int mid_requisition;
		int mid_at_close;
		int mid_ever_occupancy;
		std::string mid_time_window;
	public:
		InternalParam()
		{
			status_tagout = 0;
			mid_requisition = 0;
			mid_at_close = 0;
			mid_ever_occupancy = 0;
		}
	};

	// 容器
	class EntityContainer
	{
	public:
		EntityContainer() 
		{
			param_1_ = false;
			param_2_ = false;
			g_qiut_ = false;
		}
	// 提供访问容器内数据接口
	public:
		// param_1
		void set_param_1(bool param_1)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			param_1_ = param_1;
		}
		bool get_param_1()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return param_1_;
		}
		// param_2
		void set_param_2(bool param_2)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			param_2_ = param_2;
		}
		bool get_param_2()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return param_2_;
		}
		// name
		void set_name(std::string name)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			name_ = name;
		}
		std::string get_name()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return name_;
		}
	public:
		void put_internal_param(const InternalParam& internal_param)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			internal_param_ = internal_param;
		}
		void get_internal_param(InternalParam& right)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			right = internal_param_;
		}
	public:
		void put_sum_run_data(const SumRunData& sum_run_data)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			sum_run_data_ = sum_run_data;
		}
		void get_sum_run_data(SumRunData& right)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			right = sum_run_data_;
		}

	public:
		// g_qiut
		void set_g_qiut(bool g_qiut)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			g_qiut_ = g_qiut;
		}
		bool get_g_qiut()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return g_qiut_;
		}
	private:
		std::mutex mutex_;  // 数据互斥锁
		bool param_1_; // 容器内参数
		bool param_2_; 
		std::string name_;
		InternalParam internal_param_; // 容器内部参数(内部数据结构)---注意，必须把声明放在前面
		SumRunData sum_run_data_; // 容器内部参数(外部数据结构)
		/*
		* 建议还是把数据结构写在sin_entity_data.h的文件中
		*/
	private:
		bool g_qiut_; // entity退出标志
	};
} // namespace bsilre_entity