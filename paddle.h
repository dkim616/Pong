#ifndef PADDLE_H_
#define PADDLE_H_

#include <boost/shared_ptr.hpp>

#include "rectangle.h"

class Graphics;
class Sprite;

class Paddle {
public:
  Paddle(Graphics& graphics, float x, float y, bool flip_sprite);

  void update(int elapsed_time);
  void draw(Graphics& graphics);

  void moveUp();
  void moveDown();
  void stopMoving();

  float velocity_y() { return velocity_y_; }

  Rectangle collisionRectangle() const;

private:
  void initializeSprite(Graphics& graphics);

  float x_, y_;
  float velocity_x_, velocity_y_;
  bool flip_sprite_;
  boost::shared_ptr<Sprite> sprite_;
};

#endif // PADDLE_H_
