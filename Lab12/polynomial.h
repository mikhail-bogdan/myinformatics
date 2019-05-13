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

	Polynomial operator=(const Polynomial & a);
	Polynomial operator+(const Polynomial & a);
	Polynomial operator*(const Polynomial & a);
	Polynomial operator*(const Rational & value);
	Polynomial operator*(int value);

	Polynomial operator+=(const Polynomial & a);
	Polynomial operator*=(const Polynomial & a);
	Polynomial operator*=(const Rational & value);
	Polynomial operator*=(int value);


	std::string toString() const;

private:
	int count = 0;
	Rational * data = nullptr;
};