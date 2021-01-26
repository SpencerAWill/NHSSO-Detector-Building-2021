#ifndef TemperatureLED_h
#define TemperatureLED_h

#include "Arduino.h"
#include "LED.h"

class TemperatureLED : public LED {
  public:
    float Lower;
    float Upper;
    TemperatureLED(int pin, float lower, float upper);
    bool WithinRange(float value);
    void Update(float temperature);
};

#endif
