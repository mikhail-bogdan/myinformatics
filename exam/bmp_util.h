#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma pack(1)

#define NO_ERRORS					0
#define ILLEGAL_HEADER				1
#define ILLEGAL_FORMAT				2
#define FILE_READ_ERROR				3
#define INPUT_FILE_OPEN_ERROR		4
#define INPUT_FILE_NOT_FOUND		5
#define OUTPUT_FILE_OPEN_ERROR		6
#define FILE_WRITE_ERROR			7
#define MEMORY_ALLOC_ERROR			8


typedef struct B1 {
	short bfType; // тип файла
	long bfSize; // размер файла в байтах
	short bfReserved1; // зарезервировано (должно быть 0)
	short bfReserved2; // зарезервировано (должно быть 0)
	long bfOffBits; // расстояние в байтах от BITMAPFILEHEADER до пикселей изображения
} BITMAPFILEHEADER; // -> параметры файла 

typedef struct B2 {
	int biSize; //размер структуры BITMAPINFOHEADER в байтах 
	int biWidth; // ширина изображения в пикселях 
	int biHeight; // высота изображения в пикселях 
	short int biPlanes; // число плоскостей на устройстве вывода (должно быть 1)
	short int biBitCount; // число бит на пискель (1, 4, 8, 16, 24, 32)
	int biCompression; // метод хранения пикселей 
	int biSizeImage; // размер изображения в байтах
	int biXPelsPerMeter; // горизонтальное разрешение устройства вывода (в пикселях/метр)
	int biYPelsPerMeter; // вертикальное разрешение устройства вывода (в пикселях/метр)
	int biClrUsed; // число цветовых индексов в таблице цветов, которые используются в изображении 
	int biClrImportant; // число цветовых индексов, которые считаются важными при выводе изображения
} BITMAPINFOHEADER; // -> параметры изображения

typedef struct R1 {
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
} RGBQUAD; // -> цветовая палитра

typedef unsigned int DWORD;

DWORD load_bmp_file(const char* filename, BITMAPFILEHEADER* BFH, BITMAPINFOHEADER* BIH, RGBQUAD*** RGB);

DWORD process_bmp_file(BITMAPFILEHEADER* BFH, BITMAPINFOHEADER* BIH, RGBQUAD** RGB, int width, int height);

DWORD save_bmp_file(const char* filename, BITMAPFILEHEADER* BFH, BITMAPINFOHEADER* BIH, RGBQUAD** RGB);