#pragma once

#include "my_lab.h"
#include <math.h>

class Polynomial
{
public:
	Polynomial(int n, const Rational * values);
	Polynomial(const Polynomial & p);
	Polynomial(const Polynomial * p);
	~Polynomial();

	const Polynomial & operator=(const Polynomial & a);
	const Polynomial & operator+(const Polynomial & a);
	const Polynomial & operator*(const Polynomial & a);
	const Polynomial & operator*(const Rational & value);
	const Polynomial & operator*(int value);

	const Polynomial & operator+=(const Polynomial & a);
	const Polynomial & operator*=(const Polynomial & a);

	std::string toString() const;

private:
	int values = 0;
	Rational * data = nullptr;
};