#ifndef Button_h
#define Button_h

#include "Arduino.h"


class Button {
public:
	int Pin;

	Button(int pin);

	int ReadStatus();
};


#endif
