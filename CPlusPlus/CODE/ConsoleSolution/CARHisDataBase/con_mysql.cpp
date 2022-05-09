#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include"con_mysql.h"
#include "con_struct.hpp"
namespace cmysql {

	MysqlOperate::MysqlOperate()
	{

	}

	MysqlOperate::~MysqlOperate()
	{

	}

	void MysqlOperate::load_config()
	{

		this->local_config_.db = "ats_agent_config.db";
		this->local_config_.table = "t_agent_config";

		this->mysql_config_.dsn = "127.0.0.1@cqcocc"; // 其实这里加不加this都是一样的
		this->mysql_config_.usr = "root";
		this->mysql_config_.pwd = "baosight";
		this->mysql_config_.table = "t_cats_agent_data";

		try
		{
			SAConnection con_sqlite;
			connect_sqlite(this->local_config_.db, con_sqlite);
			std::string cmd_text = "select * from t_rdb_config limit 1";
			SACommand cmd(&con_sqlite);
			cmd.setCommandText(cmd_text.c_str());
			cmd.Execute();
			while (cmd.FetchNext())
			{
				if (!cmd.Field("fd_dsn").isNull())
				{
					this->mysql_config_.dsn = (const char*)cmd.Field("fd_dsn").asString();
				}
				if (!cmd.Field("fd_user").isNull())
				{
					this->mysql_config_.usr = (const char*)cmd.Field("fd_user").asString();
				}
				if (!cmd.Field("fd_password").isNull())
				{
					this->mysql_config_.pwd = (const char*)cmd.Field("fd_password").asString();
				}
				if (!cmd.Field("fd_table_name").isNull())
				{
					this->mysql_config_.table = (const char*)cmd.Field("fd_table_name").asString();
				}
				break;
			}

			con_sqlite.Disconnect();
		}
		catch (const SAException& ex)
		{
			
		}
		return;
	}

	bool MysqlOperate::connect_sqlite(const std::string& file, SAConnection& con)
	{
		// 连接本地config路径下的file
		std::string strFullPath = file;
		try
		{
			con.Connect(strFullPath.c_str(), "", "", SA_SQLite_Client);
			con.setAutoCommit(SA_AutoCommitOff);
		}
		catch (const SAException& ex)
		{
			return false;
		}
		return true;  // success
	}

	bool MysqlOperate::connect_mysql(MysqlConfig& config, SAConnection& con)
	{
		try
		{
			if (con.isConnected())
			{
				// 已连接
				if (con.isAlive())
				{
					//CVLog.LogMessage(LOG_LEVEL_INFO, "ConnectOracle.isAlive.");
					return true;
				}
				else
				{
					con.Disconnect();
				}
			}
			// 连接
			con.Connect(config.dsn.c_str(), config.usr.c_str(), config.pwd.c_str(), SA_MySQL_Client);
			con.setAutoCommit(SA_AutoCommitOff);
			con.setIsolationLevel(SA_ReadUncommitted);
		}
		catch (const SAException& ex)
		{
			//CVLog.LogMessage(LOG_LEVEL_ERROR, "[%s]", (const char*)ex.ErrText());
			return false;
		}
		return true;
	}

	void MysqlOperate::fill_data(SACommand& cmd, hdata::his_data_type type, const std::string& item)
	{
		time_t now = time(0);
		struct tm* ptr = localtime(&now);
		char szTimeText[1024];
		memset(szTimeText, 0x00, sizeof(szTimeText));
		sprintf_s(szTimeText, "%04d-%02d-%02d %02d:%02d:%02d", 1900 + ptr->tm_year, 1 + ptr->tm_mon, ptr->tm_mday,
			ptr->tm_hour, ptr->tm_min, ptr->tm_sec);

		cmd.Param(cmysql::sz_time).setAsString() = szTimeText;
		cmd.Param(cmysql::sz_msg_id).setAsLong() = (int)type; // 这里是枚举
		cmd.Param(cmysql::sz_content).setAsString() = item.c_str();
	}

	void MysqlOperate::insert_data(hdata::his_data_type type, const std::list<std::string>& lst, const std::string& table, SAConnection& con)
	{
		char szCmdText[2048];
		memset(szCmdText, 0x00, sizeof(szCmdText));
		sprintf_s(szCmdText, "insert into %s (%s, %s, %s, %s) \
					   values(:%s, :%s, :%s, :%s)",
			table.c_str(),
			cmysql::sz_time, cmysql::sz_msg_id, cmysql::sz_content, cmysql::sz_spare,
			cmysql::sz_time, cmysql::sz_msg_id, cmysql::sz_content, cmysql::sz_spare);
		std::list<std::string>::const_iterator it;
		for (it = lst.begin(); it != lst.end(); ++it)
		{
			const std::string& item = *it;
			SACommand cmd(&con);
			cmd.setCommandText(szCmdText);
			fill_data(cmd, type, item);
			cmd.Execute();
		}
	}

	int MysqlOperate::transfer(hdata::his_data_type type, const std::list<std::string>& lst)
	{
		int ret = 0;
		try
		{
			load_config();
			connect_mysql(this->mysql_config_, this->mysql_con_);
			insert_data(type, lst, this->mysql_config_.table, this->mysql_con_);
			this->mysql_con_.Commit();
			ret = 0;
		}
		catch (const SAException& ex)
		{
			//CVLog.LogMessage(LOG_LEVEL_ERROR, "[%s]", (const char*)ex.ErrText());
			std::string err_text = (const char*)ex.ErrText();
			ret = -1;
		}
		return ret;
	}




} // namespace