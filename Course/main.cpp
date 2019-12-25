#include "algorithm.h"



/**
Entry point
**/
int main(int argc, char** argv)
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

	std::vector<int> first, second, out;
	char tmp;
	bool flag;

	std::ifstream fin(input_filename);
	std::ofstream fout(output_filename);

	tmp = fin.get();
	while (tmp != '\n')
	{
		if (tmp == 'q') exit(0);
		first.push_back(tmp - '0');
		tmp = fin.get();
	}

	tmp = fin.get();
	while (tmp != '\n')
	{
		if (tmp == 'q') exit(0);
		second.push_back(tmp - '0');
		tmp = fin.get();
	}

	std::reverse(first.begin(), first.end());
	std::reverse(second.begin(), second.end());

	fast_multiply(first, second, out);

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