#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

typedef struct ListNodeC
{
	struct ListNodeC* next;
	int val;
}LTNode;

struct ListNodeCPP
{
	void Init(int x)
	{
		next = nullptr;
		val = x;
	}
	ListNodeCPP* next;
	int val;
};
int main()
{
	return 0;
}