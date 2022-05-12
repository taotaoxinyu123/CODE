#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>
#include <iostream>
/*
* desc:replace��ʹ�ã���Ȼstring�п⣬�Լ�������������
* replace_str(name2, "AND", "#"); ��name2���ַ��������е�AND�滻��#
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
* desc:split����stlû�У�ʹ�õ�boost������Ŀ�
* ��parttern_str�ַ���split��֣�����parttern_arr-->vector����
*/
int split_str()
{
    std::string parttern_str = "123#345#12";
    std::vector<std::string> parttern_arr;
    boost::split(parttern_arr, parttern_str, boost::is_any_of("#"), boost::token_compress_on);
    return 0;
}

/*
* desc:vectorȥ��
* ���õ�set����������
*/
int no_repeat()
{
    std::vector<std::string> vct;
    vct.push_back("12");
    vct.push_back("12");
    vct.push_back("13");
    std::set<std::string> parttern_set(vct.begin(), vct.end()); // ȥ��
    for (auto it : parttern_set)
    {
        std::cout << it << std::endl;
    }
    return 0;
}
