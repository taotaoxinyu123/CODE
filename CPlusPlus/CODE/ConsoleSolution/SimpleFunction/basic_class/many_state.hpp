#pragma once
#include <iostream>
/*
* 1.多态：一种接口，多种方法。调用成员函数时，会根据调用函数的对象的类型来执行不同的函数。
    举个例子：一个父类A，一个子类B，一个子类C，都继承A；A中有个方法fun,B重写了fun，C重写了fun。
    A的对象a.fun()  B的对象b.fun()  C的对象c.fun()就做出来不同的响应
* 2. A *a = new B()  a->fun()执行的是B的方法
* 3. 多态的使用，更多在虚函数和纯虚函数，参照inherit_virtual.hpp
*/
namespace basic_many_state
{
    class Person
    {
    public:
        Person()
        {

        }
        ~Person()
        {

        }
    public:
        void work()
        {
            std::cout << "this is Person work" << std::endl;
        }
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
        void work()
        {
            std::cout << "this is Child work" << std::endl;
        }
    };

    class Man : public Person
    {
    public:
        Man()
        {

        }
        ~Man()
        {

        }
    public:
        void work()
        {
            std::cout << "this is Man work" << std::endl;
        }
    };

    // interface：测试调用API
    void fun()
    {
        // 多态 1
        Person person;
        person.work();
        Child child;
        child.work();
        Man man;
        man.work();
        // 多态 2
        Person* p = new Child();
        p->work();
    }
}
