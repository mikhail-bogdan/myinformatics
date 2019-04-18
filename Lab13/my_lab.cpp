#include "my_lab.h"

Time::Time() {
	Time(0);
}

Time::Time(int time) {
	this->time = time;
}

int Time::operator+(int time) {
	return this->time + time;
}

int Time::operator-(int time)
{
	return this->time - time;
}

void Time::operator+=(int time) {
	this->time += time;
}

void Time::operator-=(int time) {
	this->time -= time;
}

void Time::operator=(int time) {
	this->time = time;
}

void Time::operator=(Time a) {
	this->time = a.time;
}

bool Time::operator==(Time a) {
	return this->time == a.time;
}

bool Time::operator!=(Time a) {
	return this->time != a.time;
}

bool Time::operator>(Time a) {
	return this->time > a.time;
}

bool Time::operator<(Time a) {
	return this->time < a.time;
}

bool Time::operator>=(Time a) {
	return this->time >= a.time;
}

bool Time::operator<=(Time a) {
	return this->time <= a.time;
}

void Time::operator++() {
	this->time++;
}

void Time::operator--() {
	this->time--;
}

Time::operator int() {
	return this->time;
}
