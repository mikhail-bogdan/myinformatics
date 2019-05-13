#include "polynomial.h"

inline int max(int a, int b)
{
	return a > b ? a : b;
}

inline int min(int a, int b)
{
	return a < b ? a : b;
}

Polynomial::Polynomial(int n, const Rational * data)
{
	if (data == nullptr) return;
	this->count = n;
	this->data = new Rational[n];
	for (int i = 0; i < n; i++)
	{
		this->data[i] = data[i];
	}
}

Polynomial::Polynomial(const Polynomial & p)
{
	if (p.data == nullptr) return;
	this->count = p.count;
	delete[] this->data;
	this->data = new Rational[p.count];
	for (int i = 0; i < p.count; i++)
	{
		this->data[i] = p.data[i];
	}
}

Polynomial::Polynomial(const Polynomial * p)
{
	if (p->data == nullptr) return;
	this->count = p->count;
	delete[] this->data;
	this->data = new Rational[p->count];
	for (int i = 0; i < p->count; i++)
	{
		this->data[i] = p->data[i];
	}
}

Polynomial::~Polynomial()
{
	if(this->data)
		delete[] this->data;
}

Polynomial Polynomial::operator=(const Polynomial & a)
{
	this->count = a.count;
	delete[] this->data;
	if (a.data == nullptr) return nullptr;
	this->count = a.count;
	this->data = new Rational[a.count];
	for (int i = 0; i < a.count; i++)
	{
		this->data[i] = a.data[i];
	}
	return *this;
}

Polynomial Polynomial::operator+(Polynomial const & a)
{
	int n = max(this->count, a.count);
	int m = min(this->count, a.count);
	Rational * mass = new Rational[n];
	if (this->count > a.count)
	{
		for (int i = 0; i < m; i++)
			mass[i] = this->data[i] + a.data[i];
		for (int i = m; i < n; i++)
			mass[i] = this->data[i];
	}
	else
	{
		for (int i = 0; i < m; i++)
			mass[i] = this->data[i] + a.data[i];
		for (int i = m; i < n; i++)
			mass[i] = a.data[i];
	}
	return Polynomial(n, mass);
}

Polynomial Polynomial::operator*(const Rational & value)
{
	Rational * mass = new Rational[this->count];
	for (int i = 0; i < this->count; i++)
		mass[i] = this->data[i] * value;
	return Polynomial(this->count, mass);
}

Polynomial Polynomial::operator*(int value)
{
	Rational * mass = new Rational[this->count];
	for (int i = 0; i < this->count; i++)
		mass[i] = this->data[i] * value;
	return Polynomial(this->count, mass);
}

Polynomial Polynomial::operator*=(const Rational & value)
{
	for (int i = 0; i < this->count; i++)
		this->data[i] *= value;
	return *this;
}

Polynomial Polynomial::operator*=(int value)
{
	for (int i = 0; i < this->count; i++)
		this->data[i] *= value;
	return *this;
}

Polynomial Polynomial::operator+=(const Polynomial & a)
{
	int n = max(this->count, a.count);
	int m = min(this->count, a.count);
	Rational * mass = new Rational[n];
	if (this->count > a.count)
	{
		for (int i = 0; i < m; i++)
			mass[i] = this->data[i] + a.data[i];
		for (int i = m; i < n; i++)
			mass[i] = this->data[i];
	}
	else
	{
		for (int i = 0; i < m; i++)
			mass[i] = this->data[i] + a.data[i];
		for (int i = m; i < n; i++)
			mass[i] = a.data[i];
	}
	this->count = n;
	delete[] this->data;
	this->data = mass;
	return *this;
}

std::string Polynomial::toString() const
{
	std::string line = "";
	for (int i = this->count - 1; i >= 0; i--) {
		if (this->data[i].GetNumerator() != 0)
			line += "(" + this->data[i].toString() + ")x" + (i + "");
		if (i != 0)
			line += "+";
	}
	return line;
}


