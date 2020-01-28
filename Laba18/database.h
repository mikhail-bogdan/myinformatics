#pragma once

#include <list>
#include <iostream>

#include "person.h"

class Database
{
private:
	std::list<Person> persons;
public:
	void add(const Person& person);
	void erase(const Person& person);

	void load(const std::string& filename);
	void save(const std::string& filename);
	
	friend std::ostream& operator<<(std::ostream& stream, const Database& db);
};