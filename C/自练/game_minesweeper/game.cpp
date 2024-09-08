#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set) {
	int i = 0;
	for (i = 0; i < rows; i++) {
		int j = 0;
		for (j = 0; j < cols; j++) {
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int row, int col) {
	int i = 0;
	printf("\n——扫雷游戏——\n");
	for (i = 0; i <= row; i++) {
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++) {
		int j = 0;
		printf("%d ", i);
		for (j = 1; j <= col; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

void SetMine(char board[ROWS][COLS], int row, int col) {
	int count = EASY_COUNT;
	while (count) {
		int x = rand() % row + 1;
		int y = rand() % col + 1;

		if (board[x][y] == '0') {
			board[x][y] = '1';
			count--;
		}
	}
}

int GetMineCount(char mine[ROWS][COLS], int x, int y) {
	return mine[x - 1][y - 1] + mine[x - 1][y] + mine[x - 1][y + 1] +
		mine[x][y - 1] + mine[x][y + 1] +
		mine[x + 1][y - 1] + mine[x + 1][y] + mine[x + 1][y + 1] - 8 * '0';
}

void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS], int row, int col) {
	int x = 0, y = 0;
	int win = 0;
	while (win<row*col-EASY_COUNT) {
		printf("请输入要猜的数字：>");
		scanf("%d,%d", &x, &y);
		printf("\n");
		if (x >= 1 && x <= row && y >= 1 && y <= col) {
			if (mine[x][y] == '1') {
				printf("踩雷了！游戏结束\n");
				DisplayBoard(mine, ROW, COL);
				break;
			}
			else if(mine[x][y]=='0') {
				int count = GetMineCount(mine, x, y);
				show[x][y] = count + '0';  //表示该数字的字符形式
				DisplayBoard(show, ROW, COL);
				win++;
			}
			else {
				printf("该坐标已踩过，请重新输入\n");
			}
		}
		else {
			printf("输入坐标超过范围，请重新输入");
		}
		//忘记设置成功结束了
		if (win == row * col - EASY_COUNT) {
			printf("成功排雷！恭喜你");
			DisplayBoard(mine, ROW, COL);
		}
	}
}