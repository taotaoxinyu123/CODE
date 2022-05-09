#include "sin_entity_imp.h"
#include "sin_entity_manager.hpp"
#include "sin_config_manager.hpp"
#include "sin_other_manager.hpp"

namespace sin_entity {
	// 构造函数
	EntityImpl::EntityImpl():logger_("CARHisDataDeal")
	{

	}
	EntityImpl::~EntityImpl()
	{

	}
	// 方法
	int EntityImpl::start()
	{
		// 获取配置
		std::string ip, port;
		GetConfig(ip, port);
		// 启动entity的线程
		StartEntityThread(); 
		// 启动Other的线程
		StartOtherThread();
		return 0;
	}
	void EntityImpl::stop()
	{
		// 退出entity的线程
		sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // 获取单例对象
		ei.set_entity_quit(true);
		// 退出other线程
		ei.set_other_quit(true);
	}

	// 这些函数是接口，对单例对象开放调用，这是一部分，头文件中也有一部分
	void  EntityImpl::get_run_data(sin_entity::SumRunData& run_data)
	{
		entity_container_.get_sum_run_data(run_data);
	}
	void EntityImpl::set_run_data(sin_entity::SumRunData run_data)
	{
		entity_container_.put_sum_run_data(run_data);
	}
	void EntityImpl::set_other_name(std::string name, std::string ip)
	{
		other_container_.set_other(name, ip);
	}
	std::string EntityImpl::get_other_name()
	{
		return other_container_.get_name();
	}
}