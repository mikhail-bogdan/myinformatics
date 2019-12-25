#include "algorithm.h"

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

bool my_strcmp(const char* first, const char* second)
{
	if (first == nullptr || second == nullptr) return false;

	while (*first != 0 || *second != 0)
	{
		if (*first != *second) return false;
		first++;
		second++;
	}

	return *first == *second;
}

inline int max(int first, int second)
{
	return first > second ? first : second;
}

inline void swap(int& first, int& second)
{
	int c = first;
	first = second;
	second = c;
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


int gf_reverse(int a, int m)
{
	int x, y;
	int g = gcd(a, m, x, y);
	if (g != 1)
		return -1;
	else
		return (x % m + m) % m;
}


void fft(std::vector<int>& data, bool invert)
{
	int size = (int)data.size();

	for (int i = 1, j = 0; i < size; i++)
	{
		int bit = size >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(data[i], data[j]);
	}

	for (int len = 2; len <= size; len <<= 1)
	{
		int w = invert ? root_rev : root;
		for (int i = len; i < root_pw; i <<= 1)
			w = int(w * 1ll * w % mod);
		for (int i = 0; i < size; i += len)
		{
			int w_tmp = 1;
			for (int j = 0; j < len / 2; j++)
			{
				int  u = data[(long long)i + j], v = int(data[(long long)i + j + len / 2] * 1ll * w_tmp % mod);
				data[(long long)i + j] = u + v < mod ? u + v : u + v - mod;
				data[(long long)i + j + len / 2] = u - v >= 0 ? u - v : u + mod - v;
				w_tmp = int(w_tmp * 1ll * w % mod);
			}
		}
	}

	if (invert)
	{
		int size_rev = gf_reverse(size, mod);
		for (int i = 0; i < size; i++)
			data[i] = int(data[i] * 1ll * size_rev % mod);
	}
}


void fast_multiply(std::vector<int> first, std::vector<int> second, std::vector<int>& out)
{
	size_t len = 1;
	while (len < max(first.size(), second.size()))  len <<= 1;
	len <<= 1;

	first.resize(len);
	second.resize(len);

	fft(first, false), fft(second, false);
	for (size_t i = 0; i < len; i++)
		first[i] = 1ll * first[i] * second[i] % mod;
	fft(first, true);

	out.resize(len);

	int carry = 0;
	for (size_t i = 0; i < len; i++)
	{
		out[i] = first[i] + carry;
		carry = out[i] / 10;
		out[i] %= 10;
	}
}


void multiply(std::vector<int> first, std::vector<int> second, std::vector<int>& out)
{

	int size = first.size() + second.size();

	first.resize(size);
	second.resize(size);
	out.resize(size);

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < i; j++)
			out[i] += first[j] * second[(long long)i - j];
		out[(long long)i + 1] += out[i] / 10;
		out[i] %= 10;
	}
}

void usage(std::string path)
{
	std::cout << "Usage: " << path << " <input_file> <output_file>" << "\n" <<
		"       or" << "\n" <<
		"       " << path << " [options]" << "\n" <<
		"Options:" << "\n"
		"  -i, --interactive : interactive mode" << "\n" <<
		"  -b, --bench : run benchmark" << "\n" <<
		"  -h, --help : display this message" << "\n";
	exit(0);
}

void run_benchmark()
{
	std::vector<int> first, second, result;
	
	for (int i = 0; i < digits / 10; i++)
		for (int j = 9; j >= 0; j--)
		{
			first.push_back(j);
			second.push_back((j + shift) % 10);
		}

	std::chrono::high_resolution_clock clock;

	std::cout << "benchmark running: 10000x10000 digits" << "\n";

	auto tp1 = clock.now();
	multiply(first, second, result);
	auto tp2 = clock.now();

	std::cout << "default multiply: " << time_print(std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count()) << "\n";

	tp1 = clock.now();
	fast_multiply(first, second, result);
	tp2 = clock.now();

	std::cout << "fast multiply: " << time_print(std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count()) << "\n";

	std::cout << "finished" << "\n";

	exit(0);
}

void run_interactive()
{
	char tmp;
	std::vector<int> first, second, out;
	bool flag;
	std::cout << "type q for exit" << "\n";
	do
	{
		std::cout << "Enter first  number: ";
		tmp = std::getchar();
		while (tmp != '\n')
		{
			if (tmp == 'q') exit(0);
			first.push_back(tmp - '0');
			tmp = std::getchar();
		}

		std::cout << "Enter second number: ";
		tmp = std::getchar();
		while (tmp != '\n')
		{
			if (tmp == 'q') exit(0);
			second.push_back(tmp - '0');
			tmp = std::getchar();
		}

		std::reverse(first.begin(), first.end());
		std::reverse(second.begin(), second.end());

		fast_multiply(first, second, out);

		first.resize(0);
		second.resize(0);

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