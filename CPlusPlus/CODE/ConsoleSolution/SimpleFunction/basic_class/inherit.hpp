#pragma once
#include <iostream>
/*
* 1.��������Է��ʻ����е����з�˽�г�Ա��
* 2.��������Լ̳����л���ķ�����������������⣺
    ����Ĺ��캯�������������Ϳ������캯��
    ��������������
    �������Ԫ����
* 3.�����಻�ܼ̳л���Ĺ��캯��(�����ᵽ)��������ִ�й��캯��ʱ������û���Ĺ��캯����һ����˵����Ҫ�������๹�캯����ָ�����๹�캯�����ұ����ں���ͷָ�������·����ӣ�------------�������
*   ��������Է��ʻ����е����з�˽�г�Ա������Ĺ��캯����public�ģ������಻�ܼ̳л���Ĺ��캯��------------�ú������仰��������������Է��ʻ���Ĺ��캯�������ǲ�������Ϊ�Լ��ĳ�Ա��������(this) ��
* 4.�����private��Ա����ֱ�ӱ���������ʣ����ǿ���ͨ�������public��protected��Ա������------------�������
* 5.���ڶ�̳�
*/
namespace basic_inherit
{
    class Person 
    {
    public:
        Person() // Ĭ�Ϲ��캯��
        {
            age = 0;
        }
        Person(std::string name_, int age_) // ���������캯��
        {
            this->name = name_;
            this->age = age_;
        }
        ~Person() // ��������
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
        // ��������д���ǿ��Եģ��������������д��
        /*
        Child(std::string name_, int age_, std::string height_)
        {
            Person(name_, age_);
            // this->Person(name_, age_); // ���־��Ǵ����
            height = height_;
        }
        */
        ~Child()
        {

        }
    public:
        // ��д�˸���ķ���
        void work() 
        {
            // ����ֱ�ӷ���, ͨ��public�ӿڷ���
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

    // interface�����Ե���API
    void fun() 
    {
        Person person;
        person.work();
        Child child;
        child.work();
    }
}
