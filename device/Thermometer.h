#ifndef Thermometer_h
#define Thermometer_h

#include "Thermistor.h"
#include "VoltageDivider.h"
#include "VoltageCalculator.h"

class Thermometer
{
  private:
    int _pin;
    Thermistor *_thermistor;
    VoltageCalculator *_vCalculator;
    VoltageDivider *_vDivider;
    float GetAverageAnalog();
    float AnalogToVoltage(int analogValue);
    float VoltageToResistance(float voltage);
    float ResistanceToKelvin(float resistance);
    float KelvinToCelsius(float kelvin);
  public:
    unsigned int SampleAmount;
    int TemperatureOffset;
    Thermometer(Thermistor *thermistor, int voltageDividerPin);
    float ReadTemperature();
};


#endif
