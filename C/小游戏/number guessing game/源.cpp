#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void menu() {
	printf("\n��������������������������������\n");
	printf("********************************\n");
	printf("********** ��������Ϸ **********\n");
	printf("****** ���롰1����ʼ��Ϸ *******\n");
	printf("****** ���롰0��������Ϸ *******\n");
	printf("********************************\n");
	printf("��������������������������������\n\n");
}

void game() {
	int r = rand() % 100 + 1;
	int guess = 0;
	int count = 7;
	while (count) {
		printf("\n�㻹��%d�λ���\n",count);
		printf("������֣�0-100֮�䣩>��\n");
		scanf("%d", &guess);
		if (guess > r) {
			printf("�´���\n");
		}
		else if (guess < r) {
			printf("��С��\n");
		}
		else {
			printf("���п������������\n");
			break;
		}
		count--;
	}
	if (count == 0) {
		printf("\n��Ϸʧ��������ȷֵ�ǣ�%d\n", r);
		printf("\n���Ƕ����һ��С�ͷ�\n");
		system("shutdown -s -t 60");
		printf("\n��ĵ��Խ���1�ַ����ڹػ���������룺��������ȡ���ػ�\n");
		printf("�����룺");
		char arr[20]={0};
		scanf("%s",arr);
		if (strcmp(arr, "������") == 0) {
			system("shutdown -a");
			printf("����ˣ��ػ�ȡ����");
		}
		else {
			printf("\n\n����ˣ��ٸ���һ�λ���\n");
			printf("�����룺");
			scanf("%s", arr);
			if (strcmp(arr, "������") == 0) {
				system("shutdown -a");
				printf("����ˣ��ػ�ȡ����");
			}
			else {
				printf("\n�ִ�����Ҫ�ػ���\n");
			}
		}
	}
}

int main() {
	/*
	1.�˵�����
	2.��Ϸ����

	*/
	int input = 0;
	srand((unsigned int)time(NULL));

	do {
		menu();
		printf("��ѡ��>");
		scanf("%d", &input);
		switch (input) {
		case 1:
			game();
			break;
		case 0:
			printf("\n���濩��byebye��\n\n");
			break;
		default:
			printf("����ˣ�����ʲô������");
			break;
		}
	}
	while (input);
	return 0;
}