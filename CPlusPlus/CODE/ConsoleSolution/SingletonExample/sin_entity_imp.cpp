#include "sin_entity_imp.h"
#include "sin_entity_manager.hpp"
#include "sin_config_manager.hpp"
#include "sin_other_manager.hpp"

namespace sin_entity {
	// ���캯��
	EntityImpl::EntityImpl():logger_("CARHisDataDeal")
	{

	}
	EntityImpl::~EntityImpl()
	{

	}
	// ����
	int EntityImpl::start()
	{
		// ��ȡ����
		std::string ip, port;
		GetConfig(ip, port);
		// ����entity���߳�
		StartEntityThread(); 
		// ����Other���߳�
		StartOtherThread();
		return 0;
	}
	void EntityImpl::stop()
	{
		// �˳�entity���߳�
		sin_entity::EntityImpl& ei = sin_entity::singleton_entity_impl::get_mutable_instance(); // ��ȡ��������
		ei.set_entity_quit(true);
		// �˳�other�߳�
		ei.set_other_quit(true);
	}

	// ��Щ�����ǽӿڣ��Ե������󿪷ŵ��ã�����һ���֣�ͷ�ļ���Ҳ��һ����
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