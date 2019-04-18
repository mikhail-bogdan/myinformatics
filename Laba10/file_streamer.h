#pragma once
#include <string>

class file_streamer {
public:
	file_streamer();
	file_streamer(std::string filename, char mode);
	file_streamer(const char * filename, char mode);
	~file_streamer();

	void open(std::string filename, char mode);
	void open(const char * filename, char mode);
	void close();

	char read();
	void read(char * buffer, int len);
	std::string readLine();
	void write(char c);
	void write(const char * data, int len);
	void flush();
	bool feof();

	file_streamer operator<<(char c);
	file_streamer operator<<(const char * line);
	file_streamer operator<<(std::string line);
	void operator>>(char &c);
	void operator>>(std::string &line);

private:
	FILE * fd = NULL;
	char mode;
};