#include "lab.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

class C : public Worker
{
public:
	int calcSalary() {
		return salary * coef;
	}
private:
	int salary = 2;
	int coef = 3;
};

int main()
{
	WorkerBase base;
	base.add(new C);
	C * c = new C;
	base.add(c);
	int d = base.calcTotalSalary();
	return 0;
}
