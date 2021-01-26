#ifndef Thermometer_h
#define Thermometer_h

#include "Thermistor.h"

class Thermometer
{
  private:
    Thermistor *_thermistor;
    float GetAverageADC();
    float ADCToVoltage(float adcValue);
    float VoltageToResistance(float voltage);
    float ResistanceToKelvin(float resistance);
    float KelvinToCelsius(float kelvin);
  public:
    unsigned int SampleAmount;
    unsigned int SamplingTimeMS;
    int TemperatureOffset;
    Thermometer(Thermistor *thermistor);
    float ReadTemperature();
};


#endif
