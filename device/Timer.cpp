#include "Arduino.h"
#include "Timer.h"

unsigned int _threshold;
unsigned int _counter;
bool _paused;
void (*_timerFinishedCallback)(Timer);

Timer::Timer(unsigned int seconds)
{
  _threshold = seconds;
  Reset();
}

Timer::Timer(unsigned int seconds, void (*timerFinishedCallback)(Timer))
{
  _threshold = seconds;
  SetTimerFinishedCallback(timerFinishedCallback);
  Reset();
}

bool Timer::IsPaused()
{
  return _paused;
}

void Timer::Pause()
{
  if (!IsPaused())
  {
    _paused = true;
  }
}

void Timer::Resume()
{
  if (IsPaused())
  {
    _paused = false;
  }
}

void Timer::Reset()
{
  _counter = 0;
  Pause();
}

void Timer::Restart()
{
  Reset();
  Resume();
}

bool Timer::TimerFinished()
{
  return _counter >= _threshold;
}

unsigned int Timer::GetElapsed()
{
  return _threshold;
}

void Timer::Increment(unsigned int seconds)
{
  if (!(TimerFinished() || !IsPaused()))
  {
    _counter += seconds;
    if (TimerFinished())
    {
      _timerFinishedCallback(this);
    }
  }

}

void Timer::Increment()
{
  Increment(1);
}


void Timer::SetTimerFinishedCallback(void (*timerFinishedCallback)(Timer))
{
  if (timerFinishedCallback)
  {
    _timerFinishedCallback = timerFinishedCallback;
  }
}
