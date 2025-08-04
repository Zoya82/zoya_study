#define _CRT_SECURE_NO_WARNINGS

int main()
{
	const int a = 10;
	//编译报错：error C2440 : “初始化” :⽆法从“const int”转换为“int& ”
	//这⾥的引⽤是对a访问权限的放⼤
	//int& ra = a;
	
	//这样才可以
	const int& ra = a;
	// 编译报错：error C3892 : “ra”不能给常量赋值
	//ra++;
	
	// 这⾥的引⽤是对b访问权限的缩⼩
	int b = 20;
	const int& rb = b;
	//编译报错：error C3892 : “rb”:不能给常量赋值
	//rb++;

	return 0;
}