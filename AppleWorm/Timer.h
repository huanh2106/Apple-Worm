#pragma once
#ifndef TIMER_H
#define TIMER_H
#include "CommonFunc.h"
class Timer {
public:
	Timer();
	~Timer();
	void start();
	int get_ticks();

private:
	int start_tick;
	bool is_started;
};
#endif