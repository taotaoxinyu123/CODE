#pragma once
#include <iostream>

using namespace std;
namespace simple_point_t {
	int func1()
	{
		int  var1;
		char var2[10];

		cout << "var1 �����ĵ�ַ�� ";
		cout << &var1 << endl;

		cout << "var2 �����ĵ�ַ�� ";
		cout << &var2 << endl;

		return 0;
	}

	int func2()
	{
		int  var = 20;   // ʵ�ʱ���������
		int* ip;        // ָ�����������

		ip = &var;       // ��ָ������д洢 var �ĵ�ַ

		cout << "Value of var variable: ";
		cout << var << endl;

		// �����ָ������д洢�ĵ�ַ
		cout << "Address stored in ip variable: ";
		cout << ip << endl;

		// ����ָ���е�ַ��ֵ
		cout << "Value of *ip variable: ";
		cout << *ip << endl;

		return 0;
	}
}