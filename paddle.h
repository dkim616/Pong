#ifndef PADDLE_H_
#define PADDLE_H_

#include <boost/shared_ptr.hpp>

#include "rectangle.h"

class Graphics;
class Sprite;

class Paddle {
public:
  Paddle(Graphics& graphics, float x, float y);

  void update(int elapsed_time);
  void draw(Graphics& graphics);

  void moveUp();
  void moveDown();
  void stopMoving();

  Rectangle collisionRectangle() const;

private:
  void initializeSprite(Graphics& graphics);

  float x_, y_;
  float velocity_x_, velocity_y_;
  boost::shared_ptr<Sprite> sprite_;
};

#endif // PADDLE_H_
