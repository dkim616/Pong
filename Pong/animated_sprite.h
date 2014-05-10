#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_

#include "sprite.h"
#include "timer.h"

class AnimatedSprite : public Sprite {
public:
  AnimatedSprite(Graphics& graphics,
                 const std::string& file_name,
                 int source_x, int source_y,
                 int width, int height,
                 unsigned int fps, unsigned int num_frames);
  
  void update();
  
  int num_completed_loops() const { return num_completed_loops_; }
  
private:
  Timer frame_timer_;
  const unsigned int num_frames_;
  unsigned int current_frame_;
  int num_completed_loops_;
};

#endif // ANIMATED_SPRITE_H_
