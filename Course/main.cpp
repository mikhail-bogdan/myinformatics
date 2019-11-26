#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

const int mod = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1 << 20;

int max(int a, int b)
{
	return a > b ? a : b;
}

void swap(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}

int gcd(int a, int b, int& x, int& y)
{
	if (a == 0)
	{
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

int reverse(int a, int m)
{
	int x, y;
	int g = gcd(a, m, x, y);
	if (g != 1)
		return -1;
	else
	{
		return (x % m + m) % m;
	}
}

void fft(std::vector<int>& a, bool invert)
{
	int n = (int)a.size();



	for (int i = 1, j = 0; i < n; ++i)
	{
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1)
	{
		int wlen = invert ? root_1 : root;
		for (int i = len; i < root_pw; i <<= 1)
			wlen = int(wlen * 1ll * wlen % mod);
		for (int i = 0; i < n; i += len)
		{
			int w = 1;
			for (int j = 0; j < len / 2; ++j)
			{
				int  u = a[i + j], v = int(a[i + j + len / 2] * 1ll * w % mod);
				a[i + j] = u + v < mod ? u + v : u + v - mod;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u + mod - v;
				w = int(w * 1ll * wlen % mod);
			}
		}
	}
	if (invert)
	{
		int nrev = reverse(n, mod);
		for (int i = 0; i < n; ++i)
			a[i] = int(a[i] * 1ll * nrev % mod);
	}
}

void fast_multiply(std::vector<int> a, std::vector<int> b, std::vector<int>& out)
{
	size_t n = 1;
	while (n < max(a.size(), b.size()))  n <<= 1;
	n <<= 1;

	a.resize(n);
	b.resize(n);
	std::vector<long long> tmp;

	fft(a, false), fft(b, false);
	for (size_t i = 0; i < n; i++)
		a[i] = 1ll * a[i] * b[i] % mod;
	fft(a, true);

	out.resize(n);

	int carry = 0;
	for (size_t i = 0; i < n; ++i)
	{
		out[i] = a[i] + carry;
		carry = out[i] / 10;
		out[i] %= 10;
	}
}

void multiply(std::vector<int> a, std::vector<int> b, std::vector<int>& out)
{

	int n = a.size() + b.size();
	a.resize(n);
	b.resize(n);
	out.resize(n);
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < i; j++)
			out[i] += a[j] * b[i - j];
		out[i + 1] += out[i] / 10;
		out[i] %= 10;
	}
}


int main()
{
	std::vector<int> a, b, out;
	char n;
	FILE* f;
	fopen_s(&f, "input.txt", "r");

	while ((n = fgetc(f)) != '\n') a.push_back(n - '0');
	while ((n = fgetc(f)) != '\n') b.push_back(n - '0');
	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());

	std::chrono::high_resolution_clock clock;

	auto tp1 = clock.now();
	multiply(a, b, out);
	auto tp2 = clock.now();

	std::cout << "default multiplication: " << std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1).count() << " microseconds" << std::endl;



	tp1 = clock.now();
	fast_multiply(a, b, out);
	tp2 = clock.now();

	std::cout << "fast multiplication: "<< std::chrono::duration_cast<std::chrono::microseconds>(tp2 - tp1).count() << " microseconds" << std::endl;

/*
	bool flag = false;

	for (auto iter = out.begin(); iter != out.end(); iter++)
	{
		if (*(iter) != 0) flag = true;
		if(flag)
			printf("%c", (char)('0' + *(iter)));
	}
*/

	getchar();
	return 0;
}