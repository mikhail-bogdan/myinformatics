#include <stdio.h>
#include <stdlib.h>

int abs_max(int * mass, int size) {
	int n = ((unsigned int)(-1)) / 2 - 1;
	for (int i = 0; i < size; i++) {
		if (abs(mass[i]) < abs(n)) {
			n = mass[i];
		}
	}
	return n;
}

int main() {

	//int ivalue = (unsigned int)(~0) >> 1;
	//printf("%d\n", ivalue);



	int size;
	printf("Enter the N and N numbers: ");
	scanf_s("%d", &size);
	int * mass = malloc(4 * size);
	for (int i = 0; i < size; i++) {
		scanf_s("%d", &mass[i]);
	}
	printf("Result: %d", abs_max(mass, size));
	getchar();
	getchar();
	return 0;
}