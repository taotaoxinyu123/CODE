#pragma once
#include <iostream>
/*
* 1.虚函数：如果一个类中声明了虚函数，它的作用是为了能让这个函数在它的子类中可以被覆盖，这样编译器就可以使用动态绑定来达到多态。----常用  
* 2.纯虚函数：只是一个接口，是一个函数的声明，它要留到子类中去实现。
*			 带有纯虚函数的类叫做抽象类，这种基类不能直接生成对象，只有被继承，且重写其虚函数后，才能生成对象使用。-----常用
* 3.重点：看API那里的调用; 有个思想，为啥继承后不再写virtual 我都具体实现了 肯定不虚了啊。
*/

// 虚函数
namespace basic_inherit_virtual
{
    class Character {
    public:
        virtual void attack() {}	//虚函数实现多态
        virtual void defense(); // 虚函数声明
    };
    void Character::defense() // 虚函数实现，两种写法罢了
    {
    }

    class Warrior : public Character {
    public:
        void attack() 
        {
            std::cout << "Slash the Monster" << std::endl;	//斩击怪物
        }
        void defense()
        {
            std::cout << "defense the Monster" << std::endl;	//防卫怪物
        }
    };

    class Magician : public Character {
        void attack() 
        {
            std::cout << "Fire the Ball" << std::endl;	//释放火球
        }
        void defense()
        {
            std::cout << "defense the Fire Ballr" << std::endl;	//防卫火球
        }
    };

    void fun() {
        // 这就是多态
        Character* warr = new Warrior();
        warr->attack();
        warr->defense();
        Character* magi = new Magician();
        magi->attack();
        magi->defense();
    }
}

// 纯虚函数
namespace basic_inherit_prue_virtual
{
    class Person
    {
    public:
        virtual void func1() = 0; // 纯虚函数声明
    };

    class Child : public Person
    {
    public:
        Child()
        {

        }
        ~Child()
        {

        }
    public:
        // 重写了父类的纯虚函数
        void func1()
        {
            std::cout << "Child prue virtual func1" << std::endl;
        }
    };

    // interface：测试调用API
    void fun()
    {
        Person *p = new Child();
        p->func1();
    }
}
