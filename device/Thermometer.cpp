#include "Thermometer.h"
#include "Thermistor.h"
#include "Arduino.h"

Thermistor *_thermistor;
unsigned int SampleAmount;
int TemperatureOffset;

Thermometer::Thermometer(Thermistor *thermistor)
{
  SampleAmount = 10;
  _thermistor = thermistor;
  TemperatureOffset = 0;
}

float Thermometer::GetAverageADC()
{
  int arraySize = SampleAmount;
  float adcs[arraySize];
  float cumulativeADC = 0;
  for (int i = 0; i < arraySize; i++)
  {
    cumulativeADC += (float)_thermistor->GetADC();
  }

  return cumulativeADC / arraySize;
}

float Thermometer::ADCToVoltage(float adcValue)
{
  float sourceVoltage = 5.00;
  int maxADC = 1023;

  float voltageAcross = (sourceVoltage / maxADC) * adcValue;

  return voltageAcross;
}

float Thermometer::VoltageToResistance(float voltage)
{
  //Rearranged equation of Vout = Vsource * (Rresistor / Rthermistor + Rresistor)
  // -> Rthermistor = Rresistor * (Vsource / Vmeasured - 1)

  float maxVoltage = 5.00;
  float resistorResistance = 10000.00;

  return resistorResistance * (maxVoltage / voltage - 1.00);
}

float Thermometer::ResistanceToKelvin(float resistance)
{
  /* Equation: 1/T = 1/T0 + 1/B * ln(R/R0)
     Solved for T:
     T = 1 / ((1/T0) + (1/B) * (ln(R/R0)))
  */
  float kelvin = 1.00 / ((1.00 / _thermistor->T0) + (1.00 / _thermistor->Beta) * (log(resistance / _thermistor->R0)));
  return kelvin;
}


float Thermometer::KelvinToCelsius(float kelvin)
{
  return kelvin - 273.15 + TemperatureOffset;
}

float Thermometer::ReadTemperature()
{
  float avgADC = GetAverageADC();
  
  float voltage = ADCToVoltage(avgADC);
  
  float resistance = VoltageToResistance(voltage);
  
  float kelvin = ResistanceToKelvin(resistance);
  
  float celsius = KelvinToCelsius(kelvin);

  return celsius;
}
