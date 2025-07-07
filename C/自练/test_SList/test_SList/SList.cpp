#include "SList.h"

void SLPrint(SLNode* phead)
{
	SLNode* pcur = phead;
	while (pcur != NULL)
	{
		printf("%d ", pcur->data);
		pcur = pcur->next;
	}
	printf("NULL\n");
}

SLNode* SLBuyNode(SLDataType x)
{
	SLNode* node = (SLNode*)malloc(sizeof(SLNode));
	if (node == NULL)
	{
		perror("malloc fail!\n");
		exit(1);
	}
	node->data = x;
	node->next = NULL;

	return node;
}

void SLPushBack(SLNode** pphead, SLDataType x)
{
	assert(pphead);  //pphead存在，即头指针存在，但头指针可能为空
	SLNode* newnode = SLBuyNode(x);
	if (*pphead = NULL)
	{
		*pphead = newnode;
	}
	else
	{
		SLNode* ptail = *pphead;
		while (ptail->next)
		{
			ptail = ptail->next;
		}
		ptail->next = newnode;
	}
}

void SLPopBack(SLNode** pphead)
{
	assert(pphead && *pphead);
	if ((*pphead)->next = NULL) //只有一个结点
	{
		free(*pphead);
		*pphead = NULL; //头指针为空，即不再指向下一个地址
	}
	else
	{
		SLNode* prev = NULL;
		SLNode* ptail = *pphead;

		while (ptail->next)
		{
			prev = ptail;
			ptail = ptail->next;
		}
		prev->next = NULL;
		free(ptail);
		ptail = NULL;
	}
}

void SLPushFront(SLNode** pphead, SLDataType x)
{
	assert(pphead);
	SLNode* newnode = SLBuyNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}

void SLPopFront(SLNode** pphead)
{
	assert(pphead && *pphead);
	SLNode* next = (*pphead)->next;
	free(*pphead);
	*pphead = next;
}

SLNode* SLFind(SLNode* phead, SLDataType x)
{
	assert(phead);
	SLNode* pcur = phead;
	while (pcur)
	{
		if (pcur->data == x)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	return NULL;
}

void SLInsert(SLNode** pphead,SLNode* pos, SLDataType x)
{
	assert(pphead && pos);
	if (pos = *pphead)
	{
		SLPushFront(pphead, x);
	}
	else
	{
		SLNode* newnode = SLBuyNode(x);
		SLNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}
		newnode->next = pos;
		prev->next = newnode;
	}
}

void SLInsert(SLNode* pos, SLDataType x)
{
	assert(pos);
	SLNode* newnode = SLBuyNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}

void SLErase(SLNode** pphead, SLNode* pos)
{
	assert(pphead && *pphead && pos);
	if (*pphead == pos)
	{
		SLPopFront(pphead);
	}
	else
	{
		SLNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}
		prev->next = pos->next;
		free(pos);
		pos = NULL;
	}
}

void SLEraseAfter(SLNode* pos)
{
	assert(pos);
	SLNode* del = pos->next;
	pos->next = del->next;
	free(del);
	del = NULL;
}

