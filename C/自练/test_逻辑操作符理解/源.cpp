#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
int main()
{
	int i = 0, a = 0, b = 2, c = 3, d = 4;
	//i = a++ && ++b && d++;  //此时i是0
	i = a++||++b||d++;  //此时i是1
	printf("a = %d\nb = %d\nc = %d\nd = %d\ni = %d\n", a, b, c, d, i);
	return 0;
}
