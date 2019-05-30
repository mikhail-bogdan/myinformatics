#include "my_lab.h"

int main()
{
	char * ptr = (char *)my_lab::malloc(100);
	char * ptr2 = (char *)my_lab::malloc(200);
	my_lab::free(ptr);
	ptr = (char *)my_lab::malloc(150);
	my_lab::free(ptr);
	my_lab::free(ptr2);
	my_lab::malloc_deinit();
	return 0;
}