/*
Написать функцию, вычисляющую с заданной точностью eps, значение y = x ^ (1 / k)
по итерационной формуле: y[0] = 1; y[n - 1] = y[n] + (x / (y[n] ^ (k - 1)) - y[n]) / k,
где n = 0, 1, 2, ...
*/
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

//для заголовочного файла
/*
#ifndef MY_H
#define MY_H

	float signification(int k, int x, int eps);

#endif
*/

using namespace std;

float signification(int k, int x, int eps) {
	int deg = 0;
	if (k < 0) {
		deg = k;
		k = -1 * k;
	}
	float t = 0.0;
	float *y = new float[eps];
	int i = eps - 1;
	y[i + 1] = 1.0;
	while (i > 0) {
		t = x / pow(y[i + 1], k - 1);
		y[i] = y[i + 1] + ((t - y[i + 1]) / k);
		i--;
	}
	if (deg < 0) y[i + 1] = 1 / y[i + 1];
	return y[i + 1];
}

int main() {
	int k = 0, x = 0, eps = 0;
	double y = 0.0;
	cout << "x = ";
	cin >> x;
	if (x < 0) {
		cout << "x should be positive!\nTry again!";
		exit(1);
	}
	cout << "k = ";
	cin >> k;
	cout << "Remember: the larger eps, the more accurate the result!\neps = ";
	cin >> eps;
	if (eps < 1) {
		cout << "eps should be positive and not be equal to one!" << "\n" << "Try again!";
		exit(1);
	}
	y = signification(k, x, eps);
	cout << "y = " << setprecision(10) << y << endl;

	return 0;
}
