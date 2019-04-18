#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {
	int a, b, c;
	printf("Enter a: ");
	scanf("%d", &a);
	printf("Enter b: ");
	scanf("%d", &b);
	printf("Enter c: ");
	scanf_s("%d", &c);
	a = b + c;
	float d = 4.234f;
	switch (d) {
	case 4.23:
		break;
	case 4.234:
		break;
	default:
		break;
	}
	printf("Result: %d+%d=%d", b, c, a);
	getchar();
	getchar();
	return 0;
}