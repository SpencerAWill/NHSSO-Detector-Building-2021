#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer {
  private:
    unsigned int _threshold;
    unsigned int _counter;
    bool _paused;
    void (*_timerFinishedCallback)(Timer);
    void emptyCallback();
  public:
    bool IsPaused();
    unsigned int GetElapsed();
    Timer(unsigned int seconds);
    Timer(unsigned int seconds, void (*timerFinishedCallback)(Timer));
    void Pause();
    void Resume();
    void Reset();
    void Restart();
    void SetTimerFinishedCallback(void (*timerFinishedCallback)(Timer));
    bool TimerFinished();
    void Increment(unsigned int seconds);
    void Increment();
};

#endif
