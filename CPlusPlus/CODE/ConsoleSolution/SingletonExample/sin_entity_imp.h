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
			bsilre_logger::Logger& logger() { return logger_; } // Ϊ�������ļ�Ҳ��д��־
	public:
		int start();
		void stop();
		void get_run_data(sin_entity::SumRunData& run_data);
		void set_run_data(sin_entity::SumRunData run_data);
		void set_other_name(std::string name, std::string ip);
		std::string get_other_name();
	public: // ��Щ�����ǽӿڣ��Ե������󿪷ŵ��ã�����һ���֣�cpp�ļ���Ҳ��һ����
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
		EntityContainer entity_container_;  // entity���������
		OtherContainer other_container_;	// other���������

	};

	typedef boost::serialization::singleton<EntityImpl> singleton_entity_impl;  // ����
} // namespace bsilre_entity