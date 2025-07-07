#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLDataType;
typedef struct SeqList
{
	SLDataType * arr;
	int size;
	int capacity;
}SL;

void SLPrint(SL* sl);

void SLInit(SL* sl);
void SLDestroy(SL* sl);

void SLPushBack(SL* sl, SLDataType x);
void SLPopBack(SL* sl);

void SLPushFront(SL* sl, SLDataType x);
void SLPopFront(SL* sl);

int SLFind(SL* sl, SLDataType x);

void SLInsert(SL* sl, int pos, SLDataType x);
void SLErase(SL* ps, int pos);