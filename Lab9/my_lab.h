#pragma once

class Matrix
{
public:
	Matrix(int sizeX, int sizeY);

	~Matrix();

	int sizeX();
	
	int sizeY();

	double determinant();

	Matrix minor(int x, int y);

	double * operator[](int n);

private:
	double ** matrix = nullptr;
	int sX = 0, sY = 0;
};