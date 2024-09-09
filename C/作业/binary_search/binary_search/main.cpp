#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int bin_search(int arr[], int left, int right, int key);
// arr 是查找的数组
//left 数组的左下标
//right 数组的右下标
//key 要查找的数字

int main() {
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int left = 0;
	int sz = sizeof(arr) / sizeof(int);
	int right = sz - 1;
	int mid = 0;
	int find = 0;
	int k = 0;
	scanf("%d", &k);

	while (left <= right) {
		mid = (arr[left] + arr[right]) / 2;
		if (k < mid) {
			right = mid - 1;
		}
		else if (k > mid) {
			left = mid + 1;
		}
		else {
			find = 1;
			printf("找到了！left=%d,right=%d",left,right);
			break;
		}
	}
	if (find == 0) {
		printf("找不到");
	}
}