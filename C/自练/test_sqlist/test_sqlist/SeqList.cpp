#include "SeqList.h"

void SLInit(SL* sl)
{
	sl->arr = NULL;
	sl->size = sl->capacity = 0;
}

void SLDestroy(SL* sl)
{
	if (sl->arr) //�����ͷſ�ָ��
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
	//ȷ��ָ����Ч��ͬʱ�����в�Ϊ�գ����������������ִ��--sl->size���ᵼ��sl->size��ɸ����������ǷǷ���״̬
	--sl->size; //�����sl->size--�����ȷ���sl->size��ֵ����--
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