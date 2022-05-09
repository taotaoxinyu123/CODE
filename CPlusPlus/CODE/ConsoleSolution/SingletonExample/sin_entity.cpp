#include "sin_entity.h"
#include "sin_entity_imp.h"
namespace sin_entity {
	// 核心：全是单例访问的imp接口
	void Entity::start()
	{
		singleton_entity_impl::get_mutable_instance().start();
	}
	void Entity::stop()
	{
		singleton_entity_impl::get_mutable_instance().stop();
	}
	void Entity::do_something()
	{
		sin_entity::SumRunData run_data;
		singleton_entity_impl::get_mutable_instance().set_run_data(run_data);
	}
}// namespace bsilre_entity