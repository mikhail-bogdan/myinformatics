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

Time::operator char*()
{
	int secs, mins, hours;
	hours = (this->time / 3600) % 24;
	mins = (this->time / 60) % 60;
	secs = this->time % 60;
	this->data[0] = '0' + hours / 10;
	this->data[1] = '0' + hours % 10;
	this->data[2] = ':';
	this->data[3] = '0' + mins / 10;
	this->data[4] = '0' + mins % 10;
	this->data[5] = ':';
	this->data[6] = '0' + secs / 10;
	this->data[7] = '0' + secs % 10;
	this->data[8] = '\0';
	return this->data;
}
