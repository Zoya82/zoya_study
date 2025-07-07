#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <ctime>
#include "list.h"
using namespace std;

void test_list1()
{
	list<int> lt1 = { 1,2,3,4 };

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;

	list<int> lt2 = { 10,2,30,5 };
	for (auto e : lt2)
		cout << e << " ";
	cout << endl;
}

void test_list2()
{
	list<int> lt1 = { 1,2,3,4 };
	lt1.assign(2, 1); //���lt������2��1

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;
}

struct A //��Ĭ�ϲ����Ĺ��캯��
{
	A(int a1 = 1, int a2 = 1) :_a1(a1), _a2(a2) {} //ֱ�ӳ�ʼ���б�ֱ�ӵ����вι��죬�����ٵ���Ĭ�Ϲ���
	int _a1;
	int _a2;
};

ostream& operator<<(ostream& os, const A& a) {
	os << "(" << a._a1 << ", " << a._a2 << ")";
	return os;
}

void test_list3()
{
	list<A> lt1;
	lt1.push_back(A(2, 2));

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;

	lt1.emplace_back(2, 2);

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;
}

void test_list4()
{
	list<int> lt1 = { 10,2,30,5,2,4,2 };

	lt1.remove(100);
	lt1.remove(5);
	lt1.remove(2);

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;
}

void test_list5()
{
	list<int> lt1 = { 10,2,30,5,2,4,2 };
	lt1.sort();

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;

	lt1.sort(greater<int>()); //�Ӵ�С����

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;
}

void test_list6()
{
	list<int> lt1 = { 10,2,30,5,2,5,5,2,4,2 };
	lt1.sort();
	lt1.unique(); //ֻ�Ƴ���������ȵ�Ԫ�أ�������һ������unique() �����Զ���������ͨ��Ҫ�ȵ��� sort()

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;
}

void test_list7()
{
	list<int> lt1 = { 1,2,3,4,5,6 };
	lt1.splice(lt1.end(), lt1, lt1.begin());

	for (auto e : lt1)
		cout << e << " ";
	cout << endl;
}

void test_op1()
{
	srand(time(0));
	const int N = 1000000;
	vector<int> v;
	list<int> lt1;

	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i; //rand()���ɵ��������Χ���ޣ���ʱ���ظ�������i������֤ÿ��Ԫ�����ٲ���ȫ��ͬ
		v.push_back(e);
		lt1.push_back(e);
	}

	int begin1 = clock();
	sort(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	lt1.sort(); //std::list�ĵ�������˫�����������֧��������ʣ���std::sortҪ��������ʵ�������list�޷�ֱ����std::sort������������ĳ�Ա����sort()��
	int end2 = clock();

	printf("vector sort:%d\n", end1 - begin1); //vector sort:341  
	printf("list sort:%d\n", end2 - begin2); //list sort : 564
}

void test_op2()
{
	srand(time(0));
	const int N = 1000;
	list<int> lt1, lt2;
	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		lt1.push_back(e);
		lt2.push_back(e);
	}

	int begin1 = clock();
	vector<int> v(lt2.begin(), lt2.end());
	sort(v.begin(), v.end());
	lt2.assign(v.begin(), v.end()); //��vector�е�Ԫ�ظ��Ƹ��ǵ�list��
	int end1 = clock();

	int begin2 = clock();
	lt1.sort();
	int end2 = clock();

	printf("list copy to vector and sort and copy to list:%d\n", end1 - begin1); //1
	printf("list sort:%d\n", end2 - begin2); //0
}

void test_zoyalist1()
{
	zoya::list<int> lt1 = { 1,2,3,4 };

	for (auto it = lt1.begin(); it != lt1.end(); ++it)
	{
		*it += 1;
		cout << *it << " ";
	}
	cout << endl;
}

void Print(const zoya::list<int>& lt)
{
	zoya::list<int>::const_iterator it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test_zotalist2()
{
	zoya::list<A> lt1;
	lt1.push_back({ 1,1 });
	lt1.push_back({ 2,2 });
	lt1.push_back({ 3,3 });
	lt1.push_back({ 4,4 });

	for (auto it = lt1.begin(); it != lt1.end(); ++it)
		cout << it->_a1 << ":" << it->_a2 << endl;

	zoya::list<int> lt2 = { 1,2,3,4 };
	Print(lt2);
}

void test_zoyalist3()
{
	zoya::list<int> lt1 = {1, 2, 3, 4};
	for (auto it = lt1.rbegin(); it != lt1.rend(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main()
{
	//test_list2();
	//test_list3();
	//test_list4();
	//test_list5();
	//test_list6();
	//test_list7();
	//test_op1();
	//test_op2();

	//test_zoyalist1();
	//test_zotalist2();
	test_zoyalist3();

	return 0;
}