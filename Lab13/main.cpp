#include "my_lab.h"
#include <iostream>

int main() {
	Time time;
	time = 10000;
	std::cout << (char*)time << std::endl;
	time = time + 200;
	std::cout << (char*)time << std::endl;
	int a = time;
	std::getchar();
	return 0;
}