#pragma once
#include "ZmienneWarunkowe.h"
template <typename T>
class Monitor {
private:
	T data;
	bool hasData;
	mutex& dataMutex;
	condition_variable hasNewData;
	condition_variable dataWasTaken;
public:
	Monitor(mutex& dataMutex) :dataMutex(dataMutex), hasData(false) {}
	void save(T data) {
		unique_lock<mutex> lock(dataMutex);
		if (hasData)dataWasTaken.wait(lock);
		hasData = true;
		this->data = data;
		hasNewData.notify_one();

	}
	T load() {
		unique_lock<mutex>lock(dataMutex);
		if (!hasData)hasNewData.wait(lock);
		hasData = false;
		dataWasTaken.notify_one();
		return data;
	}
};

