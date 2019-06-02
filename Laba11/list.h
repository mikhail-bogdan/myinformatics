#pragma once
#include "my_lab.h"

namespace my_lab
{
	struct node {
		node * back;
		char * word;
		node * forward;
	};
	struct list {		
		node * first;
		node * last;
	};

	list * sort(list * list1);

	void rm_duplicate(list * list1);
	
	void del_node(node * node, list * list);

	char strlen(char * word);

	bool is_more(char * word1, char * word2);

	bool strcmp(char * word1, char * word2);

	void print_list(list * data);
}