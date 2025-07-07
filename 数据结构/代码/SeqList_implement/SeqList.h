#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>

//定义顺序表的结构

#define N 100

//静态顺序表
/*
struct SeqList
{
	int arr[N];
	int size;    //有效数据个数
};
*/

typedef int SLDataType;

//动态顺序表
typedef struct SeqList
{
	//int* arr;
	SLDataType* arr;
	int size;      //有效数据个数
	int capacity;  //当前空间大小
}SL;

//typedef struct SeqList SL;

void SLPrint(SL* ps);  //打印

//顺序表初始化
void SLInit(SL *ps);
//顺序表的销毁
void SLDestroy(SL* ps);

//顺序表的插入
void SLPushBack(SL* ps, SLDataType x);  //尾插
void SLPopBack(SL* ps);                 //尾删

void SLPushFront(SL* ps, SLDataType x); //头插
void SLPopFront(SL* ps);                //头删

int SLFind(SL* ps, SLDataType x);

//指定位置之前插⼊数据
void SLInsert(SL* ps, int pos, SLDataType x);
//删除指定位置的数据
void SLErase(SL* ps, int pos);