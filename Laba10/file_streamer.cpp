#include "file_streamer.h"

file_streamer::file_streamer() {
	this->fd = NULL;
}

file_streamer::file_streamer(std::string filename, char mode) {
	open(filename, mode);
}

file_streamer::file_streamer(const char * filename, char mode) {
	open(filename, mode);
}

file_streamer::~file_streamer() {
	this->close();
}

void file_streamer::open(std::string filename, char mode) {
	open(filename.c_str(), mode);
}

void file_streamer::open(const char * filename, char mode) {
	if (!filename || !mode) {
		return;
	}
	this->close();
	fopen_s(&this->fd, filename, mode == 'w' ? "w" : "r");
	this->mode = mode == 'w' ? 'w' : 'r';
}

void file_streamer::close() {
	if (this->fd) {
		fclose(this->fd);
		this->fd = NULL;
	}
}

char file_streamer::read() {
	return getc(this->fd);
}

void file_streamer::read(char * buffer, int len) {
	if (!buffer) return;
	fread(buffer, sizeof(char), len, this->fd);
}

std::string file_streamer::readLine() {
	std::string line = "";
	char s = getc(this->fd);
	while (s != '\n' && s != '\0') {
		line += s;
		s = getc(this->fd);
	}
	line += s;
	return line;
}

void file_streamer::write(char c) {
	fputc(c, this->fd);
}

void file_streamer::write(const char * data, int len) {
	if (!data) return;
	fwrite(data, sizeof(char), len, this->fd);
}

void file_streamer::flush() {
	if (this->fd && this->mode == 'w') fflush(this->fd);
}

bool file_streamer::feof()
{
	return std::feof(this->fd);
}

file_streamer file_streamer::operator<<(char c) {
	if (this->mode != 'w') return (*this);
	this->write(c);
	return (*this);
}

file_streamer file_streamer::operator<<(const char * line) {
	if (!line || this->mode != 'w') return (*this);
	this->write(line, strlen(line));
	return (*this);
}

file_streamer file_streamer::operator<<(std::string line) {
	if (this->mode != 'w') return (*this);
	this->write(line.c_str(), line.length());
	return (*this);
}

void file_streamer::operator>>(char & c) {
	if (this->mode != 'r') return;
	c = this->read();
}

void file_streamer::operator>>(std::string & line) {
	if (this->mode != 'r') return;
	line = this->readLine();
}