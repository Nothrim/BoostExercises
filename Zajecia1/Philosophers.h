#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Semafor.h"
#include <boost\thread\thread.hpp>
#include <boost\thread\mutex.hpp>
#include <boost\random\linear_congruential.hpp>
#include <boost\random\uniform_int.hpp>
#define MAX_DELAY 1000
#define PHILOSOPHERS 5
#define MEALS 3
using namespace std;
using namespace boost;
minstd_rand generator(time(NULL));
uniform_int<> distribution(0, MAX_DELAY);

class Fork {
private:
	int number;
	Semafor* semafor;
public:
	Fork(int number) :number(number) {
		semafor = new Semafor(1);
	}
	void pickUp() {
		string o;
		o.append("Picked up fork nb:").append(to_string(number)).append("\n");
		cout << o;
		semafor->wait();
	}
	void putDown() {
		string o;
		o.append("Put down fork nb:").append(to_string(number)).append("\n");
		semafor->signalize();
	}
};

class Philosopher {
private:
	int number;
	Fork* leftFork;
	Fork* rightFork;
	int consumedMeals;
	Semafor& mealDistributor;
public:
	Philosopher(int n,Fork* leftFork,Fork* rightFork,Semafor& mealDistributor) :number(n), consumedMeals(0),leftFork(leftFork),rightFork(rightFork),
	mealDistributor(mealDistributor){}
	void operator()(){
		while (consumedMeals < MEALS) {
					mealDistributor.wait();
					leftFork->pickUp();
					rightFork->pickUp();
					int mealTime = distribution(generator);
					cout << "Philosopher " << number << " is eating meal number " << consumedMeals << " for " << mealTime << " ms" << endl;
					this_thread::sleep_for(chrono::milliseconds(mealTime));
					cout << "Philosopher " << number << " has finished meal number " << consumedMeals << endl;
					++consumedMeals;
					leftFork->putDown();
					rightFork->putDown();
					mealDistributor.signalize();
		}
		cout << "Philosopher " << number << " is really fat right now" << endl;
	}
};