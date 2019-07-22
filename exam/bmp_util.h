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
	short bfType; // ��� �����
	long bfSize; // ������ ����� � ������
	short bfReserved1; // ��������������� (������ ���� 0)
	short bfReserved2; // ��������������� (������ ���� 0)
	long bfOffBits; // ���������� � ������ �� BITMAPFILEHEADER �� �������� �����������
} BITMAPFILEHEADER; // -> ��������� ����� 

typedef struct B2 {
	int biSize; //������ ��������� BITMAPINFOHEADER � ������ 
	int biWidth; // ������ ����������� � �������� 
	int biHeight; // ������ ����������� � �������� 
	short int biPlanes; // ����� ���������� �� ���������� ������ (������ ���� 1)
	short int biBitCount; // ����� ��� �� ������� (1, 4, 8, 16, 24, 32)
	int biCompression; // ����� �������� �������� 
	int biSizeImage; // ������ ����������� � ������
	int biXPelsPerMeter; // �������������� ���������� ���������� ������ (� ��������/����)
	int biYPelsPerMeter; // ������������ ���������� ���������� ������ (� ��������/����)
	int biClrUsed; // ����� �������� �������� � ������� ������, ������� ������������ � ����������� 
	int biClrImportant; // ����� �������� ��������, ������� ��������� ������� ��� ������ �����������
} BITMAPINFOHEADER; // -> ��������� �����������

typedef struct R1 {
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
} RGBQUAD; // -> �������� �������

typedef unsigned int DWORD;

DWORD load_bmp_file(const char* filename, BITMAPFILEHEADER* BFH, BITMAPINFOHEADER* BIH, RGBQUAD*** RGB);

DWORD process_bmp_file(BITMAPFILEHEADER* BFH, BITMAPINFOHEADER* BIH, RGBQUAD** RGB, int width, int height);

DWORD save_bmp_file(const char* filename, BITMAPFILEHEADER* BFH, BITMAPINFOHEADER* BIH, RGBQUAD** RGB);