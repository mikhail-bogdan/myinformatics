#pragma once

#include <list>
#include <random>
#include <iostream>


class IMatrix{
public:
	virtual int GetSizeX() const = 0;
	virtual int GetSizeY() const = 0;
	virtual void Set(double value, int x, int y) = 0;
	virtual double Get(int x, int y) const = 0;
	//virtual void Copy(IMatrix &matrix);
	virtual void Add(const IMatrix & matrix);
	virtual void SetRandom();
};

class UsualMatrix : public IMatrix {
public:
	UsualMatrix(int sizex, int sizey);
	~UsualMatrix();

	int GetSizeX() const;
	int GetSizeY() const;

	void Set(double value, int x, int y);
	double Get(int x, int y) const;

	void Mul(const IMatrix & matrix);
private:
	double ** data;
	int sizex, sizey;
};



class SparseMatrix : public IMatrix {
public:
	class Node {
	public:
		int index;
		double value;
	};
	
	SparseMatrix(int sizex, int sizey);
	~SparseMatrix();

	int GetSizeX() const;
	int GetSizeY() const;

	void Set(double value, int x, int y);
	double Get(int x, int y) const;

	void Mul(const IMatrix & matrix);

private:
	std::list<Node> *nodes;
	int sizex, sizey;
};

