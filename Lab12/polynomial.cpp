#include "polynomial.h"

inline int max(int a, int b)
{
	return a > b ? a : b;
}

Polynomial::Polynomial(int n, const Rational * data)
{
	if (data == nullptr) return;
	this->values = n;
	this->data = new Rational[n];
	for (int i = 0; i < n; i++)
	{
		this->data[i] = data[i];
	}
}

Polynomial::Polynomial(const Polynomial & p)
{
	if (p.data == nullptr) return;
	this->values = p.values;
	delete[] this->data;
	this->data = new Rational[p.values];
	for (int i = 0; i < p.values; i++)
	{
		this->data[i] = p.data[i];
	}
}

Polynomial::Polynomial(const Polynomial * p)
{
	if (p->data == nullptr) return;
	this->values = p->values;
	delete[] this->data;
	this->data = new Rational[p->values];
	for (int i = 0; i < p->values; i++)
	{
		this->data[i] = p->data[i];
	}
}

Polynomial::~Polynomial()
{
	if(this->data)
		delete[] this->data;
}

const Polynomial & Polynomial::operator=(const Polynomial & a)
{
	this->values = a.values;
	delete[] this->data;
	if (a.data == nullptr) return nullptr;
	this->values = a.values;
	this->data = new Rational[a.values];
	for (int i = 0; i < a.values; i++)
	{
		this->data[i] = a.data[i];
	}
	return *this;
}

const Polynomial & Polynomial::operator+(Polynomial const & a)
{
	int n = max(this->values, a.values);
	Rational * mass = new Rational[n];
	for (int i = 0; i < n; i++)
		mass[i] = this->data[i] + a.data[i];
	Polynomial * p = new Polynomial(n, mass);
	return p;
}

std::string Polynomial::toString() const
{
	//std::string 
	return nullptr;
}


