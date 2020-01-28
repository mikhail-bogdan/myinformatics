#include <vector>
#include "person.h"

Person::Person(const Person& person)
{
	this->firstName = person.firstName;
	this->secondName = person.secondName;
	this->gender = person.gender;
	this->year = person.year;
	this->passport = person.passport;
}

int Person::load(const char* buf)
{
	int firstSize = strlen(buf), secondSize = strlen(buf + firstSize + 1);
	this->firstName = buf;
	this->secondName = buf + firstSize + 1;
	buf += firstSize + secondSize + 2;
	memcpy((char*)& this->year, buf, 2);
	if ((*(buf + 1)) & 0b10000000)
	{
		this->gender = 1;
		((char*)& this->year)[1] &= 0b01111111;
	}
	else
	{
		this->gender = 0;
	}
	buf += 2;
	memcpy((char*)& this->passport, buf, 5);
	return firstSize + secondSize + 9;
}

std::vector<char> Person::save()
{
	int firstSize = this->firstName.length(), secondSize = this->secondName.length();
	std::vector<char> buffer(firstSize + secondSize + 9);
	char* buf = buffer.data();

	memcpy(buf, this->firstName.c_str(), firstSize);
	buf += firstSize + 1;
	(*(buf - 1)) = 0;

	memcpy(buf, this->secondName.c_str(), secondSize);
	buf += secondSize + 1;
	(*(buf - 1)) = 0;

	memcpy(buf, (char*)& this->year, 2);

	if (this->gender)
		(*(buf + 1)) |= 0b10000000;
	buf += 2;

	memcpy(buf, (char*)& this->passport, 5);
	
	return buffer;
}

bool Person::operator==(const Person& person) const
{
	return this->passport == person.passport;
}

std::ostream& operator<<(std::ostream& stream, const Person& person)
{
	return stream << "FirstName: " << person.firstName << "  SecondName: " << person.secondName <<
		"  Year: " << person.year << "  Gender: " << (person.gender ? "Male" : "Female") <<
		"  Passport: " << person.passport;
}
