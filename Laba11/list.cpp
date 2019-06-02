#include "list.h"

namespace my_lab
{
	char strlen(char * word)
	{
		char i = 0;
		while (word[i++] != 0);
		return i - 1;
	}

	bool is_more(char * word1, char * word2)
	{
		char len1 = strlen(word1), len2 = strlen(word2);
		if (len1 != len2)
		{
			return len1 < len2;
		}
		else
		{
			for (char i = 0; i < len1; i++)
			{
				if (word1[i] != word2[i])
				{
					return word1[i] < word2[i];
				}
			}
			return 1;
		}
	}

	bool strcmp(char * word1, char * word2)
	{
		int i = 0;
		while (word1[i] == word2[i] && word1[i] != 0 && word2[i] != 0) i++;
		return word1[i] == 0 && word2[i] == 0;
	}

	/*void push_back(char * word, list * list)
	{
		node * n = (node *)my_lab::malloc(sizeof(node));
		strcpy(n->word, word);
		n->forward = list->last;
		list->last->back = n;
		n->back = 0;
		list->last = n;
	}*/

	list * sort(list * list1)
	{
		list * list3 = (list *)my_lab::malloc(sizeof(list));
		node * temp = list1->last, * max = list1->first;
		while (1)
		{
			if (is_more(temp->word, max->word))
			{
				max = temp;
			}
			if (temp->back == 0) break;
			temp = temp->back;
		}
		list3->first = list3->last = (node *)my_lab::malloc(sizeof(node));
		list3->first->forward = list3->first->back = 0;
		list3->first->word = max->word;
		del_node(max, list1);
		while (1)
		{
			if (list1->first->forward == 0 && list1->first->back == 0)
			{
				temp = (node *)my_lab::malloc(sizeof(node));
				list3->last->forward = temp;
				temp->back = list3->last;
				list3->last = temp;
				temp->word = list1->first->word;
				temp->forward = 0;
				break;
			}
			else
			{
				max = list1->first;
				if (max->forward != 0) temp = list1->last;
			}
			while (1)
			{
				if (is_more(temp->word, max->word))
				{
					max = temp;
				}
				if (temp->back == 0) break;
				temp = temp->back;
			}
			temp = (node *)my_lab::malloc(sizeof(node));
			list3->last->forward = temp;
			temp->back = list3->last;
			list3->last = temp;
			temp->word = max->word;
			temp->forward = 0;
			del_node(max, list1);
		}
		return list3;
	}

	void rm_duplicate(list * list1)
	{
		node * cur = list1->first, * next;
		while (1)
		{
			next = cur->forward;
			if (strcmp(cur->word, next->word))
			{
				del_node(next, list1);
			}
			else {
				cur = cur->forward;
			}
			if (cur->forward == 0) return;
		}
	}

	void del_node(node * node, list * list)
	{
		if (node->back != 0 && node->forward != 0)
		{
			node->back->forward = node->forward;
			node->forward->back = node->back;
		}
		else if (node->back == 0)
		{
			node->forward->back = 0;
			list->first = node->forward;
		}
		else if (node->forward == 0)
		{
			node->back->forward = 0;
			list->last = node->back;
		}
		else
		{
			list->first = 0;
			list->last = 0;
		}
		my_lab::free(node);
	}

	void print_list(struct list * data)
	{
		node * temp = data->first;
		while (1)
		{
			printf("%s ", temp->word);
			if (temp->forward == 0) break;
			temp = temp->forward;
		}
	}
}