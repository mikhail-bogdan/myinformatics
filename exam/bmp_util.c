#include "bmp_util.h"

DWORD load_bmp_file(const char * filename, BITMAPFILEHEADER * BFH, BITMAPINFOHEADER * BIH, RGBQUAD*** RGB)
{
	FILE* file = NULL;
	fopen_s(&file, filename, "rb");

	if (file == NULL)
	{
		if (errno == ENOENT)
			return INPUT_FILE_NOT_FOUND;
		return INPUT_FILE_OPEN_ERROR;
	}

	int result = 0;
	if ((result = fread(BFH, sizeof(BITMAPFILEHEADER), 1, file)) != 1)
	{
		fclose(file);
		return FILE_READ_ERROR;
	}

	if ((result = fread(BIH, sizeof(BITMAPINFOHEADER), 1, file)) != 1)
	{
		fclose(file);
		return FILE_READ_ERROR;
	}

	int h, w;
	w = BIH->biWidth;
	h = BIH->biHeight;
	int s = 0;
	if ((3 * w) % 4 != 0) s = 4 - (3 * w) % 4;

	(*RGB) = malloc(sizeof(RGBQUAD*) * h);
	for (int i = 0; i < h; i++) {
		(*RGB)[i] = malloc(sizeof(RGBQUAD) * w);
	}

	//fseek(file, BFH->bfOffBits, SEEK_SET);
	for (int i = h - 1; i >= 0; i--) {
		fread(*((*RGB) + i), sizeof(RGBQUAD), w, file);
		fseek(file, s, SEEK_CUR);
	}
	return NO_ERRORS;
}

DWORD process_bmp_file(BITMAPFILEHEADER* BFH, BITMAPINFOHEADER* BIH, RGBQUAD** RGB, int width, int height)
{
	unsigned char temp;
	for (int i = 0; i < BIH->biHeight && i < height; i++) {
		for (int j = 0; j < BIH->biWidth && j < width; j++) {
			temp = RGB[i][j].rgbRed;
			RGB[i][j].rgbRed = RGB[i][j].rgbGreen;
			RGB[i][j].rgbGreen = temp;
		}
	}

	return NO_ERRORS;
}

DWORD save_bmp_file(const char* filename, BITMAPFILEHEADER* BFH, BITMAPINFOHEADER* BIH, RGBQUAD** RGB)
{
	FILE* file = NULL;
	fopen_s(&file, filename, "wb");

	if (file == NULL)
	{
		return OUTPUT_FILE_OPEN_ERROR;
	}

	if (fwrite(BFH, sizeof(BITMAPFILEHEADER), 1, file) != 1)
	{
		fclose(file);
		return FILE_WRITE_ERROR;
	}
	if (fwrite(BIH, sizeof(BITMAPINFOHEADER), 1, file) != 1)
	{
		fclose(file);
		return FILE_WRITE_ERROR;
	}

	char temp = 0;
	int s = 0;
	if ((3 * BIH->biWidth) % 4 != 0) s = 4 - (3 * BIH->biWidth) % 4;

	for (int i = BIH->biHeight - 1; i >= 0; i--) {
		for (int j = 0; j < BIH->biWidth; j++)
			fwrite(&RGB[i][j], sizeof(RGBQUAD), 1, file);
		if (s != 0)
			fwrite(&temp, 1, s, file);
	}
	return NO_ERRORS;
}
