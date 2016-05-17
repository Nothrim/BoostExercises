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
void writeToConsole(string str) {
	cout << str;
}
class Fork {
private:
	int number;
	Semafor* semafor;
public:
	Fork(int number) :number(number) {
		semafor = new Semafor(1);
	}
	void pickUp() {
		writeToConsole(string().append("Picked up fork nb:").append(to_string(number)).append("\n"));
		semafor->wait();
	}
	void putDown() {
		writeToConsole(string().append("Put down fork nb:").append(to_string(number)).append("\n"));
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
					writeToConsole(string().append("Philosopher ").append(to_string(number)).append(" is eating meal number ").append(to_string(consumedMeals)).append(" for ")
						.append(to_string(mealTime)).append(" ms\n"));
					this_thread::sleep_for(chrono::milliseconds(mealTime));
					writeToConsole(string().append("Philosopher ").append(to_string(number)).append(" has finished meal number ").append(to_string(consumedMeals)).append("\n"));
					++consumedMeals;
					leftFork->putDown();
					rightFork->putDown();
					mealDistributor.signalize();
		}
		writeToConsole(string().append("Philosopher ").append(to_string(number)).append(" is really fat right now\n"));
	}
};