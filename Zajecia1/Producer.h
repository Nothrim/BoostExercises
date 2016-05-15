#pragma once
#include "ZmienneWarunkowe.h"
#include "Monitor.h"

class Producer {
private:
	int time;
	Monitor<char>& container;
	char currentChar;
	minstd_rand generator;
	uniform_int_distribution<char> distribution;
	int number;
	mutex& consoleMutex;
	void print() {
		lock_guard<mutex> consoleLock(consoleMutex);
		cout << "Producer nb " << number << ": saved a char: " << currentChar << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
public:
	Producer(Monitor<char>& _container,int number,mutex& consoleMutex) :time(0), container(_container),
		distribution('a', 'z'),number(number),consoleMutex(consoleMutex) {}
	void operator()() {
		while (time < WORK_TIME) {
			currentChar = distribution(generator);
			container.save(currentChar);
			print();
			this_thread::sleep_for(chrono::milliseconds(waitTime(generator)));
			++time;
		}
		currentChar = EOF;
		container.save(currentChar);
		print();
		
	}

};