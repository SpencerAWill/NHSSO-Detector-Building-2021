#include "VoltageCalculator.h"
#include "Arduino.h"

float _operatingVoltage;
int _resolution;

VoltageCalculator::VoltageCalculator()
{
  _operatingVoltage = 5.0;
  _resolution = 10;
}

VoltageCalculator::VoltageCalculator(float operatingVoltage)
{
  _operatingVoltage = operatingVoltage;
  _resolution = 10;
}

float VoltageCalculator::GetOperatingVoltage()
{
  return _operatingVoltage;
}

float VoltageCalculator::CalculateVoltage(int analogValue)
{
  // voltage = sensor value * (operating voltage / resolution);
  //    eg. voltage = sensor value * (5.0 V / 1023 bits)
  int resolution = GetResolution();
  int finalResolution = CalculateFinalResolution(resolution);
  
  return analogValue * (_operatingVoltage / (float)finalResolution);
}

int VoltageCalculator::GetResolution()
{
  return _resolution;
}

float VoltageCalculator::CalculateFinalResolution(int bits)
{
  return pow(2, bits) - 1;
}
