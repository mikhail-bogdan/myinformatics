#include <fstream>
#include <vector>
#include "database.h"

void Database::add(const Person& person)
{
	this->persons.push_back(person);
}

void Database::erase(const Person& person)
{
	this->persons.remove(person);
}

void Database::load(const std::string& filename)
{
	std::ifstream stream;
	stream.open(filename, std::ofstream::in | std::ofstream::binary);

	stream.seekg(0, std::ifstream::end);
	int filesize = stream.tellg();
	stream.seekg(0, std::ifstream::beg);

	std::vector<char> buf(filesize);
	stream.read(buf.data(), filesize);

	Person person;

	int pos = 0;
	while (filesize > 0)
	{
		int size = person.load(buf.data() + pos);
		filesize -= size;
		pos += size;
		this->persons.push_back(person);
	}
}

void Database::save(const std::string& filename)
{
	std::vector<char> buffer;

	std::ofstream stream;
	stream.open(filename, std::ofstream::out | std::ofstream::binary);

	for (auto iter = this->persons.begin(); iter != this->persons.end(); iter++)
	{
		buffer = (*iter).save();
		stream.write(buffer.data(), buffer.size());
	}
}

std::ostream& operator<<(std::ostream& stream, const Database& db)
{
	for (auto iter = db.persons.begin(); iter != db.persons.end(); iter++)
	{
		stream << (*iter) << std::endl;
	}
	return stream;
}
