#include "my_lab.h"

void IMatrix::Add(IMatrix & matrix)
{
	if (matrix.GetSizeX() != this->sizex || matrix.GetSizeY() != this->sizey) return;
	for (int i = 0; i < this->sizex; i++)
		for (int j = 0; j < this->sizey; j++)
			this->Set(this->Get(i, j) + matrix.Get(i, j), i, j);
}

void IMatrix::SetRandom()
{
	int n = 0;
	for (int i = 0; i < sizex; i++)
	{
		for (int j = 0; j < this->sizey; j++)
		{
			int r = rand() % 10;
			while (r == 0) r = rand() % 10;
			this->Set(r, i, j);
		}
		if (i % 10 == 0) {
			n++;
			std::cout << "             " << (char)13 << "Process: " << n << "%" << (char)13;
		}
	}
	for (int i = 0; i < this->sizex; i++)
		this->Set(0.0, i, rand() % this->sizey);
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

double UsualMatrix::Get(int x, int y) const
{
	if (x < 0 || x >= this->sizex || y < 0 || y >= this->sizey) return -1;
	return data[x][y];
}

void UsualMatrix::Mul(const IMatrix & matrix)
{
	if (this->sizey != matrix.GetSizeX()) return;
	
	double ** data = new double*[sizey];
	for (int i = 0; i < this->sizey; i++)
		data[i] = new double[matrix.GetSizeX()];

	for (int i = 0; i < this->sizey; i++)
	{
		for (int j = 0; j < matrix.GetSizeY(); j++) {
			double sum = 0;
			for (int a = 0; a < this->sizey; a++)
				sum += this->Get(i, a) * matrix.Get(a, j);
			data[i][j] = sum;
		}
	}
	
	for (int i = 0; i < this->sizex; i++)
		delete[] this->data[i];
	delete[] this->data;

	this->data = data;
}

SparseMatrix::SparseMatrix(int sizex, int sizey)
{
	this->sizex = sizex;
	this->sizey = sizey;
	this->nodes = new std::list<Node>[sizex];
	this->nodes[2].insert(this->nodes[2].begin(), *(new Node));
}

SparseMatrix::~SparseMatrix()
{
	delete[] this->nodes;
}

void SparseMatrix::Set(double value, int x, int y)
{
	if (x < 0 || x >= this->sizex || y < 0 || y >= this->sizey) return;
	std::list<Node> * list = &(this->nodes[x]);
	for (auto iter = (*list).begin(); iter != (*list).end(); iter++) {
		if ((*iter).index == y)
		{
			(*iter).value = value;
			return;
		}
	}
	Node node;
	node.index = y;
	node.value = value;
	list->push_back(node);
}

double SparseMatrix::Get(int x, int y) const
{
	if (x < 0 || x >= this->sizex || y < 0 || y >= this->sizey) return 0.0;
	std::list<Node> * list = &(this->nodes[x]);
	for (auto iter = (*list).begin(); iter != (*list).end(); iter++) {
		if ((*iter).index == y)
		{
			return (*iter).value;
		}
	}
	return 0.0;
}

void SparseMatrix::Mul(const IMatrix & matrix)
{
	if (this->sizey != matrix.GetSizeX()) return;

	double ** data = new double*[sizey];
	for (int i = 0; i < this->sizey; i++)
		data[i] = new double[matrix.GetSizeX()];

	for (int i = 0; i < this->sizey; i++)
	{
		for (int j = 0; j < matrix.GetSizeY(); j++) {
			double sum = 0;
			for (int a = 0; a < this->sizey; a++)
				sum += this->Get(i, a) * matrix.Get(a, j);
			data[i][j] = sum;
		}
	}

/*	for (int i = 0; i < this->sizex; i++)
		delete[] this->data[i];
	delete[] data;

	this->data = data;*/
}
