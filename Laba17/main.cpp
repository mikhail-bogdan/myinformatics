#include "list.h"
#include <iostream>
#include "test.h"



void f()
{
	list<int> l;
	l.push_back(22);
}

int main()
{
	f();
	test_func(1, 2, 3, 4);
	test_func(1.2, 3.4, 5.6, 6.7);
	Point p1, p2, p3, p4;
	p1.x = p2.z = 0;
	p1.y = p2.y = 1;
	p1.z = p2.x = 2;
	p3.x = p4.z = 3;
	p3.y = p4.x = 4;
	p3.z = p4.y = 5;
	test_func(p1, p2, p3, p4);

	return 0;
}
