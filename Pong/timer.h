#ifndef PONG_H_
#define PONG_H_

#include <boost/noncopyable.hpp>
#include <set>

class Timer : private boost::noncopyable {
public:
  Timer(unsigned int expiration_time, bool start_active = false);
  ~Timer() { timers_.erase(this); }
  
  void reset() { current_time_ = 0; }
  bool active() const { return current_time_ < expiration_time_;}
  bool expired() const { return !active(); }
  unsigned int current_time() const { return current_time_; }
  
  static void updateAll(unsigned int elapsed_time);
  
private:
  void update(unsigned int elapsed_time);
  
  unsigned int current_time_;
  const unsigned int expiration_time_;
  
  static std::set<Timer*> timers_;
};

#endif // PONG_H_
