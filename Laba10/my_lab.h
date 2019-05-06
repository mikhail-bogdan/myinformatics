#pragma once
#include "file_streamer.h"
#include <string>
#include <vector>

enum Type
{
	undefined,
	type,
	name,

};

struct Instruction
{
	Type type;
	char * data;
	int len;
};

void update_file(std::string filename_in, std::string filename_out);

void read_define(file_streamer * file);
void read_comment(file_streamer * file);

