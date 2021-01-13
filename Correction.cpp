#include "Arduino.h"
#include "Correction.h"

TemperatureCorrector::TemperatureCorrector() {};

float TemperatureCorrector::Correct(float voltage) {
	float returnValue = 0;

	if (voltage >= 3.5) {
		returnValue = -10;
	}
	else {
		//lsrl
		returnValue = (1.6701 * voltage) - 3.3556
	}

	return returnValue * -1;
};