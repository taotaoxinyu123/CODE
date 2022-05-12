#pragma once
#include <string>
#include <iostream>
/**
* 看之前，先去了解一简单指针的概念，simple_point_t.hpp
*/

/**
* 1.char static_name[length];此处的length必须为常量。当声明数组之后，便会开辟length大小的空间，可以用来存储数据。
*	常和memset搭配，用于初始化,然后使用sprintf_s赋值
* 2.char *是一个指针，可以指向一个字符串数组, 数组名可以作为数组的首地址。
	定义：char* name；使用 *name 可以访问指针的值。
* 3.string是stl中的一个类，你可以认为string类管理了一个char*指针，包含了一些对这个指针的操作函数，使对其操作更加安全好用。
*/
namespace char_and_string 
{
	void func1() 
	{
		char static_name[1024];
		memset(static_name, 0x00, sizeof(static_name));
		sprintf_s(static_name, "this is static_name value");
	}

	// 说真的，完全可以自己调试看一下变量内存中的值是怎么变化的。
	void func2() 
	{
		char* name; // 只是定义了指针，没有分配内存，就是不知道这个指针指向哪里，个人感觉像是个野指针。这时候对于通过指针访问数据的任何操作都是不合法的。
					// 如果想通过指针访问数据，需要开辟一块内存空间，让char指针指向该空间。例如已经存在字符数组空间。
		char static_name[1024]; // 定义了一个字符数组，具有一块1024大小的连续内存空间，这时候内存空间的值是乱的，可以调试看看。--注意关键字连续
		memset(static_name, 0x00, sizeof(static_name)); // 给1024大小的内存空间中每块空间附上0('\0'); 知道为啥赋值它了吧，这是为了方便字符串，'\0'起到了截断的作用
		sprintf_s(static_name, "this is static_name value"); // 给字符数组赋值，并且第一个参数是字符数组的首地址，这时候发现字符数组内存是：'t','h','i','s','',.......,'e','\0','\0',....,'\0'
		name = static_name; // 将指针指向字符数组首地址，呼应了上面-->如果想通过指针访问数据，需要开辟一块内存空间，让char指针指向该空间，所以name在调试器中看到的是首地址't'，但是一整个会看到"this is static_name value"字符串
		char t = name[888]; // 这个只是测试，字符指针是否可以往下指，答案是可以的
		std::cout << name; // 这个会输出"this is static_name value"
	}

}