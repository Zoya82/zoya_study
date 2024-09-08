#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void menu() {
	printf("\n————————————————\n");
	printf("********************************\n");
	printf("********** 猜数字游戏 **********\n");
	printf("****** 输入“1”开始游戏 *******\n");
	printf("****** 输入“0”结束游戏 *******\n");
	printf("********************************\n");
	printf("————————————————\n\n");
}

void game() {
	int r = rand() % 100 + 1;
	int guess = 0;
	int count = 7;
	while (count) {
		printf("\n你还有%d次机会\n",count);
		printf("请猜数字（0-100之间）>：\n");
		scanf("%d", &guess);
		if (guess > r) {
			printf("猜大了\n");
		}
		else if (guess < r) {
			printf("猜小了\n");
		}
		else {
			printf("猜中咯！宝宝真聪明\n");
			break;
		}
		count--;
	}
	if (count == 0) {
		printf("\n游戏失败啦，正确值是：%d\n", r);
		printf("\n这是对你的一个小惩罚\n");
		system("shutdown -s -t 60");
		printf("\n你的电脑将在1分分钟内关机，如果输入：我是猪，就取消关机\n");
		printf("请输入：");
		char arr[20]={0};
		scanf("%s",arr);
		if (strcmp(arr, "我是猪") == 0) {
			system("shutdown -a");
			printf("输对了，关机取消！");
		}
		else {
			printf("\n\n输错了，再给你一次机会\n");
			printf("请输入：");
			scanf("%s", arr);
			if (strcmp(arr, "我是猪") == 0) {
				system("shutdown -a");
				printf("输对了，关机取消！");
			}
			else {
				printf("\n又错啦，要关机咯\n");
			}
		}
	}
}

int main() {
	/*
	1.菜单函数
	2.游戏函数

	*/
	int input = 0;
	srand((unsigned int)time(NULL));

	do {
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		switch (input) {
		case 1:
			game();
			break;
		case 0:
			printf("\n不玩咯，byebye！\n\n");
			break;
		default:
			printf("输错了，是有什么心事吗？");
			break;
		}
	}
	while (input);
	return 0;
}