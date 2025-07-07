#include<iostream>
using namespace std;
typedef int STDataType;

typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;
void STInit(ST& rs, int n = 4)
{
	rs.a = (STDataType*)malloc(n * sizeof(STDataType));
	rs.top = 0;
	rs.capacity = n;
}

//栈顶
void STPush(ST& rs, STDataType x)
{
	//assert(rs.a);

	//满了，扩容
	if (rs.top == rs.capacity)
	{
		printf("扩容\n");
		int newcapacity = rs.capacity == 0 ? 4 : rs.capacity * 2;
		STDataType* tmp = (STDataType*)realloc(rs.a, newcapacity * sizeof(STDataType));
		if (tmp == NULL)
		{
			perror("realloc fail");
			return;
		}
		rs.a = tmp;
		rs.capacity = newcapacity;
	}
	rs.a[rs.top] = x;
	rs.top++;
}

// int STTop(ST& rs)
int& STTop(ST& rs)  //这里的STTop写别的名字也可以，总之是返回的引用，不管是多少，是什么名字，直接返回给函数STTop
{
	//assert(rs.top > 0);
	return rs.a[rs.top];
}

int main()
{
	//调⽤全局的
	ST st1;
	STInit(st1);
	STPush(st1, 1);
	STPush(st1, 2);

	cout << STTop(st1) << endl;

	STTop(st1) += 10;

	cout << STTop(st1) << endl;

	return 0;
}