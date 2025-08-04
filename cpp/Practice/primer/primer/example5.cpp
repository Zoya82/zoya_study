#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//inline int Add(int x, int y)
//{
//	int ret = x + y;
//	ret += 1;
//	ret += 1;
//	ret += 1;
//	return ret;
//}
//int main()
//{
//
//	int ret = Add(1, 2);
//	cout << Add(1, 2) * 5 << endl;
//	return 0;
//}

#define ADD(a, b) ((a) + (b))

int main()
{
	int ret = ADD(1, 2);
	cout << ADD(1, 2) << endl;
	cout << ADD(1, 2) * 5 << endl;
	int x = 1, y = 2;
	ADD(x & y, x | y);  // -> (x&y+x|y)
	return 0;
}