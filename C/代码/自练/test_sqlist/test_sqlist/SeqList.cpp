#include "SeqList.h"

void SLInit(SL* sl)
{
	sl->arr = NULL;
	sl->size = sl->capacity = 0;
}

void SLDestroy(SL* sl)
{
	if (sl->arr) //避免释放空指针
	{
		free(sl->arr);
	}
	sl->arr = NULL;
	sl->size = sl->capacity = 0;
}

void SLPrint(SL* sl)
{
	for (int i = 0; i < sl->size; i++)
	{
		printf("%d ", sl->arr[i]);
	}
}

void SLcheckCapacity(SL* sl)
{
	if (sl->size == sl->capacity)
	{
		int newCapacity = sl->capacity == 0 ? 4 : sl->capacity * 2;
		SLDataType* tmp = (SLDataType*)realloc(sl->arr, newCapacity * sizeof(SLDataType));
		if (tmp == NULL)
		{
			perror("realloc fail!");
		}
		sl->arr = tmp;
		sl->capacity = newCapacity;
	}
}

void SLPushBack(SL* sl,SLDataType x)
{
	assert(sl != NULL);
	SLcheckCapacity(sl);
	sl->arr[sl->size++] = x;
}

void SLPopBack(SL* sl)
{
	assert(sl && sl->size);
	//确保指针有效的同时，序列不为空，否则在这种情况下执行--sl->size，会导致sl->size变成负数，这样是非法的状态
	--sl->size; //如果用sl->size--，会先返回sl->size的值，再--
}

void SLPushFront(SL* sl, SLDataType x)
{
	assert(sl);
	SLcheckCapacity(sl);
	for (int i = sl->size; i > 0; i--)
	{
		sl->arr[i] = sl->arr[i - 1];
	}
	sl->arr[0] = x;
	++sl->size;
}

void SLPopFront(SL* sl)
{
	assert(sl && sl->size);
	for (int i = 0; i < sl->size - 1; i++)
	{
		sl->arr[i] = sl->arr[i + 1];
	}
	--sl->size;
}

void SLPrint(SL* sl)
{
	for (int i = 0; i < sl->size; i++)
	{
		printf("%d ", sl->arr[i]);
	}
	printf("\n");
}

void SLInsert(SL* sl, int pos, SLDataType x)
{
	assert(sl);
	assert(pos > 0 && pos <= sl->size);
	SLcheckCapacity(sl);
	for (int i = sl->size; i > pos; i--)
	{
		sl->arr[i] = sl->arr[i - 1];
	}
	sl->arr[pos] = x;
	++sl->size;
}

void SLErase(SL* sl, int pos)
{
	assert(sl && sl->size);
	assert(pos > 0 && pos <= sl->size);
	for (int i = pos; i < sl->size - 1; i++)
	{
		sl->arr[i] = sl->arr[i + 1];
	}
	--sl->size;
}

int SLFind(SL* sl, SLDataType x)
{
	assert(sl && sl->size);
	for (int i = 0; i < sl->size; i++)
	{
		if (sl->arr[i] = x)
		{
			return i;
		}
	}
	return -1;
}