#include "Arduino.h"
#include "Thermistor.h"

int Beta;
float T0;
float R0;

Thermistor::Thermistor(int beta, double t0, double r0) {
	Beta = beta;
	T0 = t0;
	R0 = r0;
};
