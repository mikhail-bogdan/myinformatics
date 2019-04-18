#pragma once

class Time {
public:
	Time();
	Time(int time);

	int operator+(int time);
	int operator-(int time);
	void operator+=(int time);
	void operator-=(int time);
	void operator=(int time);
	void operator=(Time a);
	bool operator==(Time a);
	bool operator!=(Time a);
	bool operator>(Time a);
	bool operator<(Time a);
	bool operator>=(Time a);
	bool operator<=(Time a);
	void operator++();
	void operator--();
	operator int();


private:
	int time;
};