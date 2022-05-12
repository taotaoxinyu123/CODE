#pragma once
#include <iostream>
#include <boost/format.hpp> 
#include"../log/bsilre_logger.h"
#define MAX_LENGTH_EX 1024

//传统的sprintf
void traditional_format(bsilre_logger::Logger& logger)
{
    char szBuffer[MAX_LENGTH_EX];
    memset(szBuffer, 0x00, MAX_LENGTH_EX);
    std::string first = "aa";
    std::string second = "bb";
    sprintf_s(szBuffer, "insert into t_signal(key, value) values('%s', '%s')", first.c_str(), second.c_str());
    logger.Log(szBuffer);
}

//boost的格式化
void boost_format(bsilre_logger::Logger& logger)
{
    std::string content = "ssss";
    std::string log_content;
    log_content = boost::str(boost::format("字符串[%s]，数字[%d]") % content % 2);
    logger.Log(log_content);
}