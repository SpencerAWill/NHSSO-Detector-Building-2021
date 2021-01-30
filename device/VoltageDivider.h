#ifndef VoltageDivider_h
#define VoltageDivider_h

class VoltageDivider
{
  private:
    float _sourceVoltage;
    float _knownResistance;
  public:
    VoltageDivider(float sourceVoltage, float knownResistance);
    float CalculateVariableResistance(float voltageBetween);
};

#endif
