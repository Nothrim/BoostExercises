#pragma once#include <cstdlib>
#include <boost/thread/thread.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <iostream>
#include "Semafor.h"
using namespace std;
using namespace boost;
using namespace boost::random;
minstd_rand trainGenerator;
uniform_int_distribution<int> trainDistribution(0, 500);
class Peron;
class Train {
private:
	string name;
	Peron &peron;
	Peron &sparePeron;
public:
	Train(string n, Peron& p1, Peron& p2);
	void operator()();
	string getName();
};
class Peron {
private:
	string name;
	bool empty;
public:
	Semafor* semafor;
	Peron(string n) :name(n), empty(true) { semafor = new Semafor(1); }
	void arrival(Train& t) {
		if (empty) {
			string info;
			info.append("Train ").append(t.getName()).append(" arrives on peron ")
				.append(name).append("\n");
			cout << info;
		}
		else {
			string info;
			info.append("Train ").append(t.getName()).append(" has crashed on peron ")
				.append(name).append("\n");
			cout << info;
		}
		empty = false;
	}
	void departure(Train& t) {
		string info;
		info.append("Train ").append(t.getName()).append(" has left peron ")
			.append(name).append("\n");
		cout << info;
		empty = true;
	}
	bool isEmpty() { return empty; }
};
Train::Train(string n, Peron& p1, Peron& p2) :name(n), peron(p1), sparePeron(p2) {}
void Train::operator()() {
		for (int i = 0; i < 3; i++) {
			this_thread::sleep_for(chrono::milliseconds(trainDistribution(trainGenerator)));
			if (peron.semafor->tryWaiting())
			{
				peron.arrival(*this);
				this_thread::sleep_for(chrono::milliseconds(trainDistribution(trainGenerator)));
				peron.departure(*this);
				peron.semafor->signalize();
			}
			else {
				sparePeron.semafor->wait();
				sparePeron.arrival(*this);
				this_thread::sleep_for(chrono::milliseconds(trainDistribution(trainGenerator)));
				sparePeron.departure(*this);
				sparePeron.semafor->signalize();
			}
		}
}
string Train::getName() { return name; }
