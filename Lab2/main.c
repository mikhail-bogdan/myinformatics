#include <stdio.h>
#include <stdlib.h>

int alloc_size = 0;

char * add_symbol(char * buffer, int size, char symbol) {
	char * buf;
	if (size + 2 > alloc_size) {
		buf = malloc(size + 1025);
		for (int i = 0; i < size; i++) {
			buf[i] = buffer[i];
		}
		alloc_size += 1024;
		free(buffer);
	}
	else {
		buf = buffer;
	}
	buf[size] = symbol;
	return buf;
}

char * symetric_words(char * buf, int size) {
	alloc_size = 0;
	char n, word = 1, i = 0, len = 0, flag = 1;
	char * result = 0, result_size = 0;
	char buffer[32];
	int offset = 0;
	int index = 0;
	while (1) {
		n = buf[index];
		index++;
		if (n == '\n') {
			flag = 1;
			for (char a = 0; a < i / 2; a++) {
				if (buffer[a] != buffer[i - 1 - a]) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				buffer[i] = 0;
				for (int a = 0; a < i; a++) {
					result = add_symbol(result, result_size, buffer[a]);
					result_size++;
				}
				result[result_size] = 0;
				result_size++;
			}
			break;
		}
		if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122) && word) {
			buffer[i] = n;
			i++;
			if (i >= 32) {
				word = 0;
			}
		}
		else if (n == ' ') {
			word = 1;
			flag = 1;
			for (char a = 0; a < i / 2; a++) {
				if (buffer[a] != buffer[i - 1 - a]) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				buffer[i] = 0;
				for (int a = 0; a < i; a++) {
					result = add_symbol(result, result_size, buffer[a]);
					result_size++;
				}
				result[result_size] = '\n';
				result_size++;
				offset += i + 1;
			}
			i = 0;
		}
	}
	return result;
}

int main() {
	char n;
	printf("Enter the line: ");
	char * buffer = 0;
	int size = 0;
	while (1) {
		scanf_s("%c", &n, 1);
		buffer = add_symbol(buffer, size, n);
		size++;
		if (n == '\n')
			break;
	}

	buffer = symetric_words(buffer, size);

	if (buffer != 0) {
		for (size = 0; buffer[size] != 0; size++) {
			printf("%c", buffer[size]);
		}
	}
	getchar();
	//getchar();
	return 0;
}