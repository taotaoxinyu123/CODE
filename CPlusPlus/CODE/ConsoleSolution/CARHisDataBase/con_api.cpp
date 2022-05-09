#include "con_api.h"

cmysql::MysqlOperate mysql_operate;

long CON_API_TRANSFER(hdata::his_data_type type, const std::list<std::string>& lst)
{
	return mysql_operate.transfer(type, lst);
}