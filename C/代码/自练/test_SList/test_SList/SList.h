#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLDataType;
typedef struct SListNode
{
	SLDataType data;
	struct SListNode* next;
}SLNode;

void SLPrint(SLNode* phead);

void SLPushBack(SLNode** pphead, SLDataType x);
void SLPopBack(SLNode** pphead);

void SLPushFront(SLNode** pphead, SLDataType x);
void SLPopFront(SLNode** pphead);

SLNode* SLFind(SLNode* phead, SLDataType x);

void SLInsert(SLNode** pphead, SLNode* pos, SLDataType x);
void SLInsertAfter(SLNode*  pos, SLDataType x);

void SLErase(SLNode** pphead, SLNode* pos);
void SLEraseAfter(SLNode* pos);

void SListDestroy(SLNode** pphead);

SLNode* SLBuyNode(SLDataType x);