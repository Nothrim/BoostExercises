#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <boost/thread/thread.hpp>
using namespace std;
using namespace boost;
#define POINTS 10
class TworzenieWatkow {
private:
	double a, b;
	double *wartosc;
public:
	TworzenieWatkow(double _a,double _b,double *_wartosc):
		a(_a), b(_b), wartosc(_wartosc) {}
	void operator()() {
		cout << "Thread is working..." << endl;
		double h = (b - a) / POINTS;
		double s = sin(a);
		for (int i = 1; i < POINTS; i++) {
			this_thread::sleep_for(chrono::milliseconds(100));
			s += 2 * sin(a + i*h);
		}
		s += sin(b);
		*wartosc = s*h / 2;
		cout << "Thread has finished..." << endl;
	}
};