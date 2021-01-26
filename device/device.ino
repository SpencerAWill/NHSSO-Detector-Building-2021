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
const char* term = "\r\n";
const char* delimiter = " ";
SerialCommands serial_commands_(&Serial, serial_command_buffer_, sizeof(serial_command_buffer_), term, delimiter);


//Timing
Timer<4, millis> timer;
uintptr_t constantUpdate;
uintptr_t timerExecuted;

/*
   Change the VALUES for any of the following
*/

// Create thermistor (readPin, beta, T0, R0)
Thermistor probeThermistor(A0, 3435, 298.15, 9999.00);

// Create leds (pin, lowerRange, upperRange)
TemperatureLED blueLED(2, 0, 20);
TemperatureLED greenLED(3, 20.1, 35);
TemperatureLED redLED(4, 35.1, 100);

// Thermometer
Thermometer thermometer(&probeThermistor);

//Other
LED resetLED(6);
const unsigned int defaultTimer = 10;

/*
   Don't bother anything after this.
*/


/*
 * Commands
 */

void cmd_unrecognized_handler(SerialCommands* sender, const char* cmd)
{
  auto serial = sender->GetSerial();
  
  serial->print("Command unrecognized: ");
  serial->print(cmd);
}

void cmd_timerCommands_handler(SerialCommands* sender)
{
  auto serial = sender->GetSerial();
  char* arg1 = sender->Next();

  if (arg1 == NULL)
  {
    serial->println("Unrecognized argument: " + String(arg1));
    return;
  }

  if (arg1 == "start")
  {
    startTimer(sender);
  }
  else if (arg1 == "cancel")
  {
      cancelTimer(sender);
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
  int t = defaultTimer;
  int milliseconds = t * 1000;
  sender->GetSerial()->println("Timer started for " + String(t) + "ms");
  //timerExecuted = timer.in(t * 1000, timer_logTimedTemperature);
}

void cancelTimer(SerialCommands* sender)
{
  sender->GetSerial()->println("Timer canceled");
  //timer.cancel(timerExecuted);
}

bool timer_finished(void *)
{
  float temperature = thermometer.ReadTemperature();
  Serial.println(temperature);
  return false; //no repeat
}

bool timer_logRegularTemperature(void *)
{
  float temperature = thermometer.ReadTemperature();
  blueLED.Update(temperature);
  redLED.Update(temperature);
  greenLED.Update(temperature);
  Serial.println(temperature);
  return true; //repeat
}
