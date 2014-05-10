#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite(Graphics& graphics,
                               const std::string &file_name,
                               int source_x, int source_y,
                               int width, int height,
                               unsigned int fps, unsigned int num_frames)
    : Sprite(graphics, file_name, source_x, source_y, width, height),
      frame_timer_(1000 / fps),
      num_frames_(num_frames),
      current_frame_(0),
      num_completed_loops_(0) {}

void AnimatedSprite::update() {
  if (frame_timer_.expired()) {
    ++current_frame_;
    frame_timer_.reset();
    
    if (current_frame_ < num_frames_) {
      source_rect_.x += source_rect_.w;
    } else {
      source_rect_.x -= source_rect_.w * (num_frames_ - 1);
      current_frame_ = 0;
      ++num_completed_loops_;
    }
  }
}

