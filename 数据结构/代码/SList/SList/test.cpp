#define _CRT_SECURE_NO_WARNINGS

#include"SList.h"

void test()
{
	//手动构造一个链表
	SLTNode* node1 = (SLTNode*)malloc(sizeof(SLTNode));
	SLTNode* node2 = (SLTNode*)malloc(sizeof(SLTNode));
	SLTNode* node3 = (SLTNode*)malloc(sizeof(SLTNode));
	SLTNode* node4 = (SLTNode*)malloc(sizeof(SLTNode));

	node1->data = 1;
	node2->data = 2;
	node3->data = 3;
	node4->data = 4;

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;

	SLTNode* plist = node1;
	SLTPrint(plist);
}

void test01()
{
	SLTNode* plist = NULL;
	SLTPushBack(&plist, 1);
	SLTPushBack(&plist, 2);
	SLTPushBack(&plist, 3);
	SLTPushBack(&plist, 4);
	SLTPrint(plist);
	//SLTPushFront(&plist, 1);
	//SLTPushFront(&plist, 2);
	//SLTPushFront(&plist, 3);
	//SLTPushFront(&plist, 4);
	//SLTPrint(plist);
	//SLTPopBack(&plist);
	//SLTPrint(plist);
	//SLTPopBack(&plist);
	//SLTPrint(plist);
	//SLTPopBack(&plist);
	//SLTPrint(plist);
	//SLTPopBack(&plist);
	//SLTPrint(plist);
	//
	//SLTPopFront(&plist);
	//SLTPrint(plist);
	//SLTPopFront(&plist);
	//SLTPrint(plist);
	//SLTPopFront(&plist);
	//SLTPrint(plist);
	//SLTPopFront(&plist);
	//SLTPrint(plist);
	//SLTPopFront(&plist);
	//SLTPrint(plist);

	SLTNode* find = SLTFind(plist, 4);
	//if (find == NULL)
	//{
	//	printf("未找到！\n");
	//}
	//else
	//{
	//	printf("找到了！\n");
	//}
	//SLTInsert(&plist, find, 88);//1 88 2 3 4
	//SLTInsertAfter(find, 88);//1 2 88 3 4
	//SLTErase(&plist, find);
	//SLTEraseAfter(find);//1 3 4
	SListDestroy(&plist);
	SLTPrint(plist);
}

struct ListNode {
	int val;//data
	struct ListNode* next;
};
typedef struct ListNode ListNode;
struct ListNode* removeElements(struct ListNode* head, int val) {
	ListNode* newHead, * newTail;
	newHead = newTail = NULL;

	ListNode* pcur = head;
	while (pcur)
	{
		//找值不为val的结点尾插到新链表中
		if (pcur->val != val)
		{
			//尾插
			if (newHead == NULL)
			{
				//链表为空
				newHead = newTail = pcur;
			}
			else {
				//链表不为空
				newTail->next = pcur;
				newTail = newTail->next;
			}
		}
		pcur = pcur->next;
	}
	return newHead;
}

void test02()
{
	ListNode* node1 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* node2 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* node3 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* node4 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* node5 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* node6 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* node7 = (ListNode*)malloc(sizeof(ListNode));

	node1->val = 1;
	node2->val = 2;
	node3->val = 6;
	node4->val = 3;
	node5->val = 4;
	node6->val = 5;
	node7->val = 6;

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = NULL;

	ListNode* plist = node1;

	removeElements(plist, 6);
}

int main()
{
	//test();
	//test01();
	test02();
	return 0;
}