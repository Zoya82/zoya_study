#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int bin_search(int arr[], int left, int right, int key);
// arr �ǲ��ҵ�����
//left ��������±�
//right ��������±�
//key Ҫ���ҵ�����

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
			printf("�ҵ��ˣ�left=%d,right=%d",left,right);
			break;
		}
	}
	if (find == 0) {
		printf("�Ҳ���");
	}
}