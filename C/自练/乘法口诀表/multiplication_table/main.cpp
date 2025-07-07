#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() {
	//打印乘法口诀表
	int count = 0;
	scanf("%d", &count);

	int i = 0;
	int j = 0;
	for (i = 1; i <= count; i++) {
		for (j = 1; j <= i; j++) {
			printf("%d×%d=%d ", j, i, j * i);
		}
		printf("\n");
	}
}