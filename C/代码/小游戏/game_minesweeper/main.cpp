#define _CRT_SECURE_NO_WARNINGS

#include "game.h"


void menu() {
	//��Ϸ�˵�
	printf("******************************\n");
	printf("**********  1.play  **********\n");
	printf("**********  0.exit  **********\n");
	printf("******************************\n");
}

void game() {
	char mine[ROWS][COLS];  //������
	char show[ROWS][COLS];  //���Ų������Ϣ

	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	//�鿴��
	//DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	
	//������
	SetMine(mine, ROW, COL);
	DisplayBoard(mine, ROW, COL);
	//����
	FindMine(mine, show, ROW, COL);
}

int main() {
	int input = 0;
	srand((unsigned int)time(NULL));
	do {
		menu();
		printf("�����룺>");
		scanf("%d", &input);
		switch (input) {
			case 1:
				game();
				break;
			case 0:
				printf("�˳���Ϸ");
				break;
			default:
				printf("ѡ�����������ѡ��");
				break;
		}
	} while (input);
}