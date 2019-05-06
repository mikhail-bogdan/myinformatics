//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char getkey() { return 'g'; }

int main() {
	char e[10] = { 'n' };
	char n[5];
	
	scanf_s("%s", n, 5);
	if (n[2] == getkey()) {
		e[0] = 'y';
	}
	if (e[0] == 'y') {
		printf("True");
	}
	else {
		printf("False");
	}
	getchar();
	getchar();
	return 0;
}