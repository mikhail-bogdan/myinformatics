#include "my_lab.h"

Matrix::Matrix(int sizeX, int sizeY)
{
	this->sX = sizeX;
	this->sY = sizeY;
	this->matrix = new double*[sizeX];
	for (int i = 0; i < sizeX; i++)
	{
		this->matrix[i] = new double[sizeY];
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < this->sX; i++)
	{
		delete[] this->matrix[i];
	}
	delete[] this->matrix;
}

double Matrix::determinant()
{
	if (sX != sY) return 0.0;
	if (sX == 1)
	{
		return **this->matrix;
	}

	double det = 0;

	for (int i = 0; i < sY; i++)
	{
		det += this->matrix[0][i] * (i % 2 ? -1 : 1) * this->minor(0, i).determinant();
	}

	return det;
}

Matrix Matrix::minor(int x, int y)
{
	Matrix * matrix = new Matrix(this->sX - 1, this->sY - 1);
	int m = 0, n = 0;
	for (int i = 0; i < this->sX; i++)
	{
		for (int j = 0; j < this->sY; j++)
		{
			if (i != x && j != y)
			{
				(*matrix)[m][n++] = this->matrix[i][j];
				if (n == sY - 1)
				{
					n = 0;
					m++;
				}
			}
		}
	}
	return * matrix;
}


int Matrix::sizeX()
{
	return this->sX;
}

int Matrix::sizeY()
{
	return this->sY;
}

double * Matrix::operator[](int n)
{
	return this->matrix[n];
}