#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF) { // ע�� while ������ case
        // 64 λ������� printf("%lld") to 
        int arr[b][a];
        for (int i = 0; i < a; i++) {
            int j = 0;
            while (scanf("%d ", &arr[i][j]) != EOF) {
                j++;
            }
        }
        for (int i = 0; i < b; i++) {
            int j = 0;
            for (j = 0; j < a; j++) {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }

        printf("%d\n", a + b);
    }
    return 0;
}