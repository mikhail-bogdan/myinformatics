#include "my_lab.h"
#include <iostream>

int main() {
	Time time;
	time = -1213;
	std::cout << (char*)time << std::endl;
	time += time + 1;
	std::cout << (char*)time << std::endl;
	time -= 7;
	std::cout << (char*)time << std::endl;
	time = 1213;
	std::cout << (char*)time << std::endl;
	int a = time;
	std::getchar();
	return 0;
}