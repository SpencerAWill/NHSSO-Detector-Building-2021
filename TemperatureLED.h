#ifndef TemperatureLED_h
#define TemperatureLED_h

#include "Arduino.h"
#include "LED.h"

class TemperatureLED : public LED {
  public:
    int Lower;
    int Upper;
    TemperatureLED(int pin, int lower, int upper);
    bool WithinRange(float value);
};

#endif
