#include <stdio.h>
#include <stdlib.h>

char ** add2(char ** buffer, int count, char * element) {
	char ** buf = malloc(sizeof(char *) * count + sizeof(char *));
	for (int i = 0; i < count; i++) {
		buf[i] = buffer[i];
	}
	buf[count] = element;
	return buf;
}

char * add1(char * buffer, int count, char element) {
	char * buf = malloc(sizeof(char) * count + sizeof(char));
	for (int i = 0; i < count; i++) {
		buf[i] = buffer[i];
	}
	buf[count] = element;
	return buf;
}

int main() {
	char ** buffer;
	char n;
	int i = 0, letter = 0;
	char * count;
	buffer = malloc(sizeof(char *));
	buffer[0] = malloc(64);
	count = malloc(sizeof(char));
	count[0] = 0;
	printf("Enter the line: ");
	while (1) {
		scanf_s("%c", &n, 1);
		if (n == '\n' || n == ' ') {
			buffer[i][letter] = 0;
			i++;
			letter = 0;
			if (n == '\n') break;
			buffer = add2(buffer, i, malloc(64));
			count = add1(count, i, 0);
		}
		if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z')) {
			switch (n) {
			case 'A':
			case 'E':
			case 'I':
			case 'J':
			case 'O':
			case 'U':
			case 'Y':
			case 'a':
			case 'e':
			case 'i':
			case 'j':
			case 'o':
			case 'u':
			case 'y':
				count[i]++;
				break;
			default:
				break;
			}
			buffer[i][letter] = n;
			letter++;
		}
	}
	printf("Result: ");
	while (1) {
		char min = 127;
		int c = 0;
		for (int a = 0; a < i; a++) {
			if (count[a] != -1 && count[a] < min) {
				min = count[a];
			}
		}
		for (int a = 0; a < i; a++) {
			if (count[a] != -1 && count[a] == min) {
				printf("%s\n", buffer[a]);
				count[a] = -1;
				c++;
			}
		}
		if (c == 0) break;
	}
	getchar();
	//getchar();
	return 0;
}