#pragma once
#include <iostream>
/*
* 1.派生类可以访问基类中的所有非私有成员。
* 2.派生类可以继承所有基类的方法，但下列情况除外：
    基类的构造函数，析构函数和拷贝构造函数
    基类的重载运算符
    基类的友元函数
* 3.派生类不能继承基类的构造函数(上述提到)，派生类执行构造函数时，会调用基类的构造函数，一般来说，需要在派生类构造函数中指明基类构造函数，且必须在函数头指明。（下方例子）------------这个常用
*   派生类可以访问基类中的所有非私有成员，基类的构造函数是public的，派生类不能继承基类的构造函数------------好好理解这句话（就是派生类可以访问基类的构造函数，但是不可以作为自己的成员函数访问(this) ）
* 4.基类的private成员不能直接被派生类访问，但是可以通过基类的public和protected成员来访问------------这个常用
* 5.存在多继承
*/
namespace basic_inherit
{
    class Person 
    {
    public:
        Person() // 默认构造函数
        {
            age = 0;
        }
        Person(std::string name_, int age_) // 带参数构造函数
        {
            this->name = name_;
            this->age = age_;
        }
        ~Person() // 析构函数
        {

        }
    public:
        void work() 
        {
            this->name = "Pname";
            this->age = 100;
            std::cout << "Person name:"<< this->name <<std::endl;
            std::cout << "Person age:" << this->age << std::endl;
        }
        std::string get_name()
        {
            return this->name;
        }
        void set_name(std::string name)
        {
            this->name = name;
        }
        int get_age()
        {
            return this->age;
        }
        void set_age(int age)
        {
            this->age = age;
        }
    private:
        std::string name;
        int age;
    };

    class Child : public Person
    {
    public:
        Child() 
        {

        }
        Child(std::string name_, int age_, std::string height_): Person(name_, age_), height(height_)
        {

        }
        // 下面这种写法是可以的，不过常用上面的写法
        /*
        Child(std::string name_, int age_, std::string height_)
        {
            Person(name_, age_);
            // this->Person(name_, age_); // 这种就是错误的
            height = height_;
        }
        */
        ~Child()
        {

        }
    public:
        // 重写了父类的方法
        void work() 
        {
            // 不能直接访问, 通过public接口访问
            //std::cout << "Person name:" << this->name << std::endl;
            //std::cout << "Person age:" << this->age << std::endl;
            this->set_name("Cname");
            this->set_age(10);
            std::cout << "Child name:" << this->get_name() << std::endl;
            std::cout << "Child age:" << this->get_age() << std::endl;
        }
    private:
        std::string height;
    };

    // interface：测试调用API
    void fun() 
    {
        Person person;
        person.work();
        Child child;
        child.work();
    }
}
