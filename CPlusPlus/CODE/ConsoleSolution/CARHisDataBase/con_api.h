#ifndef CON_API_H
#define CON_API_H

#ifdef _WIN32
#	ifdef CON_API_EXPORTS
#		define CON_API __declspec(dllexport)
#	else
#		define CON_API __declspec(dllimport)
#	endif
#else
#	define CON_API
#endif
#include <list>
#include "con_mysql.h"

/**
* ��ʼ��
*
* @param type ��������
* @param obj ��Ҫ��������ݶ���
*
* @retval
*/

CON_API long CON_API_TRANSFER(hdata::his_data_type type, const std::list<std::string>& lst);

#endif

