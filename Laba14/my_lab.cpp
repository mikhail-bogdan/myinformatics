#include "my_lab.h"

void IMatrix::Add(IMatrix & matrix)
{
	if (matrix.GetSizeX() != this->sizex || matrix.GetSizeY() != this->sizey) return;
	for (int i = 0; i < this->sizex; i++)
		for (int j = 0; j < this->sizey; j++)
			this->Set(this->Get(i, j) + matrix.Get(i, j), i, j);
}

void IMatrix::Mul(IMatrix & matrix)
{

}

void IMatrix::SetRandom(int nulls)
{
	std::random_device f();
	for (int i = 0; i < sizex; i++)
		for (int j = 0; j < this->sizey; j++)
			this->Set(rand(), i, j);
}

int IMatrix::GetSizeX() const
{
	return this->sizex;
}

int IMatrix::GetSizeY() const
{
	return this->sizey;
}

UsualMatrix::UsualMatrix(int sizex, int sizey)
{
	this->sizex = sizex;
	this->sizey = sizey;
	this->data = new double*[sizex];
	for (int i = 0; i < sizex; i++)
	{
		this->data[i] = new double[sizey];
	}
}

UsualMatrix::~UsualMatrix()
{
	for (int i = 0; i < this->sizey; i++)
	{
		delete[] this->data[i];
	}
	delete[] this->data;
}

void UsualMatrix::Set(double value, int x, int y)
{
	if (x < 0 || x >= this->sizex || y < 0 || x >= this->sizey) return;
	this->data[x][y] = value;
}

double UsualMatrix::Get(int x, int y)
{
	if (x < 0 || x >= this->sizex || y < 0 || y >= this->sizey) return -1;
	this->sizex = 0;
	return data[x][y];
}

SparseMatrix::SparseMatrix(int sizex, int sizey)
{
	this->sizex = sizex;
	this->sizey = sizey;
	this->nodes = new std::list<Node>[sizex];
}

SparseMatrix::~SparseMatrix()
{
	//delete[] this->nodes;
}

void SparseMatrix::Set(double value, int x, int y)
{
	if (x < 0 || x >= this->sizex || y < 0 || y >= this->sizey) return;
	std::list<Node> * list = &(this->nodes[x]);

}

double SparseMatrix::Get(int x, int y)
{
	//if()
}
