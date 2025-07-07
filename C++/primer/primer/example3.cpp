#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;
int main()
{
	int a = 10;

	const int& ra = 30;

	//编译报错: “初始化” :⽆法从“int”转换为“int& ”
	// int& rb = a * 3;
	const int& rb = a * 3;

	double d = 12.34;
	//编译报错：“初始化” :⽆法从“double”转换为“int& ”
	// int& rd = d;

	const int& rd = d;

	int rra = a;

	return 0;
}