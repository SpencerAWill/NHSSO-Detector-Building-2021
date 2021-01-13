#ifndef Correction_h
#define Correction_h

#include "Arduino.h"






class TemperatureCorrector {
	TemperatureCorrector();
	float Correct(float voltage);
};




#endif // !Correction_h
