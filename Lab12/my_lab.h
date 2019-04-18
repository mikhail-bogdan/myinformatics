#pragma once
#include <string>

class Rational {
public:
	Rational();
	Rational(const Rational &rational);
	Rational(const Rational *rational);
	Rational(int numerator, int denumerator);
	~Rational();

	Rational operator+(Rational a);
	Rational operator-(Rational a);
	Rational operator*(Rational a);
	Rational operator/(Rational a);
	void operator+=(Rational a);
	void operator-=(Rational a);
	void operator*=(Rational a);
	void operator/=(Rational a);

	const int GetNumerator();
	const int GetDenumerator();
	void SetNumerator(int numerator);
	void SetDenumerator(int denumerator);
	void SetValues(int numerator, int denumerator);

	const std::string toString();

private:
	static const int nod(int a, int b);
	static const int nok(int a, int b);

	int numerator;
	int denumerator;
};