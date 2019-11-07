#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <fstream>

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