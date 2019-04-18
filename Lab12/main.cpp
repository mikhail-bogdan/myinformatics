#include "my_lab.h"
#include <iostream>

int main() {
	Rational a(1, 10);
	Rational b(3, 10);
	Rational c(1, 1);
	c *= a + b;
	std::cout << c.toString() << std::endl;
	std::getchar();
	//std::getchar();
	return 0;
}