#include "my_lab.h"
#include "polynomial.h"
#include <iostream>

int main()
{
	/*Polynomial a1(2, new Rational[2]{ Rational(3800, 2), Rational(3, 5)});
	Polynomial b1(2, new Rational[2]{ Rational(0, 10), Rational(3, 5) });
	std::cout << a1.toString() << std::endl;
	std::cout << b1.toString() << std::endl;

	Polynomial c1 = a1 + b1;
	std::cout << c1.toString();*/
	Rational a(10000, 200);
	Rational b(200, 10000);
	Rational c(1, 1);
	c = a + b;
	std::cout << c.toString() << std::endl;
	std::getchar();
	//std::getchar();
	return 0;
}