#include "Arduino.h"
#include "TemperatureLED.h"
#include "LED.h"

float Lower;
float Upper;

TemperatureLED::TemperatureLED(int pin, float lower, float upper) : LED(pin) {
  Lower = lower;
  Upper = upper;
};

bool TemperatureLED::WithinRange(float value) {
  // Lower < value <= Upper;
  return Lower < value && value <= Upper;
};

void TemperatureLED::Update(float temperature)
{
  if (WithinRange(temperature))
  {
    TurnOn();
  }
  else
  {
    TurnOff();
  }
}
