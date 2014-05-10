#include "timer.h"

std::set<Timer*> Timer::timers_;

Timer::Timer(unsigned int expiration_time, bool start_active)
    : current_time_(start_active ? 0 : expiration_time),
      expiration_time_(expiration_time) {
        timers_.insert(this);
}

void Timer::updateAll(unsigned int elapsed_time) {
  for (std::set<Timer*>::iterator iter = timers_.begin(); iter != timers_.end(); ++iter) {
    (*iter)->update(elapsed_time);
  }
}

void Timer::update(unsigned int elapsed_time) {
  if (active()) {
    current_time_ += elapsed_time;
  }
}
