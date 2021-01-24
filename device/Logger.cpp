#include "Arduino.h"
#include "Logger.h"


Verbosity LogLevel;

void Logger::Log(String message)
{
  Log(message, Verbosity::Normal);
}

void Logger::Log(String message, Verbosity verbosity)
{
  if (verbosity > LogLevel) {
    Serial.print(message);
  }
}

Logger::Logger(Verbosity verbosity)
{
  LogLevel = verbosity;
}
