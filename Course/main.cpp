#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <algorithm>


const int mod = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1 << 20;

void usage(std::string);
void run_benchmark();
void run_interactive();
const std::string time_print(long long);

bool my_strcmp(const char* a, const char* b)
{
	while (*a != 0 || *b != 0)
	{
		if (*a != *b) return false;
		a++;
		b++;
	}
	return *a == *b;
}

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
				int  u = a[(long long)i + j], v = int(a[(long long)i + j + len / 2] * 1ll * w % mod);
				a[(long long)i + j] = u + v < mod ? u + v : u + v - mod;
				a[(long long)i + j + len / 2] = u - v >= 0 ? u - v : u + mod - v;
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
			out[i] += a[j] * b[(long long)i - j];
		out[(long long)i + 1] += out[i] / 10;
		out[i] %= 10;
	}
}


int main(int argc, char ** argv)
{
	std::string input_filename, output_filename;

	switch (argc)
	{
	case 2:
		if (my_strcmp(argv[1], "-b") || my_strcmp(argv[1], "--bench"))
			run_benchmark();
		if (my_strcmp(argv[1], "-i") || my_strcmp(argv[1], "--interactive"))
			run_interactive();
		if (my_strcmp(argv[1], "-h") || my_strcmp(argv[1], "--help"))
			usage(argv[0]);
		usage(argv[0]);
	case 3:
		input_filename = argv[1];
		output_filename = argv[2];
		break;
	default:
		usage(argv[0]);
	}

	std::vector<int> a, b, out;
	char c;
	bool flag;

	std::ifstream fin(input_filename);
	std::ofstream fout(output_filename);

	c = fin.get();
	while (c != '\n')
	{
		if (c == 'q') exit(0);
		a.push_back(c - '0');
		c = fin.get();
	}

	
	c = fin.get();
	while (c != '\n')
	{
		if (c == 'q') exit(0);
		b.push_back(c - '0');
		c = fin.get();
	}

	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());

	fast_multiply(a, b, out);

	std::reverse(out.begin(), out.end());

	flag = false;

	for (auto iter = out.begin(); iter != out.end(); iter++)
	{
		if (*(iter) != 0) flag = true;
		if (flag)
			fout << (char)('0' + (*iter));
	}
	fout << "\n";


	return 0;
}


void usage(std::string line)
{
	std::cout << "Usage: " << line << " <input_file> <output_file>" << "\n" <<
		"       or" << "\n" <<
		"       " << line << " [options]" << "\n" <<
		"Options:" << "\n"
		"  -i, --interactive : interactive mode" << "\n" <<
		"  -b, --bench : run benchmark" << "\n" <<
		"  -h, --help : display this message" << "\n";
	exit(0);
}

void run_benchmark()
{
	std::vector<int> number1, number2, result;
	
	for(int i = 0; i < 10000; i++)
		for (int j = 9; j >= 0; j--)
		{
			number1.push_back(j);
			number2.push_back((j + 6) % 10);
		}

	std::chrono::high_resolution_clock clock;
	
	std::cout << "benchmark running: 10000x10000 digits" << "\n";

	auto tp1 = clock.now();
	multiply(number1, number2, result);
	auto tp2 = clock.now();

	std::cout << "default multiply: " << time_print(std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count()) << "\n";

	tp1 = clock.now();
	fast_multiply(number1, number2, result);
	tp2 = clock.now();

	std::cout << "fast multiply: " << time_print(std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count()) << "\n";

	std::cout << "finished" << "\n";

	exit(0);
}

const std::string time_print(long long millis)
{
	std::stringstream out;
	int ms = millis % 1000;
	millis /= 1000;
	int secs = millis % 60;
	millis /= 60;
	int mins = millis % 60;
	millis /= 60;
	int hours = millis;

	if (hours)
		out << hours << "h ";
	if (mins)
		out << mins << "m ";
	if (secs)
		out << secs << "s ";
	out << ms << "ms";
	return out.str();
}


void run_interactive()
{
	char c;
	std::vector<int> a, b, out;
	bool flag;
	std::cout << "type q for exit" << "\n";
	do
	{
		std::cout << "Enter first  number: ";
		c = std::getchar();
		while (c != '\n')
		{
			if (c == 'q') exit(0);
			a.push_back(c - '0');
			c = std::getchar();
		}
		
		std::cout << "Enter second number: ";
		c = std::getchar();
		while (c != '\n')
		{
			if (c == 'q') exit(0);
			b.push_back(c - '0');
			c = std::getchar();
		}

		std::reverse(a.begin(), a.end());
		std::reverse(b.begin(), b.end());

		fast_multiply(a, b, out);

		a.resize(0);
		b.resize(0);

		std::reverse(out.begin(), out.end());

		std::cout << "Result: ";

		flag = false;

		for (auto iter = out.begin(); iter != out.end(); iter++)
		{
			if (*(iter) != 0) flag = true;
			if (flag)
				std::cout << (char)('0' + (*iter));
		}
		std::cout << "\n";
	} while (1);
}