#define _CRT_SECURE_NO_WARNINGS

#include"SList.h"

void SLTPrint(SLTNode* phead)
{
	SLTNode* pcur = phead;
	while (pcur != NULL)
	{
		printf("%d -> ", pcur->data);  //第一次：1->
		pcur = pcur->next;  //2的地址覆盖掉pcur之前指向的1的地址，即pcur指向2
	}
	printf("NULL\n");
}

SLTNode* SLTBuyNode(SLTDataType x)  //申请一个新节点
{
	SLTNode* node = (SLTNode*)malloc(sizeof(SLTNode));
	if (node == NULL)  //为空，则申请失败
	{
		perror("malloc fail!\n");
		exit(1);
	}
	node->data = x;
	node->next = NULL;

	return node;
}

//尾插
void SLTPushBack(SLTNode** pphead, SLTDataType x)  //二级指针接收一级指针的地址
{
	assert(pphead);
	SLTNode* newnode = SLTBuyNode(x);
	if (*pphead == NULL)  //空链表
	{
		*pphead = newnode;
	}
	else {  //非空链表
		//链表非空，找尾结点
		SLTNode* ptail = *pphead;
		while (ptail->next)//等价于ptail->next != NULL
		{                  //当写为ptail!=NULL时，当停止时已指向一个新的空的节点，而不是尾结点
			ptail = ptail->next;
		}
		//ptail newnode
		ptail->next = newnode;
	}
}
void SLTPushFront(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode* newnode = SLTBuyNode(x);
	//newnode *pphead
	newnode->next = *pphead;  //新结点指向的地址为头结点
	*pphead = newnode;  //新结点的地址覆盖掉头结点的地址，即新结点成为新的头结点
}
//尾删
void SLTPopBack(SLTNode** pphead)
{
	assert(pphead && *pphead);  //pphead是有效指针（指向一个有效的头指针），否则无法正确操作链表，会崩溃
	//只有一个结点的情况        //*pphead，确保二级指针pphead指向的头指针不是NULL，即链表非空
	if ((*pphead)->next == NULL)  //箭头的优先级高于*
	{
		free(*pphead);
		*pphead = NULL;
	}
	else {
		SLTNode* prev = NULL;
		SLTNode* ptail = *pphead;

		while (ptail->next)  //找尾
		{
			prev = ptail;
			ptail = ptail->next;
		}
		//prev ptail
		prev->next = NULL;  //将最后一个节点与链表断开，防止出现野指针
		free(ptail);
		ptail = NULL;
	}
}

//头删
void SLTPopFront(SLTNode** pphead)
{
	assert(pphead && *pphead);

	SLTNode* next = (*pphead)->next;  //先标记第二个节点的位置，且箭头操作符优先级高，所以加括号
	free(*pphead);
	*pphead = next;
}

//查找
SLTNode* SLTFind(SLTNode* phead, SLTDataType x)
{
	SLTNode* pcur = phead;
	while (pcur) //pcur != NULL，无论pcur如何变化，不影响phead
	{
		if (pcur->data == x)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	//pcur==NULL，未找到
	return NULL;
}
//在指定位置之前插⼊数据
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)  //有可能在第一个结点前插入数据，即改变头结点，所以传入** pphead
{
	assert(pphead && pos);  //链表不能为空，pos也不能为空
	//当pos就是头结点时，相当于头插
	if (pos == *pphead)
	{
		SLTPushFront(pphead, x);
	}
	else {
		SLTNode* newnode = SLTBuyNode(x);
		SLTNode* prev = *pphead;
		while (prev->next != pos)  //如果prev的下一个结点时pos，则停止循环
		{
			prev = prev->next;
		}
		//prev newnode pos
		newnode->next = pos;
		prev->next = newnode;
	}
}

//在指定位置之后插⼊数据
void SLTInsertAfter(SLTNode* pos, SLTDataType x)
{
	assert(pos);
	SLTNode* newnode = SLTBuyNode(x);
	//pos newnode -> (pos->next)
	newnode->next = pos->next;  
	pos->next = newnode;  //如果先执行这句，则和下一个的链接就断了，无法再找到下一个结点
}

//删除pos结点
void SLTErase(SLTNode** pphead, SLTNode* pos)
{
	assert(pphead && pos);
	//要删除的节点就是头结点
	if (pos == *pphead)
	{
		SLTPopFront(pphead);
	}
	else {
		SLTNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}
		//prev pos pos->next
		prev->next = pos->next;
		free(pos);
		pos = NULL;
	}
}
//删除pos之后的结点
void SLTEraseAfter(SLTNode* pos)
{
	assert(pos && pos->next);
	//pos->next=pos->next->next  直接这样，就断开了与中间结点的链接，出现野指针
	SLTNode* del = pos->next;
	//pos del del->next
	pos->next = del->next;
	free(del);
	del = NULL;
}
//销毁链表
void SListDestroy(SLTNode** pphead)
{
	SLTNode* pcur = *pphead;
	while (pcur)
	{
		SLTNode* next = pcur->next;  //存储下一个的地址
		free(pcur);
		pcur = next;
	}
	*pphead = NULL;
}