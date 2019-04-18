#pragma once
#include <vector>

struct Point
{
	char x = 0, y = 0;
	Point(char x, char y) : x(x), y(y) {}
};

class Matrix
{
public:
	Matrix(int sizeX, int sizeY)
	{
		this->sX = sizeX;
		this->sY = sizeY;
		matrix = new double*[sizeX];
		for (int i = 0; i < sizeX; i++)
		{
			matrix[i] = new double[sizeY];
		}
	}

	~Matrix()
	{
		for (int i = 0; i < this->sX; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	int sizeX()
	{
		return this->sX;
	}

	int sizeY()
	{
		return this->sY;
	}

	double * operator[](int x)
	{
		return matrix[x];
	}

private:
	double ** matrix = nullptr;
	int sX = 0, sY = 0;
};

void saddle_elements(Matrix &matrix, std::vector<Point*> * points);