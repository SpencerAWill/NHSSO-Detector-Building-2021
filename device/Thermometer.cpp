#include "Thermometer.h"
#include "Thermistor.h"
#include "Arduino.h"
#include "VoltageDivider.h"
#include "VoltageCalculator.h"

int _pin;
Thermistor *_thermistor;
VoltageCalculator *_voltageCalculator;
VoltageDivider *_voltageDivider;

unsigned int SampleAmount;
int TemperatureOffset;

Thermometer::Thermometer(Thermistor *thermistor, int voltageDividerPin)
{
  _pin = voltageDividerPin;
  _voltageCalculator = new VoltageCalculator();
  _voltageDivider = new VoltageDivider(5.0, 10000.0);
  SampleAmount = 10;
  _thermistor = thermistor;
  TemperatureOffset = 0;
}

float Thermometer::GetAverageAnalog()
{
  int cumulativeAnalog = 0;
  for (int i = 0; i < SampleAmount; i++)
  {
    cumulativeAnalog += analogRead(_pin);
  }

  return (float)cumulativeAnalog / SampleAmount;
}

float Thermometer::AnalogToVoltage(int analogValue)
{
  return _voltageCalculator->CalculateVoltage(analogValue);
}

float Thermometer::VoltageToResistance(float voltage)
{
  return _voltageDivider->CalculateVariableResistance(voltage);
}

float Thermometer::ResistanceToKelvin(float resistance)
{
  /* Steinhart-hart equation
     Equation: 1/T = 1/T0 + 1/B * ln(R/R0)
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
  float avgAnalog = GetAverageAnalog();
  
  float voltage = AnalogToVoltage(avgAnalog);
  
  float resistance = VoltageToResistance(voltage);
  
  float kelvin = ResistanceToKelvin(resistance);
  
  float celsius = KelvinToCelsius(kelvin);

  return celsius;
}
