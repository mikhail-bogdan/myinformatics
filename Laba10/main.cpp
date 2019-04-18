#include "file_streamer.h"
#include "my_lab.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	string filename_in = "new.txt", filename_out = "new2.txt";
	update_file(filename_in, filename_out);
	return 0;
}