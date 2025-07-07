#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF) { // 注意 while 处理多个 case
        // 64 位输出请用 printf("%lld") to 

        int num1[a];
        int i = 0;
        while (scanf("%d ", &num1[i]) != EOF) {
            i++;
        }
        int num2[b];
        i = 0;
        while (scanf("%d ", &num2[i]) != EOF) {
            i++;
        }
        int num3[a + b];
        i = 0;
        int j = 0, k = 0;
        while (i < a && j < b) {
            if (num1[i] < num2[j]) {
                num3[k] = num1[i];
                i++;
                k++;
            }
            else if (num1[i] > num2[j]) {
                num3[k] = num2[j];
                j++;
                k++;
            }
            else if (num1[i] == num2[j]) {
                num3[k] = num1[i];
                i++;
                k++;
                num3[k] = num2[j];
                k++;
                k++;
            }
        }
        while (i < a) {
            num3[k++] = num1[i++];
        }
        while (j < b) {
            num3[k++] = num2[j++];
        }
        for (k = 0; k < a + b; k++) {
            printf("%d ", num3[k]);
        }
    }
    return 0;
}