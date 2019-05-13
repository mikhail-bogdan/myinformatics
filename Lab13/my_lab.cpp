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

int mod(int n) {
	if (n < 0) return -n;
	return n;
}

Time::operator char*()
{
	int secs, mins, hours;
	hours = (mod(this->time) / 3600) % 24;
	mins = (mod(this->time) / 60) % 60;
	secs = mod(this->time) % 60;
	int i = 0;
	if (this->time < 0) this->data[i++] = '-';
	this->data[i++] = '0' + hours / 10;
	this->data[i++] = '0' + hours % 10;
	this->data[i++] = ':';
	this->data[i++] = '0' + mins / 10;
	this->data[i++] = '0' + mins % 10;
	this->data[i++] = ':';
	this->data[i++] = '0' + secs / 10;
	this->data[i++] = '0' + secs % 10;
	this->data[i++] = '\0';
	return this->data;
}
