#pragma once
#include "Monitor.h"
class Consumer {
private:
	Monitor<char>& container;
	int number;
	mutex& consoleMutex;
	void print(char character){
		lock_guard<mutex>consoleLock(consoleMutex);
		cout << "Consumber nb " << number << ": " << character << endl;
		this_thread::sleep_for(chrono::milliseconds(10));
	}
public:
	Consumer(Monitor<char>&_container,int number,mutex& consoleMutex) :
		container(_container),number(number),consoleMutex(consoleMutex) {}
	void operator()() {
		char character = container.load();
		print(character);
		while (character != EOF) {
			character = container.load();
			print(character);
		}
	}
};
