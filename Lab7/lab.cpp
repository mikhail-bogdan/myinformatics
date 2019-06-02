#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "lab.h"
#include <cstdlib>
#include <string.h>

List::List()
{
}

List::~List()
{
	this->RemoveAll();
}

void List::Add(Worker * data)
{
	Node * node = new Node;
	if (this->size == 0)
	{
		this->first = this->last = node;
		node->next = nullptr;
	}
	else
	{
		this->last->prev = node;
		node->next = this->last;
	}
	node->prev = nullptr;
	this->last = node;
	node->data = data;
	size++;
}

void List::Erase(Worker * data)
{
	Node * n = nullptr;
	for (Node * iter = this->first; iter != last; iter = iter->prev)
	{
		if (iter->data == data)
		{
			n = iter;
			break;
		}
	}

	if (this->last->data == data) n = this->last;

	if (n == nullptr) return;

	if (n->next)
	{
		n->next->prev = n->prev;
	}
	else
	{
		this->first = n->prev;
	}

	if (n->prev)
	{
		n->prev->next = n->next;
	}
	else
	{
		this->last = n->next;
	}

	delete n->data;
	delete n;
	size--;
}

Worker * List::Find(int pos)
{
	if (pos >= size) return nullptr;
	Node * iter = this->first->prev;
	for (int i = 0; i < pos; i++)
	{
		iter = iter->prev;
	}
	return iter->data;
}

void List::RemoveAll()
{
	Node * tmp;
	if (this->size == 0) return;
	for (Node * iter = this->first->prev; iter != last; iter = iter->prev)
	{
		tmp = iter;
		iter = iter->next;
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		delete tmp->data;
		delete tmp;
	}
	delete this->first->data;
	delete this->first;
	delete this->last->data;
	delete this->last;
	this->first = this->last = nullptr;
	this->size = 0;
}

int WorkerBase::calcTotalSalary()
{
	int salary = 0;
	for (List::Node * iter = this->first; iter != this->last; iter = iter->prev)
	{
		salary += iter->data->calcSalary();
	}
	salary += this->last->data->calcSalary();
	return salary;
}
