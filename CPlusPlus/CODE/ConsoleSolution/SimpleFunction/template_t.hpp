#pragma once
/*
* C++ ��ߴ���Ŀ���������Ҫ�������棺 - �̳� - ģ��
* ʹ�á�ģ�塹��������ƣ�ʵ����Ҳ���ǡ����͡��������
*/

/*
* ����ģ��
*/

// �����������ͱ�����ֵ��Swap������
void Swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

// ��������double�ͱ�����ֵ��Swap����:
void Swap(double& x, double& y)
{
    double tmp = x;
    x = y;
    y = tmp;
}

// ������������������͵�ֵ�������ǲ���ÿ�ζ�Ҫ����дһ�� Swap �������ǲ��Ǻܷ������Ҵ�������Խ��Խ���ࡣ

template <class T>
void Swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <class T1, class T2>
T2 MyFun(T1 arg1, T2 arg2)
{
    cout << arg1 << " " << arg2 << endl;
    return arg2;
}
// ����
void transfer_func_template()
{
    MyFun("arg1", "arg2");
}

/*
* ��ģ��
*/
template <class T>
class A
{
public:
    template<class T2>
    void Func(T2 t) { cout << t; } // ��Ա����ģ��
};

// ����
void transfer_class_template()
{
    A<int> a;
    a.Func('K');     //��Ա����ģ�� Func��ʵ����
    a.Func("hello"); //��Ա����ģ�� Func�ٴα�ʵ����
}