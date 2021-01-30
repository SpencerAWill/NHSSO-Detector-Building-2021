#ifndef Thermistor_h
#define Thermistor_h

class Thermistor {
	public:
		int Beta;
		float T0;
		float R0;
		Thermistor(int beta, double t0, double r0);
};

#endif
