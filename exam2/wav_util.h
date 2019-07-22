#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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
#define BUFFER_OVERFLOW_ERROR		9

#define MAXHDRLEN			1000


typedef struct
{
	/*  ������������ RIFF  */
	BYTE	riff[4];		// ��� ������ ���� ����� RIFF
	DWORD	riffsize;		// ������ ����� - 8

	/* ������������ FORMAT, ��������� ������ WAV �����  */
	BYTE	wawefmt[8];			// ��� ������ ���� ����� "WAVEfmt "
	DWORD	fmtsize;			// ������ ������������ FORMAT - ����� ���� ������ 16 ��� 18
								// ��� ������������ ��������� WAV ���������� �������� 16
	WORD	wFormatTag;			// ������ ����� , ��� ���������� ������ WAVE_FORMAT_PCM ( == 1 )
	WORD	nChannels;			// ����� ������� ( 1 ��� 2 )
	DWORD	nSamplesPerSec;		// ����� �������� � ������� ( 8000, 11025, 22050 ��� 44100 )
	DWORD	nAvgBytesPerSec;	// ����� ���� � �������. 
	WORD	nBlockAlign;		// ������������ ����� ������
	SHORT	wBitsPerSample;		// ����� ��� �� ������ ( 8 ��� 16 )
} WAVE_HEADER, * LPWAVE_HEADER;

typedef struct
{
	BYTE	data[4];
	DWORD	datasize;
	void* samples;
} DATA_CHUNK;

DWORD load_wav_file(const char * filename, WAVE_HEADER* wav_hdr, DATA_CHUNK* data_chunk);

DWORD read_wave_header(FILE* file, WAVE_HEADER* wav_hdr);

DWORD read_data_chunk(FILE* file, DATA_CHUNK* dat_hdr, SHORT bitsPerSample);

DWORD process_wav_file(WAVE_HEADER* wav_hdr, DATA_CHUNK* data_chunk);

DWORD save_wav_file(const char* filename, WAVE_HEADER* wav_hdr, DATA_CHUNK* data_chunk);

