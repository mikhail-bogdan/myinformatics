#pragma once

class Worker
{
public:
	virtual int calcSalary() = 0;
};

class List
{
public:
	struct Node
	{
		Worker * data;
		Node * next;
		Node * prev;
	};
	List();
	~List();

	void add(Worker * data);
	virtual void erase(Worker * data);
	virtual Worker * find(int pos);
	void removeAll();

protected:
	Node * first = nullptr;
	Node * last = nullptr;
	int size = 0;
};

class WorkerBase : public List
{
public:
	int calcTotalSalary();
};

