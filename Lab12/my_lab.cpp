#include "my_lab.h"

Rational::Rational() {
	this->numerator = 0;
	this->denumerator = 1;
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
	this->numerator = numerator;
	if (!denumerator)
	{
		std::cout << "Denumerator equals zero" << std::endl;
		getchar();
		getchar();
		exit(1);
	}
	else
		this->denumerator = denumerator;
}

Rational::Rational(float value)
{
	this->numerator = (int)(value * 100000);
	this->denumerator = 100000;
	int n = nod(this->numerator, this->denumerator);
	this->numerator /= n;
	this->denumerator /= n;
}

Rational::~Rational() {}

Rational Rational::operator=(const Rational & a)
{
	this->numerator = a.numerator;
	this->denumerator = a.denumerator;
	return *this;
}

Rational Rational::operator+(const Rational & a)
{
	int general_denumerator = nok(this->denumerator, a.denumerator);
	int general_numerator = this->numerator * (general_denumerator / this->denumerator)
		+ a.numerator * (general_denumerator / a.denumerator);
	int n = nod(general_numerator, general_denumerator);
	return Rational(general_numerator / n, general_denumerator / n);
}

Rational Rational::operator-(const Rational & a)
{
	int general_denumerator = nok(this->denumerator, a.denumerator);
	int general_numerator = this->numerator * (general_denumerator / this->denumerator)
		- a.numerator * (general_denumerator / a.denumerator);
	int n = nod(general_numerator, general_denumerator);
	return Rational(general_numerator / n, general_denumerator / n);
}

Rational Rational::operator*(const Rational & a)
{
	int general_denumerator = this->denumerator * a.denumerator;
	int general_numerator = this->numerator * a.numerator;
	int n = nod(general_numerator, general_denumerator);
	return Rational(general_numerator / n, general_denumerator / n);
}

Rational Rational::operator/(const Rational & a)
{
	int general_denumerator = this->denumerator * a.numerator;
	int general_numerator = this->numerator * a.denumerator;
	int n = nod(general_numerator, general_denumerator);
	return Rational(general_numerator / n, general_denumerator / n);
}

Rational Rational::operator+=(const Rational & a)
{
	int general_denumerator = nok(this->denumerator, a.denumerator);
	int general_numerator = this->numerator * (general_denumerator / this->denumerator)
		+ a.numerator * (general_denumerator / a.denumerator);
	int n = nod(general_numerator, general_denumerator);
	this->numerator = general_numerator / n;
	this->denumerator = general_denumerator / n;
	return *this;
}

Rational Rational::operator-=(const Rational & a)
{
	int general_denumerator = nok(this->denumerator, a.denumerator);
	int general_numerator = this->numerator * (general_denumerator / this->denumerator)
		- a.numerator * (general_denumerator / a.denumerator);
	int n = nod(general_numerator, general_denumerator);
	this->numerator = general_numerator / n;
	this->denumerator = general_denumerator / n;
	return *this;
}

Rational Rational::operator*=(const Rational & a)
{
	int general_denumerator = this->denumerator * a.denumerator;
	int general_numerator = this->numerator * a.numerator;
	int n = nod(general_numerator, general_denumerator);
	this->numerator = general_numerator / n;
	this->denumerator = general_denumerator / n;
	return *this;
}

Rational Rational::operator/=(const Rational & a)
{
	int general_denumerator = this->denumerator * a.numerator;
	int general_numerator = this->numerator * a.denumerator;
	int n = nod(general_numerator, general_denumerator);
	this->numerator = general_numerator / n;
	this->denumerator = general_denumerator / n;
	return *this;
}

int Rational::GetNumerator() const {
	return this->numerator;
}

int Rational::GetDenumerator() const {
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

float Rational::toFloat() const
{
	return (float)this->numerator / this->denumerator;
}

std::string Rational::toString() const
{
	return std::string(std::to_string(this->numerator) + "/" + std::to_string(this->denumerator));
}

int Rational::nod(int a, int b)
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

int Rational::nok(int a, int b)
{
	return (a * b) / nod(a, b);
}