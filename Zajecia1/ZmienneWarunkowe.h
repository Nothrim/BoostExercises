#pragma once
#include <cstdio>
#include <iostream>
#include <boost\thread\thread.hpp>
#include <boost\thread\mutex.hpp>
#include <boost\thread\condition.hpp>
#include <boost\random\linear_congruential.hpp>
#include <boost\random\uniform_int_distribution.hpp>
using namespace std;
using namespace boost;
using namespace boost::random;
#define WORK_TIME 5
uniform_int_distribution<int>waitTime(1, 5);