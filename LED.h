#ifndef LED_h
#define LED_h

#include "Arduino.h"


class LED {
  private:
    bool On;
  public:
    int Pin;
    void TurnOn();
    void TurnOff();
    bool IsOn();
    LED(int pin);
};

#endif
