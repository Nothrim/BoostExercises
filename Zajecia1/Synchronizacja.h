#pragma once
#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost\thread\thread.hpp>
#include <vector>
#include <boost\thread\mutex.hpp>
using namespace std;
using namespace boost;
#define NUMBER_OF_THREADS 5
#define CHARACTERS_TO_WRITE 128
#define delay 1
class Watek {
private:
	char character;
	string& lancuch;
	mutex& characterMutex;
public:
	Watek(char character, string& lancuch,mutex& characterMutex ) :character(character), lancuch(lancuch),characterMutex(characterMutex) {}
	void operator()() {
		lock_guard<mutex>lock(this->characterMutex);
		for (int i = 0; i < CHARACTERS_TO_WRITE; ++i) {
			this_thread::sleep_for(chrono::milliseconds(delay));
			lancuch[i] = character;
		}
	}
};