#pragma once
#include <iostream>
/*
* 1.��̬��һ�ֽӿڣ����ַ��������ó�Ա����ʱ������ݵ��ú����Ķ����������ִ�в�ͬ�ĺ�����
    �ٸ����ӣ�һ������A��һ������B��һ������C�����̳�A��A���и�����fun,B��д��fun��C��д��fun��
    A�Ķ���a.fun()  B�Ķ���b.fun()  C�Ķ���c.fun()����������ͬ����Ӧ
* 2. A *a = new B()  a->fun()ִ�е���B�ķ���
* 3. ��̬��ʹ�ã��������麯���ʹ��麯��������inherit_virtual.hpp
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

    // interface�����Ե���API
    void fun()
    {
        // ��̬ 1
        Person person;
        person.work();
        Child child;
        child.work();
        Man man;
        man.work();
        // ��̬ 2
        Person* p = new Child();
        p->work();
    }
}
