#include <ArduinoLog.h>
#include <SerialCommands.h>
#include <arduino-timer.h>



#include "Arduino.h"
#include "LED.h"
#include "TemperatureLED.h"
#include "Thermistor.h"
#include "Thermometer.h"

/*
 * Serial Command Setup
 */

//Create a 32 bytes static buffer to be used exclusive by SerialCommands object.
//The size should accomodate command token, arguments, termination sequence and string delimeter \0 char.
char serial_command_buffer_[32];

//Creates SerialCommands object attached to Serial
//working buffer = serial_command_buffer_
//command delimeter: Cr & Lf
//argument delimeter: SPACE
const char* term = "\n";
const char* delimiter = " ";
SerialCommands serial_commands_(&Serial, serial_command_buffer_, sizeof(serial_command_buffer_), term, delimiter);


//Timing
Timer<2, millis> timer;
uintptr_t constantUpdate;
uintptr_t timerExecuted;

/*
   Change the VALUES for any of the following
*/

// Create thermistor (readPin, beta, T0, R0)
Thermistor probeThermistor(3435, 298.15, 9999.00);

// Create leds (pin, lowerRange, upperRange)
TemperatureLED blueLED(2, 0, 20);
TemperatureLED greenLED(3, 20.1, 35);
TemperatureLED redLED(4, 35.1, 100);

// Thermometer
Thermometer thermometer(&probeThermistor, A0);

const unsigned int defaultTimer = 90;

/*
   Don't bother anything after this.
*/


/*
 * Commands
 */

void cmd_unrecognized_handler(SerialCommands* sender, const char* cmd)
{
  sender->GetSerial()->print("Command unrecognized: ");
  sender->GetSerial()->println(cmd);
}

void cmd_timerCommands_handler(SerialCommands* sender)
{
  char* arg = sender->Next();
  
  if (arg == NULL)
  {
    sender->GetSerial()->println("invalid parameter: [" + String(arg) + "]");
    return;
  }
  
  String argString = String(arg);

  if (argString == "start")
  {
    if (!timerExecuted)
    {
      startTimer(sender);
    }
    else
    {
      Log.warning("Cannot start timer because one is already running" CR);
    }
  }
  else if (argString == "stop")
  {
    if (timerExecuted)
    {
      stopTimer();
    }
  }
}
SerialCommand cmd_timerCommands("timer", cmd_timerCommands_handler);

void setup() {
  Serial.begin(9600);
  Log.begin(LOG_LEVEL_NOTICE, &Serial);
  serial_commands_.SetDefaultHandler(cmd_unrecognized_handler);
  serial_commands_.AddCommand(&cmd_timerCommands);
  timer.every(1000, timer_logRegularTemperature);

  Log.notice("=======< device.ino >=======" CR);
}

void loop() {
  timer.tick();
  serial_commands_.ReadSerial();
}


void startTimer(SerialCommands* sender)
{
  char* arg2 = sender->Next();
  unsigned int duration;
  if (arg2 == NULL)
  {
    duration = defaultTimer;
  }
  else
  {
    duration = atoi(arg2);
  }
  int milliseconds = duration * 1000;
  Log.notice("Timer started for %dms" CR, milliseconds);
  timerExecuted = timer.in(milliseconds, timer_finished);
}

void stopTimer()
{
  Log.notice("Timer stopped" CR);
  timer.cancel(timerExecuted);
}

bool timer_finished(void *)
{
  float temperature = thermometer.ReadTemperature();
  Log.notice("Mark: %D Celsius" CR, temperature);
  stopTimer();
  return false; //no repeat
}

bool timer_logRegularTemperature(void *)
{
  float temperature = thermometer.ReadTemperature();
  blueLED.Update(temperature);
  redLED.Update(temperature);
  greenLED.Update(temperature);
  Log.notice("%D Celsius" CR, temperature);
  return true; //repeat
}
