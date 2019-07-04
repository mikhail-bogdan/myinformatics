// 10. �������� ���������, ����������� �� ��������� BMP ����� ����� BMP ����, � ������� ������ ����� �� �������� ( R, G, B ).
// R,G � B ( ����� �� 0 �� 255 ) ������� � ��������� ������.
//	1) ��������� ����� ������ �������� � �������������� ������ � ��������� ������
//	2) �����, ����� ��������� ����������, ������ ������� � ����������� ���������� ������

#include <stdlib.h>
#include <string.h>
#include <iostream>

#pragma pack(1)

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

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	// ���������� ��������
	BITMAPFILEHEADER BFH;
	BITMAPINFOHEADER BIH;
	RGBQUAD** RGB;
	FILE* fin;
	FILE* fout;
	size_t k = 0;
	char file1[15] = { 0 };
	char file2[15] = { 0 };
	std::cout << "������� ��� ��������� �����: ";
	std::cin >> file1;
	std::cout << "������� ��� ��������������� �����: ";
	std::cin >> file2;
	fopen_s(&fin, file1, "rb");
	k = fread(&BFH, sizeof(BFH), 1, fin); // ������ �������� ��������� � ��������� BITMAPFILEHEADER // � ��������� 14, � ��������� ������, ��� 16, ������� ���� �������� 2
	if (k == 0) {
		std::cout << "������ ������! \n";
		exit(-1000);
	}
	k = fread(&BIH, sizeof(BIH), 1, fin); // ������ ��������� ����������� � ��������� BITMAPINFOHEADER 
	if (k == 0) {
		std::cout << "������ ������! \n";
		exit(-1000);
	}
	int h, w;
	w = BIH.biWidth;
	h = BIH.biHeight;
	int s = 0;
	if ((3 * w) % 4 != 0) s = 4 - (3 * w) % 4;

	fopen_s(&fout, file2, "wb");
	RGB = new RGBQUAD * [h];
	for (int i = 0; i < h; i++) {
		RGB[i] = new RGBQUAD[w];
	}
	for (int i = h - 1; i >= 0; i--) {
		for (int j = 0; j < w; j++) {
			fread(&RGB[i][j], sizeof(RGBQUAD), 1, fin);
		}
		fseek(fin, s, SEEK_CUR);
	}
	unsigned char temp;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			temp = RGB[i][j].rgbRed;
			RGB[i][j].rgbRed = RGB[i][j].rgbGreen;
			RGB[i][j].rgbGreen = temp;
		}
	}
	fwrite(&BFH, sizeof(BFH), 1, fout);
	fwrite(&BIH, sizeof(BIH), 1, fout);

	temp = 0;
	for (int i = h - 1; i >= 0; i--) {
		for (int j = 0; j < w; j++)
			fwrite(&RGB[i][j], sizeof(RGBQUAD), 1, fout);
		if(s != 0)
			fwrite(&temp, 1, s, fout);
	}
	fclose(fin);
	fclose(fout);
	std::cout << "����������. \n";
	system("pause");
	return 0;
}