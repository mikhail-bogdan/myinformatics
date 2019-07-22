#include "bmp_util.h"

int main(int argc, char* argv[]) {
	// Объявление структур
	BITMAPFILEHEADER BFH;
	BITMAPINFOHEADER BIH;
	RGBQUAD** RGB;
	
	if (argc < 5)
	{
		printf("Usage: exam.exe <input file> <output file> <x border> <y border>");
		return 0;
	}

	load_bmp_file(argv[1], &BFH, &BIH, &RGB);
	process_bmp_file(&BFH, &BIH, RGB, atoi(argv[3]), atoi(argv[4]));
	save_bmp_file(argv[2], &BFH, &BIH, RGB);

	return 0;
}