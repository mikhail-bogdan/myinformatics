#include <stdio.h>
#include <stdlib.h>

/*Написать программу, которая объединяет два упорядоченных списка слов в один упорядоченный список.
Функция merge должна получать указатели на оба списка и возвращать указатель на новый список.
Новый список выдать на экран.
*/

struct node{
	struct node * back;
	char * word;
	struct node * forward;
};

struct list {
	struct node * first;
	struct node * last;
};

char strlen(char * word) {
	char i = 0;
	while (word[i++] != 0);
	return i - 1;
}

char is_more(char * word1, char * word2) {
	char len1 = strlen(word1), len2 = strlen(word2);
	if (len1 != len2) {
		return len1 < len2;
	}
	else {
		for (char i = 0; i < len1; i++) {
			if (word1[i] != word2[i]) {
				return word1[i] < word2[i];
			}
		}
		return 1;
	}
}

void del_node(struct node * node, struct list * list1, struct list * list2) {
	if (node->back != 0 && node->forward != 0) {
		node->back->forward = node->forward;
		node->forward->back = node->back;
	}
	else if (node->back == 0) {
		node->forward->back = 0;
		list1->first = node->forward;
	}
	else if(node->forward == 0) {
		node->back->forward = 0;
		list2->last = node->back;
	}
	else {
		list1->first = 0;
		list2->last = 0;
	}
	free(node);
}

struct list * merge(struct list * list1, struct list * list2) {
	struct list * list3 = malloc(sizeof(struct list));
	struct node * temp = list2->last, * max = list1->first;
	list1->last->forward = list2->first;
	list2->first->back = list1->last;
	//list3->first = list3->last = max;
	while (1) {
		if (is_more(temp->word, max->word)) {
			max = temp;
		}
		if (temp->back == 0) break;
		temp = temp->back;
	}
	list3->first = list3->last = malloc(sizeof(struct node));
	list3->first->forward = list3->first->back = 0; 
	list3->first->word = max->word;
	del_node(max, list1, list2);
	while (1) {
		if (list1->first->forward == 0 && list1->first->back == 0) {
			temp = malloc(sizeof(struct node));
			list3->last->forward = temp;
			temp->back = list3->last;
			list3->last = temp;
			temp->word = list1->first->word;
			temp->forward = 0;
			break;
		}
		else {
			max = list1->first;
			if (max->forward != 0) temp = list2->last;
		}
		while (1) {
			if (is_more(temp->word, max->word)) {
				max = temp;
			}
			if (temp->back == 0) break;
			temp = temp->back;
		}
		temp = malloc(sizeof(struct node));
		list3->last->forward = temp;
		temp->back = list3->last;
		list3->last = temp;
		temp->word = max->word;
		temp->forward = 0;
		del_node(max, list1, list2);
	}
	return list3;
}

void print_list(struct list * data);

int main(){
	int i = 0;
	char n, letter = 0;
	struct node * temp = malloc(sizeof(struct node));
	temp->word = malloc(64);
	struct node * first = temp, * last = temp;
	struct node * first2, * last2;
	first->back = first->forward = 0;
	printf("Enter the first line: ");
	while (1) {
		scanf_s("%c", &n, 1);
		if (n == '\n' || n == ' ') {
			temp->word[letter] = 0;
			if (n == '\n') break;
			else {
				temp = malloc(sizeof(struct node));
				last->forward = temp;
				temp->back = last;
				temp->word = malloc(64);
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
	letter = 0;
	temp = malloc(sizeof(struct node));
	temp->back = temp->forward = 0;
	temp->word = malloc(64);
	last2 = first2 = temp;
	printf("Enter the second line: ");
	while (1) {
		scanf_s("%c", &n, 1);
		if (n == '\n' || n == ' ') {
			temp->word[letter] = 0;
			if (n == '\n') break;
			else {
				temp = malloc(sizeof(struct node));
				last2->forward = temp;
				temp->back = last2;
				temp->word = malloc(64);
				temp->forward = 0;
				last2 = temp;
			}
			letter = 0;
		}
		if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122)) {
			temp->word[letter] = n;
			letter++;
		}
	}
	struct list * list1, * list2, * list3;
	list1 = malloc(sizeof(struct list));
	list1->first = first;
	list1->last = last;
	list2 = malloc(sizeof(struct list));
	list2->first = first2; 
	list2->last = last2;
	n = strlen("len");
	list3 = merge(list1, list2);
	printf("Result: ");
	print_list(list3);
	getchar();
	getchar();
	return 0;
}

/*
abc bsa
dsa geaad
*/

void print_list(struct list * data) {
	struct node * temp = data->first;
	while (1) {
		printf("%s ", temp->word);
		if (temp->forward == 0) break;
		temp = temp->forward;
	}
}