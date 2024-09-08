#define _CRT_SECURE_NO_WARNINGS

#include "game.h"


void menu() {
	//游戏菜单
	printf("******************************\n");
	printf("**********  1.play  **********\n");
	printf("**********  0.exit  **********\n");
	printf("******************************\n");
}

void game() {
	char mine[ROWS][COLS];  //布置雷
	char show[ROWS][COLS];  //放排查出的信息

	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	//查看雷
	//DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	
	//布置雷
	SetMine(mine, ROW, COL);
	DisplayBoard(mine, ROW, COL);
	//排雷
	FindMine(mine, show, ROW, COL);
}

int main() {
	int input = 0;
	srand((unsigned int)time(NULL));
	do {
		menu();
		printf("请输入：>");
		scanf("%d", &input);
		switch (input) {
			case 1:
				game();
				break;
			case 0:
				printf("退出游戏");
				break;
			default:
				printf("选择错误，请重新选择");
				break;
		}
	} while (input);
}