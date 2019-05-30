#pragma once
#include <list>

namespace my_lab
{
	struct mem_block
	{
		void * ptr;
		int size;
	};

	bool operator==(mem_block a, mem_block b);

	void malloc_init(unsigned long long memory_size);
	void malloc_deinit();

	void refactor_memory();

	void * malloc(unsigned long long int size);

	void free(void * ptr);
}