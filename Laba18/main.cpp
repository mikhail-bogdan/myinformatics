#include "database.h"

int main()
{
	Person person, person2;
	person.firstName = "asdasd";
	person.year = 9999;
	person.passport = 9999999999;
	person.gender = 1;
	std::vector<char> buf;
	buf = person.save();
	person2.load(buf.data());
	person2.passport = 9999999995;
	Database db, db2;
	db.add(person);
	db.add(person2);
	person.passport = 9999999990;
	db.add(person);
	std::cout << db << std::endl;
	db.save("test.txt");
	db2.load("test.txt");
	std::cout << db2;
	return 0;
}