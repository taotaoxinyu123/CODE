#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>
#include <iostream>
/*
* desc:replace的使用，虽然string有库，自己还是造轮子了
* replace_str(name2, "AND", "#"); 将name2的字符串种所有的AND替换成#
*/
int replace_str(std::string& src_str, const std::string& rep_src_str, const std::string& rep_dst_str)
{
    while (src_str.find(rep_src_str) != std::string::npos)
    {
        src_str = src_str.replace(src_str.find(rep_src_str), rep_src_str.size(), rep_dst_str);
    }
    return 0;
}

/*
* desc:split方法stl没有，使用的boost的里面的库
* 将parttern_str字符串split拆分，返回parttern_arr-->vector类型
*/
int split_str()
{
    std::string parttern_str = "123#345#12";
    std::vector<std::string> parttern_arr;
    boost::split(parttern_arr, parttern_str, boost::is_any_of("#"), boost::token_compress_on);
    return 0;
}

/*
* desc:vector去重
* 利用的set容器的特性
*/
int no_repeat()
{
    std::vector<std::string> vct;
    vct.push_back("12");
    vct.push_back("12");
    vct.push_back("13");
    std::set<std::string> parttern_set(vct.begin(), vct.end()); // 去重
    for (auto it : parttern_set)
    {
        std::cout << it << std::endl;
    }
    return 0;
}
