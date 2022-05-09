#ifndef COCC_LOAD_DATABASE_HPP
#define COCC_LOAD_DATABASE_HPP
#include "sqlite3.h"
#include <string>
#include <list>
#include "cocc_publish_impl.h"
namespace pdatabase 
{
	void load(const std::string& db, const std::string& table, std::map<std::string, int>& map_d) throw(std::exception)
	{
		map_d.clear();
		sqlite3* db_ptr = NULL;
		int err = 0;
		err = sqlite3_open(db.c_str(), &db_ptr);
		if (SQLITE_OK != err) throw(std::string("sqlite3_open"));

		char sz[1024];
		memset(sz, 0x00, 1024);
		sprintf_s(sz, "select fd_train_id_x, fd_train_id from %s", table.c_str());
		sqlite3_stmt* stmt = NULL;
		int ret = sqlite3_prepare_v2(db_ptr, sz, -1, &stmt, NULL);
		if (SQLITE_OK != sqlite3_prepare_v2(db_ptr, sz, -1, &stmt, NULL)) throw(std::string("sqlite3_prepare_v2"));

		while (SQLITE_ROW == sqlite3_step(stmt))
		{
			const unsigned char* sz_train_id_x = sqlite3_column_text(stmt, 0);
			std::string train_id_x= reinterpret_cast<const char*>(sz_train_id_x);
			int sz_train_id = sqlite3_column_int(stmt, 1);
			int train_id = sz_train_id;
			map_d[train_id_x] = train_id; // add 
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db_ptr);
	}

	int load_static_data() 
	{
		std::map<std::string, int> train_id_lst;
		load("train_id_config.db", "t_train_config", train_id_lst);
		pubdata::CoccPublishImpl& pi = pubdata::singleton_coccpublish_impl::get_mutable_instance();
		pi.set_trip_id_lst_imp(train_id_lst);
		return 0;
	}
}

#endif
