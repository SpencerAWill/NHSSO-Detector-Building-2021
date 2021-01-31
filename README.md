# NHSSO-Detector-Building-2021
Code for the 2021 NHS Science Olympiad Detector Building Device

---

# Installation
Instructions for downloading the Detector Building Source Code

## GitHub
1. Click on the green "Code" dropdown.
2. Download ZIP file
3. Extract file and open device/device.ino in Arduino IDE

## CLI
1. Clone source code using the command `git clone https://github.com/SpencerAWill/NHSSO-Detector-Building-2021.git` in your chosen CLI
2. Open device/device.ino in Arduino IDE

---

# Configuration


## Adjust thermistor values (only modify if the thermistor changes)
Set the values of the 'Thermistor' object:
`Thermistor probeThermistor(beta, T0, R0)`
Example:
`Thermistor probeThermistor(3435, 298.15, 9999.00);`

## Adjust temperature LEDs
Set the ranges of all 3 temperature LEDs to the competition ranges:
`TemperatureLED led(pin, lowerLimit, upperLimit)`
Example:
```
TemperatureLED blueLED(2, 0, 20); //LED on pin 2 that activates on temperatures 0-20
TemperatureLED greenLED(3, 20.1, 35);
TemperatureLED redLED(4, 35.1, 100);
```

## Adjust thermometer pin
Only change `voltageDividerPin` to the pin where the variable voltage is being read.
This pin must be able to read analog signals.
`Thermometer thermometer(&probeThermistor, voltageDividerPin)`
Example:
`Thermometer thermometer(&probeThermistor, A0);`

## Default Timer
You can change the default timer seconds by setting the value of `defaultTimer` to any positive integer number of seconds.

---

# Usage
Click the 'Verify' and 'Upload' button to upload the code to the connected Arduino
Temperature values (in celsius) are logged in the Serial Monitor

## Commands
- "timer start"
  - Starts a timer for `defaultTimer` seconds
- "timer start n"
  - Starts a timer for n seconds
- "timer stop"
  - Stops any timer that may be running