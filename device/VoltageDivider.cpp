#include "VoltageDivider.h"

float _sourceVoltage;
float _knownResistance;

VoltageDivider::VoltageDivider(float sourceVoltage, float knownResistance)
{
  _sourceVoltage = sourceVoltage;
  _knownResistance = knownResistance;
}

float VoltageDivider::CalculateVariableResistance(float voltageBetween)
{
  //using equation Vout = Vin * (R2 / (R1 + R2))
  //rearrange to solve for R2: R2 = R1 * ((Vin/Vout) - 1)
  return _knownResistance * ((_sourceVoltage / voltageBetween) - 1);
}
