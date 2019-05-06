#pragma once
#include <string>
#include <iostream>

class Rational {
public:
	Rational();
	Rational(const Rational &rational);
	Rational(const Rational *rational);
	Rational(int numerator, int denumerator = 1);
	Rational(float value);
	~Rational();

	const Rational & operator=(const Rational & a);
	const Rational & operator+(const Rational & a);
	const Rational & operator-(const Rational & a);
	const Rational & operator*(const Rational & a);
	const Rational & operator/(const Rational & a);
	const Rational & operator+=(const Rational & a);
	const Rational & operator-=(const Rational & a);
	const Rational & operator*=(const Rational & a);
	const Rational & operator/=(const Rational & a);


	int GetNumerator() const;
	int GetDenumerator() const;
	void SetNumerator(int numerator);
	void SetDenumerator(int denumerator);
	void SetValues(int numerator, int denumerator);

	std::string toString() const;
	float toFloat() const;

private:
	static int nod(int a, int b);
	static int nok(int a, int b);

	int numerator;
	int denumerator;
};