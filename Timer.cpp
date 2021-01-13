#include "Arduino.h"
#include "Timer.h"

int _counter;
int Threshold;
bool Enabled;

Timer::Timer(int threshold) {
	Threshold = threshold;
	Enabled = true;
	_counter = 0;
};

int Timer::GetProgress() {
	return _counter;
};

bool Timer::CounterAboveThreshold() {
	return _counter >= Threshold;
};

void Timer::Increment() {
	if (Enabled) {
		_counter++;
	}
};

void Timer::Reset() {
	_counter = 0;
};