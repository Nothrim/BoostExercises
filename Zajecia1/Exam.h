#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Semafor.h"
#include <boost\thread\thread.hpp>
#include <boost\thread\mutex.hpp>
#include <boost\random\linear_congruential.hpp>
#include <boost\random\uniform_int.hpp>
minstd_rand task1Generator(time(NULL));
uniform_int<> task1Distribution(100, 500);
int task2Array[100];
 class Task1 {
private:
	boost::mutex& consoleMutex;
	int threadNumber;
public:
	Task1(boost::mutex& consoleMutex,int threadNumber) :consoleMutex(consoleMutex),threadNumber(threadNumber) {}
	void operator()() {
		for (int i = 0; i < 10; i++) {
			{
				boost::lock_guard<boost::mutex>lock(consoleMutex);
				cout << "i=" << i << " number=" << threadNumber << endl;
			}
			this_thread::sleep_for(chrono::milliseconds(task1Distribution(task1Generator)));
		}
	}
};
class Task2 {
private:
	int n;
public:
	boost::condition_variable* task2isGeneratingData;
	Task2(int n) :n(n) { task2isGeneratingData = new condition_variable(); }
	void operator()() {
		if (n > 100)n = 100;
		for (int i = 0; i < n; i++) {
			task2Array[i] = i;
		}
		task2isGeneratingData->notify_one();
	}
};
class Task3 {
private:
	Semafor& consoleSemafor;
	Semafor& max3ThreadsSemafor;
	int threadNumber;
public:
	Task3(Semafor& max3ThreadsSemafor,Semafor& consoleSemafor, int threadNumber) :max3ThreadsSemafor(max3ThreadsSemafor),
		consoleSemafor(consoleSemafor), threadNumber(threadNumber) {}
	void operator()() {
		max3ThreadsSemafor.wait();
		for (int i = 0; i < 10; i++) {
			{
				consoleSemafor.wait();
				cout << "i=" << i << " number=" << threadNumber<<" id="<<this_thread::get_id() << endl;
				consoleSemafor.signalize();
			}
			this_thread::sleep_for(chrono::milliseconds(task1Distribution(task1Generator)));
		}
		max3ThreadsSemafor.signalize();
	}
};
