// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "timer.h"

Timer::Timer() {
  last_time_ = std::chrono::steady_clock::now();
}

Timer::~Timer() { }

float
Timer::get_delta_time() {
  Timer::DeltaTime delta = std::chrono::steady_clock::now() -
     last_time_;
  last_time_ = std::chrono::steady_clock::now();

  return  std::chrono::duration_cast<std::chrono::duration<float>>(delta).count();
}
