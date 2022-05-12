#pragma once
#include <iostream>
/*
* 1.�麯�������һ�������������麯��������������Ϊ������������������������п��Ա����ǣ������������Ϳ���ʹ�ö�̬�����ﵽ��̬��----����  
* 2.���麯����ֻ��һ���ӿڣ���һ����������������Ҫ����������ȥʵ�֡�
*			 ���д��麯��������������࣬���ֻ��಻��ֱ�����ɶ���ֻ�б��̳У�����д���麯���󣬲������ɶ���ʹ�á�-----����
* 3.�ص㣺��API����ĵ���; �и�˼�룬Ϊɶ�̳к���дvirtual �Ҷ�����ʵ���� �϶������˰���
*/

// �麯��
namespace basic_inherit_virtual
{
    class Character {
    public:
        virtual void attack() {}	//�麯��ʵ�ֶ�̬
        virtual void defense(); // �麯������
    };
    void Character::defense() // �麯��ʵ�֣�����д������
    {
    }

    class Warrior : public Character {
    public:
        void attack() 
        {
            std::cout << "Slash the Monster" << std::endl;	//ն������
        }
        void defense()
        {
            std::cout << "defense the Monster" << std::endl;	//��������
        }
    };

    class Magician : public Character {
        void attack() 
        {
            std::cout << "Fire the Ball" << std::endl;	//�ͷŻ���
        }
        void defense()
        {
            std::cout << "defense the Fire Ballr" << std::endl;	//��������
        }
    };

    void fun() {
        // ����Ƕ�̬
        Character* warr = new Warrior();
        warr->attack();
        warr->defense();
        Character* magi = new Magician();
        magi->attack();
        magi->defense();
    }
}

// ���麯��
namespace basic_inherit_prue_virtual
{
    class Person
    {
    public:
        virtual void func1() = 0; // ���麯������
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
        // ��д�˸���Ĵ��麯��
        void func1()
        {
            std::cout << "Child prue virtual func1" << std::endl;
        }
    };

    // interface�����Ե���API
    void fun()
    {
        Person *p = new Child();
        p->func1();
    }
}
