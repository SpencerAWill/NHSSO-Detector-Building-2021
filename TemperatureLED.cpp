#include "Arduino.h"
#include "TemperatureLED.h"
#include "LED.h"

int Lower;
int Upper;

TemperatureLED::TemperatureLED(int pin, int lower, int upper) : LED(pin) {
  Lower = lower;
  Upper = upper;
};

bool TemperatureLED::WithinRange(float value) {
  return value <= Upper && value > Lower;
};
