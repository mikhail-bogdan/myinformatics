#include <stdio.h>
#include "my_lab.h"
#include <vector>
#include <chrono>

void write_to_matrix(IMatrix & matrix1, IMatrix & matrix2)
{
	FILE * f;
	fopen_s(&f, "lab.txt", "r");
	int sizex, sizey;
	double tmp = 0;
	fscanf_s(f, "%d%d", &sizex, &sizey);
	for (int i = 0; i < sizex; i++)
	{
		for (int j = 0; j < sizey; j++)
		{
			fscanf_s(f, "%lf", &tmp);
			matrix1.Set(tmp, i, j);
		}
	}
	fscanf_s(f, "%d%d", &sizex, &sizey);
	for (int i = 0; i < sizex; i++)
	{
		for (int j = 0; j < sizey; j++)
		{
			fscanf_s(f, "%lf", &tmp);
			matrix2.Set(tmp, i, j);
		}
	}
	fclose(f);
}

void copy_matrix(IMatrix & matrix1, IMatrix & matrix2)
{
	for (int i = 0; i < matrix1.GetSizeX(); i++)
		for (int j = 0; j < matrix1.GetSizeY(); j++)
			matrix1.Set(matrix2.Get(i, j), i, j);
}

bool matrix_test(IMatrix & matrix1, IMatrix & matrix2)
{
	for (int i = 0; i < matrix1.GetSizeX(); i++)
		for (int j = 0; j < matrix1.GetSizeY(); j++)
			if (matrix1.Get(i, j) != matrix2.Get(i, j)) return false;
	return true;
}

int main() {
	std::chrono::high_resolution_clock::now();
	UsualMatrix test_matrix(3, 3);
	UsualMatrix umatrix1(3, 3);
	UsualMatrix umatrix2(3, 3);
	SparseMatrix smatrix1(3, 3);
	SparseMatrix smatrix2(3, 3);

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	
	write_to_matrix(umatrix1, smatrix1);
	start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < 1000; i++)
		umatrix1.Add(smatrix1);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "sum diff(Usual first):  "
		<< (end - start).count() << "ns  " << (end - start).count() / 1000000 << "ms" << std::endl;
	
	copy_matrix(test_matrix, umatrix1);

	write_to_matrix(smatrix1, umatrix1);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
		smatrix1.Add(umatrix1);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "sum diff(Sparse first):  "
		<< (end - start).count() << "ns  " << (end - start).count() / 1000000 << "ms   Test: " << (matrix_test(smatrix1, test_matrix) ? "Success" : "Fail") << std::endl;


	write_to_matrix(umatrix1, umatrix2);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
		umatrix1.Add(umatrix2);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "sum (Usual):  "
		<< (end - start).count() << "ns  " << (end - start).count() / 1000000 << "ms   Test: " << (matrix_test(umatrix1, test_matrix) ? "Success" : "Fail") << std::endl;


	write_to_matrix(smatrix1, smatrix2);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
		smatrix1.Add(smatrix2);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "sum (Sparse):  "
		<< (end - start).count() << "ns  " << (end - start).count() / 1000000 << "ms   Test: " << (matrix_test(smatrix1, test_matrix) ? "Success" : "Fail") << std::endl;





	write_to_matrix(umatrix1, smatrix1);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1; i++)
		umatrix1.Mul(smatrix1);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "mul diff(Usual first):  "
		<< (end - start).count() << "ns  " << (end - start).count() / 1000000 << "ms" << std::endl;

	copy_matrix(test_matrix, umatrix1);

	write_to_matrix(smatrix1, umatrix1);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1; i++)
		smatrix1.Mul(umatrix1);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "mul diff(Sparse first):  "
		<< (end - start).count() << "ns  " << (end - start).count() / 1000000 << "ms   Test: " << (matrix_test(smatrix1, test_matrix) ? "Success" : "Fail") << std::endl;


	write_to_matrix(umatrix1, umatrix2);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1; i++)
		umatrix1.Mul(umatrix2);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "mul (Usual):  "
		<< (end - start).count() << "ns  " << (end - start).count() / 1000000 << "ms   Test: " << (matrix_test(umatrix1, test_matrix) ? "Success" : "Fail") << std::endl;


	write_to_matrix(smatrix1, smatrix2);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1; i++)
		smatrix1.Mul(smatrix2);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "mul (Sparse):  "
		<< (end - start).count() << "ns  " << (end - start).count() / 1000000 << "ms   Test: " << (matrix_test(smatrix1, test_matrix) ? "Success" : "Fail") << std::endl;


	//getchar();
	getchar();
	return 0;
}