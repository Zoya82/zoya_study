#define _CRT_SECURE_NO_WARNINGS
#include "SeqList.h"

void SLInit(SL* ps) {
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

void SLDestroy(SL* ps)
{
	if (ps->arr)
	{
		free(ps->arr);  //free之后指向的空间还在
	}
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

void SLcheckCapacity(SL* ps)
{
	//空间不够，申请空间
	if (ps->size == ps->capacity)
	{
		int newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;//三目表达式
		//空间不够-2倍增容
		SLDataType* tmp = (SLDataType*)realloc(ps->arr, newCapacity * sizeof(SLDataType));
		if (tmp == NULL)
		{
			perror("realloc fail!");
			exit(1);
		}
		ps->arr = tmp;
		ps->capacity = newCapacity;
	}
}

void SLPushBack(SL* ps, SLDataType x)
{
	////温柔的处理方式
	//if (ps == NULL)
	//{
	//	return;
	//}
	//粗暴---断言
	//为真-通过，为假-报错
	assert(ps != NULL);

	//插入数据之前先看空间够不够
	/*
	if (ps->capacity == ps->size)
	{
		//申请空间
		int newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;//三目表达式
		//空间不够-2倍增容
		SLDataType* tmp = (SLDataType*)realloc(ps->arr, newCapacity * sizeof(SLDataType));
		if (tmp == NULL)
		{
			perror("realloc fail!");
			exit(1);
		}
		ps->arr = tmp;
		ps->capacity = newCapacity;
	}*/
	SLcheckCapacity(ps);

	//ps->arr[ps->size] = x;
	//ps->size++;
	ps->arr[ps->size++] = x;
}

//头插
void SLPushFront(SL* ps, SLDataType x)
{
	assert(ps);         //等价于assert(ps != NULL)
	SLcheckCapacity(ps);
	//直接头插
	//数据整体向后挪动一位
	for (int i = ps->size; i > 0; i--)
	{
		ps->arr[i] = ps->arr[i - 1];  //arr[1] = arr[0]
	}
	ps->arr[0] = x;
	++ps->size;
}

//尾删
void SLPopBack(SL* ps)
{
	assert(ps && ps->size);

	--ps->size;
	//size直接-不影响数据的增删查改
}

//头删
void SLPopFront(SL* ps)
{
	assert(ps && ps->size);

	for (int i = 0; i < ps->size - 1; i++)
	{
		ps->arr[i] = ps->arr[i + 1];  //arr[size-2] = arr[size-1]
	}

	--ps->size;
}

void SLPrint(SL* ps)
{
	for (int i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->arr[i]);
	}
	printf("\n");
}

//指定位置之前插⼊数据
void SLInsert(SL* ps, int pos, SLDataType x)
{
	assert(ps);
	//前=：头插
	//后=：尾插
	assert(pos >= 0 && pos <= ps->size);
	//插入，空间够不够
	SLcheckCapacity(ps);
	//让pos及之后的数据整体往后挪动一位
	for (int i = ps->size; i > pos; i--)
	{
		ps->arr[i] = ps->arr[i - 1];  //arr[pos+1] = arr[pos]
	}
	ps->arr[pos] = x;
	++ps->size;
}

//删除指定位置的数据
void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(pos >= 0 && pos < ps->size);  //size处无有效数据

	for (int i = pos; i < ps->size - 1; i++)
	{
		ps->arr[i] = ps->arr[i + 1];  //arr[size-2] = arr[size-1]
	}

	--ps->size;
}

//查找x，查找到了就返回对应数据下标
int SLFind(SL* ps, SLDataType x)
{
	assert(ps);
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->arr[i] == x)
		{
			//找到了，返回下标
			return i;
		}
	}
	//没找到,返回无效下标
	return -1;
}