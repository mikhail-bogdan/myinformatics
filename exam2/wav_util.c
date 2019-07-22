#include "wav_util.h"

DWORD load_wav_file(const char* filename, WAVE_HEADER* wav_hdr, DATA_CHUNK* data_chunk)
{
	FILE* file = NULL;
	fopen_s(&file, filename, "rb");

	if (file == NULL)
	{
		if (errno == ENOENT)
			return INPUT_FILE_NOT_FOUND;
		return INPUT_FILE_OPEN_ERROR;
	}

	DWORD result = 0;
	
	if((result = read_wave_header(file, wav_hdr)) != NO_ERRORS)
	{
		fclose(file);
		return result;
	}
	if ((result = read_data_chunk(file, data_chunk, wav_hdr->wBitsPerSample)) != NO_ERRORS)
	{
		fclose(file);
		return result;
	}

	fclose(file);
	return NO_ERRORS;
}

/* 
������ WAVE_HEADER, ������������ ��� ������������
� ���������� ��� ������, ��� 0, ���� ��� � �������
*/
DWORD read_wave_header(FILE* file, WAVE_HEADER* wav_hdr)
{
	char buf[4];
	DWORD i;
	DWORD j;
	DWORD bytecnt = 0;		// ������� ����������� �� ����� ����
	
	// ������ ����� ���������, ��� �������������� ������ � ������� � ��� DATA_CHUNK
	if (fread((char*)wav_hdr, sizeof(WAVE_HEADER), 1, file) != 1)
		return FILE_READ_ERROR;	// ����� �� ������ ������

	// ��������� ������������ �������
	if (strncmp(wav_hdr->riff, "RIFF", 4) != 0)
		return ILLEGAL_HEADER;	// ���� riff �� �������� �������� "RIFF"

	if (strncmp(wav_hdr->wawefmt, "WAVEfmt ", 8) != 0)
		return ILLEGAL_HEADER;  // ���� wavefmt �� �������� �������� "WAVEfmt "

	if (wav_hdr->wFormatTag != WAVE_FORMAT_PCM)
		return ILLEGAL_FORMAT;	// ������ ����� - �� WAVE_FORMAT_PCM, ��� ����� ���� ���� �� ������
								// ������ - MP3 , ADPCM , ...
	if (wav_hdr->wBitsPerSample != 8 && wav_hdr->wBitsPerSample != 16)
		return ILLEGAL_FORMAT;

	if (wav_hdr->fmtsize > 16)	// � ����������� ����� ��������� ����� ������� ������,
	{							// ���� ��������� ������ �����, ��� ��� �� ����������
		i = (SHORT)wav_hdr->fmtsize;
		while (i > 16)
		{
			j = min(sizeof(buf), i - 16);
			if (fread(buf, j, 1, file) != 1)
				return FILE_READ_ERROR;
			i -= j;
		}
		wav_hdr->fmtsize = 16L;		// ��� WAVEFORMAT ����� ����� ����� 16 ����
	}
	return NO_ERRORS;
}


/*
������ DATA_CHUNK � ������ �������, ������������ �� ������������
� ���������� ��� ������, ��� 0, ���� ��� � �������
*/
DWORD read_data_chunk(FILE * file, DATA_CHUNK * dat_hdr, SHORT bitsPerSample)
{
	char buf[4];
	DWORD i;
	DWORD j;
	DWORD bytecnt = 0;		// ������� ����������� �� ����� ����


	// ���� "data" ����
	while (bytecnt <= MAXHDRLEN)	// ������ �� ������������� �� �� �����
	{
		/*  ��������� ��������� ���������� chunk'a  */
		if (fread((char*) dat_hdr, sizeof(DATA_CHUNK) - sizeof(void *), 1, file) != 1)
			return FILE_READ_ERROR;		// ������ ������
		i = dat_hdr->datasize;		// ������

		/* ��������, �������� �� ����������� ������������ ������� data-�����*/
		if (strncmp((char*)dat_hdr->data, "data", 4) == 0)
		{	  // ����� data chunk
			dat_hdr->samples = malloc(dat_hdr->datasize);
			if (dat_hdr->samples == NULL) return MEMORY_ALLOC_ERROR;
			if (fread(dat_hdr->samples, 1, dat_hdr->datasize, file) != dat_hdr->datasize)
				return FILE_READ_ERROR;
			return NO_ERRORS;								// ���������� �����, header ��������
		}
		// ��� �� "data" chunk, ����������
		bytecnt += i;	// ������� ����� �� DATA_CHUNK
		while (i > 0)
		{
			j = min(sizeof(buf), i);
			if (fread(buf, j, 1, file) != 1)
				return FILE_READ_ERROR;
			i -= j;
		}

	}
	return ILLEGAL_HEADER;	// ������-������, � �� �����
}

DWORD process_wav_file(WAVE_HEADER* wav_hdr, DATA_CHUNK* data_chunk, int first, int last)
{
	if (first * wav_hdr->nAvgBytesPerSec >= data_chunk->datasize) return BUFFER_OVERFLOW_ERROR;
	wav_hdr->nSamplesPerSec <<= 1;
	wav_hdr->nAvgBytesPerSec <<= 1;
	data_chunk->datasize = min(data_chunk->datasize, last * wav_hdr->nAvgBytesPerSec / 2) - first * wav_hdr->nAvgBytesPerSec / 2;
	DWORD size = data_chunk->datasize * 2 - wav_hdr->nChannels;
	if (wav_hdr->wBitsPerSample == 8)
	{
		BYTE* samples = (BYTE*)data_chunk->samples;
		samples += first * wav_hdr->nAvgBytesPerSec / 2;
		BYTE* new_samples = (BYTE*)malloc(size);
		if (new_samples == NULL) return MEMORY_ALLOC_ERROR;

		for(DWORD i = 0; i < data_chunk->datasize - 1; i += wav_hdr->nChannels)
		{
			for (WORD j = 0; j < wav_hdr->nChannels; j++)
			{
				new_samples[i * 2 + j] = samples[i + j];
				new_samples[wav_hdr->nChannels + i * 2 + j] = (((DWORD)samples[i + j]) + samples[i + wav_hdr->nChannels]) / 2;
			}
		}
		new_samples[size - 1] = samples[data_chunk->datasize - 1];
		data_chunk->samples = new_samples;
		data_chunk->datasize = size;
		
		free(samples - first * wav_hdr->nAvgBytesPerSec / 2);
	}
	else
	{
		WORD* samples = (WORD*)data_chunk->samples;
		samples += first * wav_hdr->nAvgBytesPerSec / 2;
		WORD* new_samples = (WORD*)malloc(size * sizeof(WORD));
		if (new_samples == NULL) return MEMORY_ALLOC_ERROR;

		for (DWORD i = 0; i < data_chunk->datasize - 1; i += wav_hdr->nChannels)
		{
			for (WORD j = 0; j < wav_hdr->nChannels; j++)
			{
				new_samples[i * 2 + j] = samples[i + j];
				new_samples[wav_hdr->nChannels + i * 2 + j] = (((DWORD)samples[i + j]) + samples[i + wav_hdr->nChannels]) / 2;
			}
		}
		new_samples[size - 1] = samples[data_chunk->datasize - 1];
		data_chunk->samples = new_samples;
		data_chunk->datasize = size;
		free(samples - first * wav_hdr->nAvgBytesPerSec / 2);
	}
	return 0;
}

DWORD save_wav_file(const char* filename, WAVE_HEADER* wav_hdr, DATA_CHUNK* data_chunk)
{
	FILE* file = NULL;
	fopen_s(&file, filename, "wb");

	if (file == NULL)
	{
		return OUTPUT_FILE_OPEN_ERROR;
	}

	if (fwrite(wav_hdr, sizeof(WAVE_HEADER), 1, file) != 1)
	{
		fclose(file);
		return FILE_WRITE_ERROR;
	}
	if (fwrite(data_chunk, sizeof(DATA_CHUNK) - sizeof(data_chunk->samples), 1, file) != 1)
	{
		fclose(file);
		return FILE_WRITE_ERROR;
	}
	if (fwrite(data_chunk->samples, 1, data_chunk->datasize, file) != data_chunk->datasize)
	{
		fclose(file);
		return FILE_WRITE_ERROR;
	}


	fclose(file);
	return NO_ERRORS;
}
