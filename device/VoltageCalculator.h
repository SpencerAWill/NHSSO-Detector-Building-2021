#ifndef VoltageCalculator_h
#define VoltageCalculator_h

//Converts analog values into working, usable voltages
class VoltageCalculator
{
  private:
    unsigned long _operatingVoltage;
    int _resolution;
    float CalculateFinalResolution(int bits);
  public:
    VoltageCalculator();
    VoltageCalculator(unsigned long operatingVoltage);
    unsigned long GetOperatingVoltage();
    int GetResolution();
    float CalculateVoltage(int analogValue);
};

#endif
