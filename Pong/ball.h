#ifndef BALL_H_
#define BALL_H_

#include <boost/shared_ptr.hpp>

#include "rectangle.h"

class Graphics;
class Sprite;
class Paddle;

class Ball {
public:
  Ball(Graphics& graphics, float x, float y);

  bool update(int elapsed_time);
  void draw(Graphics& graphics);

  void bounce(Paddle& paddle);
  void reset();
  
  float get_x() { return x_; }
  float get_y() { return y_; }

  Rectangle collisionRectangle() const;

private:
  void initializeSprite(Graphics& graphics);
  void setRandomVelocity();

  bool alive_;
  float x_, y_;
  float velocity_x_, velocity_y_;
  boost::shared_ptr<Sprite> sprite_;
};

#endif // BALL_H_
