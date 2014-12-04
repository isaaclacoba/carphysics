#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer {
public:
  typedef std::chrono::steady_clock::duration DeltaTime;
  typedef std::chrono::steady_clock::time_point Time;

  Timer();
  virtual ~Timer();
  float get_delta_time();

private:
  Time last_time_;
};

#endif
