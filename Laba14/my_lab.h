#pragma once

#include <list>
#include <random>
#include <iostream>


class IMatrix{
public:
	virtual int GetSizeX() const;
	virtual int GetSizeY() const;
	virtual void Set(double value, int x, int y) = 0;
	virtual double Get(int x, int y) const = 0;
	//virtual void Copy(IMatrix &matrix);
	virtual void Add(IMatrix & matrix);
	virtual void SetRandom();
protected:
	int sizex, sizey;
};

class UsualMatrix : public IMatrix {
public:
	UsualMatrix(int sizex, int sizey);
	~UsualMatrix();

	void Set(double value, int x, int y);
	double Get(int x, int y) const;

	void Mul(const IMatrix & matrix);
private:
	double ** data;
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

	void Set(double value, int x, int y);
	double Get(int x, int y) const;

	void Mul(const IMatrix & matrix);

private:
	std::list<Node> *nodes;
};

