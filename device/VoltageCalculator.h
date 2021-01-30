#ifndef VoltageCalculator_h
#define VoltageCalculator_h

//Converts analog values into working, usable voltages
class VoltageCalculator
{
  private:
    float _operatingVoltage;
    int _resolution;
    float CalculateFinalResolution(int bits);
  public:
    VoltageCalculator();
    VoltageCalculator(float operatingVoltage);
    float GetOperatingVoltage();
    int GetResolution();
    float CalculateVoltage(int analogValue);
};

#endif
