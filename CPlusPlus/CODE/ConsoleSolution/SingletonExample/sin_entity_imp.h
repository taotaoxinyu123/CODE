#pragma once
#include "bsilre_logger.h"
#include "boost/serialization/singleton.hpp"
#include "sin_entity_container.hpp"
#include "sin_other_container.hpp"
namespace sin_entity {
	class EntityImpl
	{
	public:
		EntityImpl();
		~EntityImpl();
	public:
			bsilre_logger::Logger& logger() { return logger_; } // 为了其他文件也能写日志
	public:
		int start();
		void stop();
		void get_run_data(sin_entity::SumRunData& run_data);
		void set_run_data(sin_entity::SumRunData run_data);
		void set_other_name(std::string name, std::string ip);
		std::string get_other_name();
	public: // 这些函数是接口，对单例对象开放调用，这是一部分，cpp文件中也有一部分
		void set_entity_quit(bool g_qiut)
		{
			logger_.Log("set_entity_quit");
			entity_container_.set_g_qiut(g_qiut);
		}
		bool get_entity_quit()
		{
			return entity_container_.get_g_qiut();
		}

		void set_other_quit(bool t_qiut)
		{
			logger_.Log("set_other_quit");
			other_container_.set_t_qiut(t_qiut);
		}
		bool get_other_quit()
		{
			return other_container_.get_t_qiut();
		}

	private:
		bsilre_logger::Logger logger_;
		EntityContainer entity_container_;  // entity共享的数据
		OtherContainer other_container_;	// other共享的数据

	};

	typedef boost::serialization::singleton<EntityImpl> singleton_entity_impl;  // 单例
} // namespace bsilre_entity