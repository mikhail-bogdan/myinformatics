#pragma once


struct Point { int x; int y; int z; };

bool operator ==(const Point& a, const Point& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

std::ostream& operator << (std::ostream& stream, const Point& a)
{
	return stream << "Point { x=" << a.x << ", y=" << a.y << ", z=" << a.z << " }";
}


template <class T>
void test_func(T t1, T t2, T t3, T t4)
{
	list<T> l;
	l.push_back(t1);
	l.push_back(t2);
	l.push_front(t3);
	l.push_front(t4);

	std::cout << "size: " << l.size() << std::endl;

	l.find_and_erase(t3);

	std::cout << "size: " << l.size() << std::endl;

	for (int i = -1; i < 4; i++)
	{
		std::cout << "index: " << i << "   ";
		try
		{
			std::cout << "value: " << l.at(i) << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

	}

	l.find_and_erase(t1);
	l.find_and_erase(t2);
	l.find_and_erase(t4);

	std::cout << "size: " << l.size() << std::endl << std::endl;
}