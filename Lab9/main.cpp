#include <iostream>
#include <vector>
#include "my_lab.h"

using namespace std;

int main()
{
	int N;
	cout << "Enter N" << endl;
	cin >> N;
	Matrix matrix(N, N);
	
	cout << "Enter matrix " << N << "x" << N << endl;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];

	double det = matrix.determinant();
	cout << "Result " << det << endl;

	getchar();
	getchar();
	return 0;
}