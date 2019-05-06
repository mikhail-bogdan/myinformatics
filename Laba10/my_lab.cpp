#include "my_lab.h"

void update_file(std::string filename_in, std::string filename_out)
{
	file_streamer file_in(filename_in, 'r'), file_out(filename_out, 'w');

	char c;
	std::string function_name, argument;
	std::vector<std::string> functions;
	while (1)
	{
		file_in >> c;
		if (c == '#')
		{
			read_define(&file_in);
		}
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{
			function_name = c;
			file_in >> c;
			while (c != '(')
			{
				function_name += c;
				file_in >> c;
			}
			int count = 1;
			argument = "";
			while (count)
			{
				file_in >> c;
				if (c == '(') count++;
				if (c == ')') count--;
				if (!count) break;
				argument += c;
			}
			functions.push_back(function_name + "(" + argument + ");");
			
			while (c != '{') file_in >> c;
			count = 1;
			while (count)
			{
				file_in >> c;
				if (c == '{') count++;
				if (c == '}') count--;
			}
		}
		if (file_in.feof()) break;
	}
	std::string data = "";
	for (auto function = functions.begin(); function != functions.end(); function++)
	{
		data += ((std::string)*function) + "\n\n";
	}
	file_out << data;
}

void read_define(file_streamer * file)
{
	std::string str;
	(*file) >> str;
	
}

void read_comment(file_streamer * file)
{

}
