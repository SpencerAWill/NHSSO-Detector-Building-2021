#include "Arduino.h"
#include "LED.h"

int Pin;
bool On;

void LED::TurnOn() {
  On = true;
  digitalWrite(Pin, HIGH);
}

void LED::TurnOff() {
  On = false;
  digitalWrite(Pin, LOW);
}

bool LED::IsOn() {
  return On;
}

LED::LED(int pin) {
  Pin = pin;
  On = false;
  pinMode(Pin, OUTPUT);
}
