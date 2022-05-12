#pragma once
#include <iostream>
#include <boost/lexical_cast.hpp>
#include"../log/bsilre_logger.h"
#define MAX_LENGTH_EX 1024

// int与string的相互转换
void boost_transfer(bsilre_logger::Logger& logger)
{
    //int与string的相互转换--传统
    char str_temp[MAX_LENGTH_EX];
    memset(str_temp, 0x00, MAX_LENGTH_EX);
    int aa = 11;
    sprintf_s(str_temp, "%d", aa);

    std::string name = "111";
    int bb = atoi(name.c_str());

    // int与string的相互转换--stl
    const double dd = 123.12;
    std::string ss = std::to_string(dd);

}

// 强制类型转换
void force_type_convert(bsilre_logger::Logger& logger)
{
    //int与string的相互转换--boost
    const double d = 123.12;
    std::string s = boost::lexical_cast<std::string>(d);

    int a = boost::lexical_cast<int>("123");
    double b = boost::lexical_cast<double>("123.12");
}