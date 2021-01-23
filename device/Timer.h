#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer {
	private:
		int _counter;
	public:
		int Threshold;
		bool Enabled;

		int GetProgress();

		bool CounterAboveThreshold();

		void Increment();

		void Reset();

		Timer(int threshold);
};

#endif // !Timer_h
