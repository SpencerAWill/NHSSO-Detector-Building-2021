#include "Arduino.h"
#include "Thermistor.h"

int Beta;
float T0;
float R0;
int ReadPin;

Thermistor::Thermistor(int pin, int beta, double t0, double r0) {
	ReadPin = pin;
	Beta = beta;
	T0 = t0;
	R0 = r0;
};

int Thermistor::GetADC() {
	return analogRead(ReadPin);
};