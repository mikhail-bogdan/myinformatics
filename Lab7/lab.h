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

	void Add(Worker * data);
	virtual void Erase(Worker * data);
	virtual Worker * Find(int pos);
	void RemoveAll();

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

