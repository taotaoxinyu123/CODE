#include <iostream>
#include <boost/format.hpp> 
#include <boost/lexical_cast.hpp>
#include <map>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>
#include "crc/crc_t.hpp"
#include "basic_class/inherit.hpp"
#include "basic_class/inherit_virtual.hpp"
#include "thread/thread_t.hpp"
#include "char_and_string/char_t.hpp"


// for thread
bool gQiut_tock = true;
bool gQiut_tick = true;
/*
    boost 使用单例模式 + 锁 + 共享内存的设计模式（非常经典)
    查看项目名：SingletonExample
*/

/*
    boost读取xml的配置文件；
    项目名：可以参考CARDataPublish; 参考cocc_config_manager.hpp
*/

/*
    josn字符串解析与封装
    项目名：可以参考CARHisDataDeal; 解析是在common_json.cpp里面  封装是在frame.hpp里面
*/

/*
    1）boost使用beast实现websocket的客户端和服务端：项目CARHisDataDeal; 里面有客户端和服务端,目前存在有个缺陷：就是无法做到客户端或者服务端实现发送和接受分离。有个备用的方案go可以
    2）boost使用beast实现http的服务端（客户可以使用ｈｔｍｌ但是也可以看一下怎么使用代码实现的客户端）
    3）boost使用asio实现socket客户端和服务端（使用cocc的报文）
*/

/*
   联锁的设计模式：内存模式 --- 有限变量的套圈圈 + 流程图的实现方式
*/


/*
   操作关系型数据库（原生sqlite, mysql, oracle + 封装库SQLAPI）和非关系型数据库（至少redis）
*/

/*
   专门建立一个工程来实现数据结构里面的算法、stl里面的算法（抄）、stl的容器（抄 + 注意事项：例如map.at()访问不存在的元素将会崩溃）
*/

/*
   虽然上面已经实现了单例的设计模式，但是还是存在其他的设计模式，新建一个工程学习新的设计模式
*/

/*
   这一步就显得有点遥远了，linux + boost其他库 + 简单的qt使用
   这一步就更加遥远了，选定方向：智能装备（软硬件结合之法）、图像处理、数据科学AI、测试深耕、做一个管理系统模板(这个简单一点，java？python？都有对应的框架)
*/

int main()
{
    //std::map<std::string, int> t_map;
    //t_map["1"] = 1;
    //t_map["2"] = 2;
    //t_map["2"] = 3;

    //int a = t_map.at("1");
    //int b = t_map.at("3");
    //char_and_string::func2();
    basic_inherit_virtual::fun();
    basic_inherit_prue_virtual::fun();
}

