#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SLTDataType;
//定义链表结点的结构
typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;

void SLTPrint(SLTNode* phead);

//尾插
void SLTPushBack(SLTNode** pphead, SLTDataType x);
//头插
void SLTPushFront(SLTNode** pphead, SLTDataType x);
//尾删
void SLTPopBack(SLTNode** pphead);
//头删
void SLTPopFront(SLTNode** pphead);

//查找
SLTNode* SLTFind(SLTNode* phead, SLTDataType x);

//在指定位置之前插⼊数据 
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x);
//在指定位置之后插⼊数据
void SLTInsertAfter(SLTNode* pos, SLTDataType x);  //用不到头结点

//删除pos结点
void SLTErase(SLTNode** pphead, SLTNode* pos);
//删除pos之后的结点
void SLTEraseAfter(SLTNode* pos);

//销毁链表
void SListDestroy(SLTNode** pphead);

SLTNode* SLTBuyNode(SLTDataType x);