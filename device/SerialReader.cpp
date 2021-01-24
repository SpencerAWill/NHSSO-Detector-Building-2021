#include "Arduino.h"
#include "SerialReader.h"

SerialReader::SerialReader() {}

String SerialReader::GetCommand() {
  if (Serial.available()) {
    return Serial.readStringUntil('\n');
  }
  else {
    return "";
  }
}
