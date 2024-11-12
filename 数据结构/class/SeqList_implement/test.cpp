#define _CRT_SECURE_NO_WARNINGS
#include "SeqList.h"

void SLTest()
{
	SL sl;
	SLInit(&sl);
	SLPushBack(&sl, 1);
	SLPushBack(&sl, 2);
	SLPushBack(&sl, 3);
	SLPushBack(&sl, 4);
	SLPushBack(&sl, 5);//1 2 3 4 5 
	SLPrint(&sl);

	//SLPushFront(&sl, 1);
	//SLPushFront(&sl, 2);
	//SLPushFront(&sl, 3);
	//SLPushFront(&sl, 4);
	//SLPushFront(&sl, 5);//5 4 3 2 1
	//
	//SLPopBack(&sl);
	//SLPrint(&sl);
	//SLPopBack(&sl);
	//SLPrint(&sl);
	//SLPopBack(&sl);
	//SLPrint(&sl);
	//SLPopBack(&sl);
	//SLPrint(&sl);
	//SLPopBack(&sl);
	//SLPrint(&sl);//ctrl+d快速复制

	//SLPopBack(&sl);
	//SLPrint(&sl);

	//SLPopFront(&sl);
	//SLPrint(&sl);
	//SLPopFront(&sl);
	//SLPrint(&sl);
	//SLPopFront(&sl);
	//SLPrint(&sl);
	//SLPopFront(&sl);
	//SLPrint(&sl);
	//SLPopFront(&sl);
	//SLPrint(&sl);//ctrl+d快速复制

	//SLPopFront(&sl);
	//SLPrint(&sl);
}

void SLTest02()
{
	SL sl;
	SLInit(&sl);
	SLPushBack(&sl, 1);
	SLPushBack(&sl, 2);
	SLPushBack(&sl, 3);
	SLPushBack(&sl, 4);//1 2 3 4
	SLPrint(&sl);

	//SLErase(&sl, 2);
	//SLPrint(&sl);//2 3 4

	//SLDestroy(&sl);

	SLInsert(&sl, 0, 99);//99 1 2 3 4
	SLPrint(&sl);
	SLInsert(&sl, sl.size, 88);//99 1 2 3 4 88
	//此时sl是变量，sl.size表示结构体sl的成员
	SLPrint(&sl);


	//int ret = SLFind(&sl,99);
	//if (ret < 0)
	//{
	//	printf("未找到！\n");
	//}
	//else
	//{
	//	printf("找到了！\n");
	//}
}


int main()
{
	//SLTest();
	SLTest02();
	return 0;
}

