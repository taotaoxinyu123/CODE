#pragma once
#include <iostream>
#include"../log/bsilre_logger.h"
/*
    try-catchµÄÊ¹ÓÃ
*/
void use_try_catch(bsilre_logger::Logger& logger) {
    std::string message;
    try
    {
        int a = 1;
    }
    catch (const std::exception& ex)
    {
        message = ex.what();
    }
}