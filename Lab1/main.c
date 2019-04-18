#include <stdio.h>

int main() {
	int max = 0, max_i = 0, i = 0, n = 0;
	printf("Enter N numbers and zero in end:\n");
	do {
		printf("Enter %d element: ", i);
		scanf_s("%d", &n);
		if (n > max) {
			max = n;
			max_i = i;
		}
		i++;
	} while (n != 0);
	printf("Result: %d(%d)", max, max_i);
	getchar();
	getchar();
	return 0;
}