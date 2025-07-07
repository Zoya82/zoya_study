#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void init(int arr[]);

void assign(int arr[], int sz);

void print(int arr[],int sz);

void reserve(int arr[],int sz);

int main() {
	int arr[10];
	int sz = sizeof(arr) / sizeof(int);
	init(arr);
	//赋值方便观察后面几个函数是否作用
	assign(arr, sz);
	print(arr, sz);
	reserve(arr,sz);
}

void init(int arr[]) {
	arr = { 0 };
}

void assign(int arr[], int sz) {
	int i = 0;
	for (i = 0; i < sz; i++) {
		scanf("%d", &arr[i]);
	}
}

void print(int arr[], int sz) {
	int i = 0;
	for (i = 0; i < sz; i++) {
		printf("%d\n", arr[i]);
	}
}

void reserve(int arr[],int sz) {
	int right = sz - 1;
	int left = 0;
	int temp = 0;

	while (left <= right) {
		temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		left++;
		right--;
	}
	print(arr, sz);
}