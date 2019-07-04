// 10. Написать программу, формирующую по исходному BMP файлу новый BMP файл, с заменой белого цвета на заданный ( R, G, B ).
// R,G и B ( числа от 0 до 255 ) указать в командной строке.
//	1) указывать имена файлов исходных и результирующих файлов в командной строке
//	2) файлы, после обработки заголовков, читать целиком в динамически заказанную память

#include <stdlib.h>
#include <string.h>
#include <iostream>

#pragma pack(1)

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

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	// Объявление структур
	BITMAPFILEHEADER BFH;
	BITMAPINFOHEADER BIH;
	RGBQUAD** RGB;
	FILE* fin;
	FILE* fout;
	size_t k = 0;
	char file1[15] = { 0 };
	char file2[15] = { 0 };
	std::cout << "Введите имя исходного файла: ";
	std::cin >> file1;
	std::cout << "Введите имя результирующего файла: ";
	std::cin >> file2;
	fopen_s(&fin, file1, "rb");
	k = fread(&BFH, sizeof(BFH), 1, fin); // читаем файловый заголовок в структуру BITMAPFILEHEADER // в структуре 14, а процессор думает, что 16, поэтому надо вычитать 2
	if (k == 0) {
		std::cout << "Ошибка чтения! \n";
		exit(-1000);
	}
	k = fread(&BIH, sizeof(BIH), 1, fin); // читаем заголовок изображения в структуру BITMAPINFOHEADER 
	if (k == 0) {
		std::cout << "Ошибка чтения! \n";
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
	std::cout << "Обработано. \n";
	system("pause");
	return 0;
}