#include "my_lab.h"

Rational::Rational() {
	Rational(1, 1);
}

Rational::Rational(const Rational & rational) {
	this->numerator = rational.numerator;
	this->denumerator = rational.denumerator;
}

Rational::Rational(const Rational * rational) {
	this->numerator = rational->numerator;
	this->denumerator = rational->denumerator;
}

Rational::Rational(int numerator, int denumerator) {
	if (!numerator)
		this->numerator = 1;
	else
		this->numerator = numerator;
	if (!denumerator)
		this->denumerator = 1;
	else
		this->denumerator = denumerator;
}

Rational::~Rational() {}

Rational Rational::operator+(Rational a)
{
	int general_denumerator = nok(this->denumerator, a.denumerator);
	int general_numerator = this->numerator * (general_denumerator / this->denumerator)
		+ a.numerator * (general_denumerator / a.denumerator);
	int n = nod(general_numerator, general_denumerator);
	return Rational(general_numerator / n, general_denumerator / n);
}

Rational Rational::operator-(Rational a)
{
	int general_denumerator = nok(this->denumerator, a.denumerator);
	int general_numerator = this->numerator * (general_denumerator / this->denumerator)
		- a.numerator * (general_denumerator / a.denumerator);
	int n = nod(general_numerator, general_denumerator);
	return Rational(general_numerator / n, general_denumerator / n);
}

Rational Rational::operator*(Rational a)
{
	int general_denumerator = this->denumerator * a.denumerator;
	int general_numerator = this->numerator * a.numerator;
	int n = nod(general_numerator, general_denumerator);
	return Rational(general_numerator / n, general_denumerator / n);
}

Rational Rational::operator/(Rational a)
{
	int general_denumerator = this->denumerator * a.numerator;
	int general_numerator = this->numerator * a.denumerator;
	int n = nod(general_numerator, general_denumerator);
	return Rational(general_numerator / n, general_denumerator / n);
}

void Rational::operator+=(Rational a)
{
	int general_denumerator = nok(this->denumerator, a.denumerator);
	int general_numerator = this->numerator * (general_denumerator / this->denumerator)
		+ a.numerator * (general_denumerator / a.denumerator);
	int n = nod(general_numerator, general_denumerator);
	this->numerator = general_numerator / n;
	this->denumerator = general_denumerator / n;
}

void Rational::operator-=(Rational a)
{
	int general_denumerator = nok(this->denumerator, a.denumerator);
	int general_numerator = this->numerator * (general_denumerator / this->denumerator)
		- a.numerator * (general_denumerator / a.denumerator);
	int n = nod(general_numerator, general_denumerator);
	this->numerator = general_numerator / n;
	this->denumerator = general_denumerator / n;
}

void Rational::operator*=(Rational a)
{
	int general_denumerator = this->denumerator * a.denumerator;
	int general_numerator = this->numerator * a.numerator;
	int n = nod(general_numerator, general_denumerator);
	this->numerator = general_numerator / n;
	this->denumerator = general_denumerator / n;
}

void Rational::operator/=(Rational a)
{
	int general_denumerator = this->denumerator * a.numerator;
	int general_numerator = this->numerator * a.denumerator;
	int n = nod(general_numerator, general_denumerator);
	this->numerator = general_numerator / n;
	this->denumerator = general_denumerator / n;
}

const int Rational::GetNumerator() {
	return this->numerator;
}

const int Rational::GetDenumerator() {
	return this->denumerator;
}

void Rational::SetNumerator(int numerator) {
	if (!numerator) numerator = 1;
	int n = nod(numerator, this->denumerator);
	this->numerator = numerator / n;
	this->denumerator /= n;
}

void Rational::SetDenumerator(int denumerator) {
	if (!denumerator) denumerator = 1;
	int n = nod(this->numerator, denumerator);
	this->numerator /= n;
	this->denumerator = denumerator / n;
}

void Rational::SetValues(int numerator, int denumerator) {
	if (!numerator) numerator = 1;
	if (!denumerator) denumerator = 1;
	int n = nod(numerator, denumerator);
	this->numerator = numerator / n;
	this->denumerator = denumerator / n;
}

const std::string Rational::toString()
{
	return std::string(std::to_string(this->numerator) + "/" + std::to_string(this->denumerator));
}

const int Rational::nod(int a, int b)
{
	while (a != b) {
		if (a > b) {
			a -= b;
		}
		else {
			b -= a;
		}
	}
	return a;
}

const int Rational::nok(int a, int b)
{
	return (a * b) / nod(a, b);
}