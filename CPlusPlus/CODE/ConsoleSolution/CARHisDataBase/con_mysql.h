#ifndef CON_MYSQL_H
#define CON_MYSQL_H

#include <list>
#include <string>
#include "sqlapi/SQLAPI.h"
#include "../CARHisDataDeal/cocc_his_enum.h"
namespace cmysql {
	// ��������-SQLite
	class LocalConfig
	{
	public:
		std::string db;
		std::string table;
	};
	// ��������
	class MysqlConfig
	{
	public:
		std::string dsn;
		std::string usr;
		std::string pwd;
		std::string table;
	};

	// ����mysql
	class MysqlOperate 
	{
	public:
		MysqlOperate();		
		~MysqlOperate();
	public:
		void load_config(); // ��������

		bool connect_sqlite(const std::string& file, SAConnection& con);

		bool connect_mysql(MysqlConfig& config, SAConnection& con);

		void fill_data(SACommand& cmd, hdata::his_data_type type, const std::string& item);

		void insert_data(hdata::his_data_type type, const std::list<std::string>& lst, const std::string& table, SAConnection& con);

		int transfer(hdata::his_data_type type, const std::list<std::string>& lst);

	private:
		LocalConfig local_config_;
		MysqlConfig mysql_config_; 
		SAConnection mysql_con_; 
	};
}



#endif
