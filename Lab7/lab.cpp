#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "lab.h"
#include <cstdlib>
#include <string.h>

int count_words(const int size, FILE *fin) {
	char *buf = new char[size];
	int count = 0;
	while (fgets(buf, size, fin)) {
		char *a = strtok(buf, " —,.:;-!\n\0?");
		while (a != NULL) {
			a = strtok(NULL, " —,.:;-!\n\0?");
			count++;
		}
	}
	return count;
	delete[] buf;
}

void sort(const int i, const int size, FILE * fin, char ** arr, char * ar) {
	int ip = 0, count = 0;
	while (!feof(fin)) {
		ar[ip++] = fgetc(fin);
	}
	ar[ip++] = 0;
	char * a = strtok(ar, " —,.:;-!\n\0?");
	while (a != NULL) {
		*(arr + count) = a;
		std::cout << "a - <<" << a << ">>; ";
		std::cout << " arr = " << (void*)*(arr + count) << std::endl;
		count++;
		a = strtok(NULL, " —,.:;-!\n\0?");
	}
	for (int j = 0; j < i - 1; j++)
		std::cout << (void *)(arr[j]) << std::endl;
	return;
}

