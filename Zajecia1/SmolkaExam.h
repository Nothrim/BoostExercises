#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Semafor.h"
#include <boost\thread\thread.hpp>
#include <boost\thread\mutex.hpp>
#include <boost\random\linear_congruential.hpp>
#include <boost\random\uniform_int.hpp>
char sTask2Array[75];
minstd_rand sTask1Generator(time(NULL));
uniform_int<> sTask1Distribution(100, 500);
int sN = 0;
boost::condition_variable sTask2Condition;
class STask1 {
private:
	boost::mutex& consoleMutex;
public:
	STask1(boost::mutex& consoleMutex) :consoleMutex(consoleMutex) {}
	void operator()() {
		for (int i = 0; i < 15; i++) {
			{
				boost::lock_guard<boost::mutex> consoleLock(consoleMutex);
				std::cout << "i=" << i << " id=" << this_thread::get_id()<<endl;
			}
			this_thread::yield();
		}
	}
};
void sTask2() {
	int n;
	if (sN > 75)n = 75;
	else n = sN;
	for (int i = 0; i < n; i++)
	{
		sTask2Array[i]= (char)(i + 32);
	}
	sTask2Condition.notify_one();
}