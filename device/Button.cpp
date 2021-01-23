#include "Arduino.h"
#include "Button.h"

Button::Button(int pin) {
	Pin = pin;
	pinMode(Pin, INPUT);
};

int Button::ReadStatus() {
	int buttonState = digitalRead(Pin);
	if (buttonState == HIGH)
		return 1;
	else
		return 0;
};