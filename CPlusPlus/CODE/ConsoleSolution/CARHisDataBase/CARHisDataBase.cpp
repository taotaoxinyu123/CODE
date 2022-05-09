#include <iostream>
#include "con_mysql.h"

int main()
{
    std::cout << "operate database Hello World!\n";
    hdata::GroupRunningData group_running_data;
    group_running_data.pvid = "pvid";
    group_running_data.total_running = "total_running";
    group_running_data.month_repair = "month_repair";
    group_running_data.self_repair = "self_repair";
    group_running_data.period_repair = "period_repair";
    group_running_data.factory_repair = "factory_repair";
    group_running_data.spare = "spare";

    hdata::ReportGroupRunning group_running;
    group_running.time = "time";
    group_running.msg_id = hdata::his_data_type::E_GROUP_RUNNING_REPORT;
    group_running.version = "version";
    group_running.line_id = "line_id";
    group_running.report_id = "report_id";
    group_running.total_message = 1;
    group_running.message_sequence = 1;
    group_running.count = 1;
    group_running.group_running_data.push_back(group_running_data);

    std::list<hdata::ReportGroupRunning> lst;
    lst.push_back(group_running);

    cmysql::MysqlOperate mysql_operate;
    mysql_operate.transfer(lst);
    std::cout << "operate database end!\n";
}