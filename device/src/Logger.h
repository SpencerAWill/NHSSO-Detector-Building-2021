#ifndef Logger_h
#define Logger_h

enum class Verbosity
{
  Quiet,
  Minimal,
  Normal,
  Detailed,
  Diagnostic
};

class Logger
{
  public:
    Verbosity LogLevel;
    void Log(String message);
    void Log(String message, Verbosity verbosity);
    Logger(Verbosity verbosity);
};

#endif
