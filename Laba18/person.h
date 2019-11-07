#pragma once

#include <string>
#include <iostream>

class Person
{
public:
	std::string firstName = "";
	std::string secondName = "";
	unsigned short year = 0;
	bool gender = 0;
	unsigned long long passport = 0;

	Person(){}
	Person(const Person& person);

	int load(const char* buf);
	char* save(int& size);

	friend std::ostream& operator<<(std::ostream& stream, const Person& person);
	bool operator==(const Person& person) const;
};