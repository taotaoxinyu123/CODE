#pragma once
/*
* C++ 提高代码的可重用性主要有两方面： - 继承 - 模板
* 使用「模板」的特性设计，实际上也就是「泛型」程序设计
*/

/*
* 函数模板
*/

// 交换两个整型变量的值的Swap函数：
void Swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

// 交换两个double型变量的值的Swap函数:
void Swap(double& x, double& y)
{
    double tmp = x;
    x = y;
    y = tmp;
}

// 那如果是其他变量类型的值交换，那不是每次都要重新写一次 Swap 函数？是不是很繁琐？且代码后面会越来越冗余。

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
// 调用
void transfer_func_template()
{
    MyFun("arg1", "arg2");
}

/*
* 类模板
*/
template <class T>
class A
{
public:
    template<class T2>
    void Func(T2 t) { cout << t; } // 成员函数模板
};

// 调用
void transfer_class_template()
{
    A<int> a;
    a.Func('K');     //成员函数模板 Func被实例化
    a.Func("hello"); //成员函数模板 Func再次被实例化
}