#pragma once
#include <exception>

template <class T>
class list{
private:
	class node {
	public:
		node* next = nullptr;
		node* prev = nullptr;
		T data;
	};
	node* first = nullptr;
	node* last = nullptr;
	int length = 0;
public:
	~list();
	void push_back(const T& value);
	void push_front(const T& value);
	int size() const;
	void find_and_erase(const T& value);
	T at(int pos) const;
};

template<class T>
list<T>::~list()
{
	if (this->length)
	{
		for (node* iter = this->first; iter != this->last;)
		{
			node* i = iter;
			iter = iter->next;
			delete i;
		}
		delete this->last;
	}
}

template<class T>
void list<T>::push_back(const T& value)
{
	node* new_node = new node;
	new_node->data = value;
	if (this->last == nullptr)
	{
		this->first = new_node;
		this->last = new_node;
	}
	else
	{
		this->last->next = new_node;
		new_node->prev = this->last;
		this->last = new_node;
	}
	this->length++;
}

template<class T>
void list<T>::push_front(const T& value)
{
	node* new_node = new node;
	new_node->data = value;
	if (this->first == nullptr)
	{
		this->first = new_node;
		this->last = new_node;
	}
	else
	{
		this->first->prev = new_node;
		new_node->next = this->first;
		this->first = new_node;
	}
	this->length++;
}

template<class T>
void list<T>::find_and_erase(const T& value)
{
	if (!this->length) return;
	node* iter = this->first;
	for (; iter != this->last; iter = iter->next)
	{
		if (iter->data == value)
		{
			if (iter == this->first)
			{
				this->first = iter->next;
			}
			else
			{
				iter->prev->next = iter->next;
			}
			iter->next->prev = iter->prev;

			this->length--;
			delete iter;
			return;
		}
	}
	if (iter->data == value)
	{
		if (iter == this->first)
		{
			this->first = nullptr;
			this->last = nullptr;
		}
		else
		{
			this->last = iter->prev;
			iter->prev->next = nullptr;
		}
		this->length--;
		delete iter;
	}
}


template <class T>
int list<T>::size() const
{
	//int size = 1;
	//for (node* iter = this->first; iter != this->last; iter = iter->next, size++);
	return this->length;
}

template <class T>
T list<T>::at(int pos) const
{
	if (pos >= this->length || pos < 0)
		throw std::exception("ERROR: Position is larger than size or smaller than zero");

	node* iter = this->first;
	for (int i = 0; i < pos; iter = iter->next, i++);
	return iter->data;
}