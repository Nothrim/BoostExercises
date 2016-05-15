#pragma once
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
using namespace boost;
class Semafor
{
private:
	int resourceCounter;
	mutex counterMutex;
	condition_variable counterDifferentThanZero;
public:
	Semafor(int count):resourceCounter(count){}
	void signalize() {
		unique_lock<mutex> counterLock(counterMutex);
		++resourceCounter;
		counterDifferentThanZero.notify_one();
	}
	void wait() { 
		unique_lock<mutex> counterLock(counterMutex);
		while (resourceCounter == 0)counterDifferentThanZero.wait(counterLock);
		--resourceCounter;
	}
	bool tryWaiting() {
		unique_lock<mutex> counterLock(counterMutex);
		if (resourceCounter != 0) {
			--resourceCounter;
			return true;
		}
		return false;
	}
	int value() { return resourceCounter; }
};