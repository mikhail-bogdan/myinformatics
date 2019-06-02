#include "list.h"

int main()
{
	/*char * ptr = (char *)my_lab::malloc(100);
	char * ptr2 = (char *)my_lab::malloc(200);
	my_lab::free(ptr);
	ptr = (char *)my_lab::malloc(150);
	my_lab::free(ptr);
	my_lab::free(ptr2);
	my_lab::malloc_deinit();*/
	int i = 0;
	char n, letter = 0;
	my_lab::node * temp = (my_lab::node *)my_lab::malloc(sizeof(my_lab::node));
	temp->word = (char *)my_lab::malloc(64);
	temp->back = 0;
	my_lab::node * first = temp, *last = temp;
	FILE * f;
	fopen_s(&f, "lab.txt", "r");
	while (1) {
		fscanf_s(f, "%c", &n, 1);
		if (n == '\n' || n == ' ') {
			temp->word[letter] = 0;
			if (n == '\n') break;
			else {
				temp = (my_lab::node *)my_lab::malloc(sizeof(my_lab::node));
				last->forward = temp;
				temp->back = last;
				temp->word = (char *)my_lab::malloc(64);
				temp->forward = 0;
				last = temp;
			}
			letter = 0;
		}
		if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122)) {
			temp->word[letter] = n;
			letter++;
		}
	}
	my_lab::list * list1, *list3;
	list1 = (my_lab::list *)my_lab::malloc(sizeof(my_lab::list));
	list1->first = first;
	list1->last = last;
	list3 = my_lab::sort(list1);
	my_lab::rm_duplicate(list3);
	my_lab::print_list(list3);
	getchar();
	return 0;
}