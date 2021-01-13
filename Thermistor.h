#ifndef Thermistor_h
#define Thermistor_h

#include "Arduino.h"

class Thermistor {
	public:
		int Beta;
		float T0;
		float R0;
		int ReadPin;
		Thermistor(int pin, int beta, double t0, double r0);

		int GetADC();
};

#endif
