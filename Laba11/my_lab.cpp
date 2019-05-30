#include "my_lab.h"
namespace my_lab
{
	bool is_initialized = false;
	void * memory_start;
	unsigned long long memory_size;
	std::list<mem_block> free_blocks;
	std::list<mem_block> allocated_blocks;

	bool operator==(mem_block a, mem_block b)
	{
		if (a.ptr == b.ptr && a.size == b.size) return true;
		return false;
	}

	void malloc_init(unsigned long long memory_size)
	{
		my_lab::memory_size = memory_size;
		my_lab::memory_start = std::malloc(memory_size);
		mem_block block;
		block.ptr = my_lab::memory_start;
		block.size = my_lab::memory_size;
		my_lab::free_blocks.push_back(block);
		my_lab::is_initialized = true;
	}

	void malloc_deinit()
	{
		std::free(my_lab::memory_start);
	}

	void * malloc(unsigned long long int size)
	{
		if (!my_lab::is_initialized) my_lab::malloc_init(1024 * 1024);
		mem_block * block = nullptr;
		auto it = my_lab::free_blocks.begin();
		for (auto iter = my_lab::free_blocks.begin(); iter != my_lab::free_blocks.end(); iter++)
		{
			if ((*iter).size >= size)
			{
				block = &(*iter);
				it = iter;
				break;
			}
		}
		if (block == nullptr) return NULL;
		mem_block bl;
		bl.ptr = block->ptr;
		bl.size = size;
		allocated_blocks.push_front(bl);
		if (block->size == size)
		{
			my_lab::free_blocks.remove(*block);
		}
		else
		{
			block->ptr = ((char *)block->ptr) + size;
			block->size -= size;
		}
		return bl.ptr;
	}

	void free(void * ptr)
	{
		if (my_lab::allocated_blocks.size() == 0) return;
		for (auto iter = my_lab::allocated_blocks.begin(); iter != my_lab::allocated_blocks.end(); iter++)
		{
			if(ptr == (*iter).ptr)
			{
				mem_block * block = nullptr;
				auto i = my_lab::free_blocks.begin();
				for (auto it = my_lab::free_blocks.begin(); it != my_lab::free_blocks.end(); it++)
				{
					if (((char *)ptr) + (*iter).size >= (*it).ptr)
					{
						i = it;
						if (((char *)ptr) + (*iter).size > (*it).ptr) break;
						block = &(*it);
						break;
					}
				}
				if (block == nullptr)
				{
					mem_block bl;
					bl.ptr = ptr;
					bl.size = (*iter).size;
					if (ptr != my_lab::memory_start)
						my_lab::free_blocks.insert(i, bl);
				}
				else
				{
					(*i).ptr = ptr;
					(*i).size += (*iter).size;
				}
				my_lab::allocated_blocks.remove(*iter);
				refactor_memory();
				return;
			}
		}
	}

	void refactor_memory()
	{
		for (auto iter = my_lab::free_blocks.begin(); iter != my_lab::free_blocks.end()--; iter++)
		{
			auto it = iter;
			it++;
			if (it == my_lab::free_blocks.end()) return;
			if (((char *)(*iter).ptr) + (*iter).size == (*it).ptr)
			{
				(*iter).size += (*it).size;
				my_lab::free_blocks.erase(it);
			}
		}
	}
}
