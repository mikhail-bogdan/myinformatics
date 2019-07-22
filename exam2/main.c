#include "wav_util.h"

void print_error(const char* type, DWORD code);

int main(int argc, char** argv)
{
	if (argc < 5)
	{
		printf("Usage: exam.exe <input file> <output file> <first> <last>");
		getchar();
		return 0;
	}
	WAVE_HEADER hdr;
	DATA_CHUNK data;
	DWORD result = 0;
	if ((result = load_wav_file(argv[1], &hdr, &data)) != NO_ERRORS)
	{
		int n = errno;
		print_error("load file", result);
		getchar();
		return -1;
	}
	if ((result = process_wav_file(&hdr, &data, atoi(argv[3]), atoi(argv[4]))) != NO_ERRORS)
	{
		print_error("process file", result);
		getchar();
		return -1;
	}
	if ((result = save_wav_file(argv[2], &hdr, &data)) != NO_ERRORS)
	{
		print_error("save file", result);
		getchar();
		return -1;
	}

	return 0;
}

void print_error(const char * type, DWORD code)
{
	printf("ERROR: %s\n", type);
	printf("Error type: ");
	switch (code)
	{
	case ILLEGAL_HEADER:
		printf("Illegal header");
		break;
	case ILLEGAL_FORMAT:
		printf("Illegal format");
		break;
	case FILE_READ_ERROR:
		printf("File read");
		break;
	case INPUT_FILE_OPEN_ERROR:
		printf("Input file open");
		break;
	case INPUT_FILE_NOT_FOUND:
		printf("Input file not found");
		break;
	case OUTPUT_FILE_OPEN_ERROR:
		printf("Output file open");
		break;
	case FILE_WRITE_ERROR:
		printf("File write");
		break;
	case MEMORY_ALLOC_ERROR:
		printf("Memory allocation");
		break;
	case BUFFER_OVERFLOW_ERROR:
		printf("Buffer overflow");
		break;
	default:
		printf("Error type: Unknown");
		break;
	}
	printf("\nPress Enter...");
}