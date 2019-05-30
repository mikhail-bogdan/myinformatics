#include <stdio.h>
#include "my_lab.h"
#include <vector>

int main() {
	UsualMatrix matrix1(3, 3);
	SparseMatrix matrix2(3, 3);
	matrix1.SetRandom();
	matrix2.SetRandom();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << matrix1.Get(i, j) << " ";
		std::cout << std::endl;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << matrix2.Get(i, j) << " ";
		std::cout << std::endl;
	}
	matrix1.Mul(matrix2);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << matrix1.Get(i, j) << " ";
		std::cout << std::endl;
	}
	getchar();
	getchar();
	return 0;
}