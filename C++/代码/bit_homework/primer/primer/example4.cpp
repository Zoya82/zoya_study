#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;
void f(int x)
{
	cout << "f(int x)" << endl;
}
void f(int* ptr)
{
	cout << "f(int* ptr)" << endl;
}
int main()
{
	f(0);
	//����ͨ��f(NULL)��?ָ��汾��f(int*)��������������NULL�������0����?��f(int x)����������ĳ�����㣡�

	f(NULL);
	f((int*)NULL);

	// ���뱨��error C2665 : ��f��: 2��������û��?������ת�����в�������
	// f((void*)NULL);

	f(nullptr);
	return 0;
}