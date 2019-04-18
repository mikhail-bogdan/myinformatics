#include <iostream>
#include "lab.h"
#include <cstdlib>
#include <string.h>

const int size = 500;

int main() {
	setlocale(LC_ALL, "Russian");
	FILE *fin;
	char file1[15] = { 0 };
	std::cout << "�������� ���������, ����������� ���������� ���� � ������������ ������ ������� ��������, �������� ������ ���������� �� �����. ������������� ������ ����(����������) � ������� ��� ����� � ���������� �������." << std::endl << "������� ��� ��������� �����: ";
	std::cin >> file1;
	fopen_s(&fin, file1, "rt");
	if (fin == NULL) {
		return -1000;
	}
	else {
		char * ar = new char[4096];
		int i = count_words(size, fin);
		std::cout << std::endl << "���������� ���� � ����� = " << i << std::endl;
		char ** pointers = new char*[i + 1];
		fseek(fin, 0, SEEK_SET);
		sort(i, size, fin, pointers, ar);
		delete[] pointers;
		delete[] ar;// ! �������� �� �������� ����� !
		
	}
	fclose(fin);
	std::cout << std::endl;
	system("pause");
	return 0;
}

