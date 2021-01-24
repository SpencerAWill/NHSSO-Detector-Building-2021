#include "Arduino.h"
#include "LED.h"
#include "TemperatureLED.h"
#include "Thermistor.h"
#include "Timer.h"
#include "Button.h"
#include "SerialReader.h"
#include "Logger.h"

/*
   Change the VALUES for any of the following
*/

// Create thermistor (readPin, beta, T0, R0)
Thermistor probeThermistor(A0, 3435, 298.15, 9999.00);

// Create leds (pin, lowerRange, upperRange)
TemperatureLED blueLED(2, 0, 20);
TemperatureLED greenLED(3, 20.1, 35);
TemperatureLED redLED(4, 35.1, 100);

// Temperature Sampling
int numSamples = 10;
int samplingTime = 1000;

// Other
float tempCorrection = 0;

// Other other
Timer timer(90);
SerialReader serialReader;
Button startTimerButton(5);
Button resetTimerButton(7);
LED resetLED(6);
bool AlreadyTriggered = false;

/*
   Don't bother anything after this.
*/

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Read Pin
  //Create thermistor (readPin, beta, T0, R0)
  Thermistor probeThermistor(A0, 3435, 298.15, 9999.00);

  float adcValue = GetAverageADC(probeThermistor, numSamples, (int)(samplingTime / numSamples));
  float celcius = GetTemp(probeThermistor, adcValue) + tempCorrection;

  String command = serialReader.GetCommand();
  if (timer.Enabled) {
    timer.Increment();

    if (timer.CounterAboveThreshold()) {
      resetLED.TurnOn();

      if (!AlreadyTriggered) {
        LogMessage("Timer Triggered!");
        PrintNewLine();
        LogMessage("--> ");
        AlreadyTriggered = true;
      }
    }
    else {
      resetLED.TurnOff();
    }

    LogMessage("Timer: ");
    LogMessage(timer.GetProgress());
    PrintDivider();
  }

  if (startTimerButton.ReadStatus() == HIGH && timer.Enabled == false) {
    timer.Enabled = true;
  }

  if (resetTimerButton.ReadStatus() == HIGH || command == "reset") {
    timer.Reset();
    AlreadyTriggered = false;
  }

  if (command == "disable" && timer.Enabled) {
    timer.Enabled = false;
  }

  if (command == "enable" && !timer.Enabled) {
    timer.Enabled = true;
  }

  if (command == "toggle") {
    timer.Enabled = !timer.Enabled;
  }

  //Logs values
  LogCelcius(celcius);
  PrintDivider();
  LogVoltage(adcValue);
  PrintNewLine();

  //Determines whether or not they should be on or off
  ToggleLEDs(redLED, greenLED, blueLED, celcius);
}






/*
   CALCULATIONS
*/

float GetTemp(Thermistor thermistor, float adcValue) {
  float volts = ConvertADCtoVoltage(adcValue);
  float resistance = ConvertVoltagetoResistance(volts);


  /* Equation: 1/T = 1/T0 + 1/B * ln(R/R0)
     Solved for T:
     T = 1 / ((1/T0) + (1/B) * (ln(R/R0)))
  */
  float kelvin = 1.00 / ((1.00 / thermistor.T0) + (1.00 / thermistor.Beta) * (log(resistance / thermistor.R0)));
  float celcius = kelvin - 273.15;
  return celcius;
}

float ConvertADCtoVoltage(float adc) {
  float sourceVoltage = 5.00;
  int maxADC = 1023;

  float voltageAcross = (sourceVoltage / maxADC) * adc;

  return voltageAcross;
}

float ConvertVoltagetoResistance(float voltage) {
  //Rearranged equation of Vout = Vsource * (Rresistor / Rthermistor + Rresistor)
  // -> Rthermistor = Rresistor * (Vsource / Vmeasured - 1)

  float maxVoltage = 5.00;
  float measuredVoltage = voltage;

  float resistorResistance = 10000.00;

  float measuredResistance = resistorResistance * (maxVoltage / measuredVoltage - 1.00);
  return measuredResistance;
}






/*
   SAMPLING
*/
float GetAverageADC(Thermistor thermistor, int numSamples, int delayMS) {
  int cumulativeADC = 0;

  for (int i = 0; i < numSamples; i++) {
    delay(delayMS);
    cumulativeADC += thermistor.GetADC();
  }

  return cumulativeADC / numSamples;
}







/*
   OTHER LED STUFF
*/
void ToggleLEDs(TemperatureLED red, TemperatureLED green, TemperatureLED blue, float temp) {
  if (red.WithinRange(temp)) {
    red.TurnOn();
  } else red.TurnOff();

  if (green.WithinRange(temp)) {
    green.TurnOn();
  } else green.TurnOff();

  if (blue.WithinRange(temp)) {
    blue.TurnOn();
  } else blue.TurnOff();
}





/*
   LOGGING
*/

void LogMessage(String message) {
  Serial.print(message);
}
void LogMessage(int message) {
  Serial.print(message);
}
void LogMessage(float message) {
  Serial.print(message);
}

void LogCelcius(float temp) {
  LogMessage("Celcius: ");
  LogMessage(temp);
}

void LogVoltage(int adc) {
  float voltage = ConvertADCtoVoltage(adc);

  LogMessage("Voltage: ");
  LogMessage(voltage);
}

void PrintDivider() {
  Serial.print("   ||   ");
}

void PrintNewLine() {
  Serial.println();
}
