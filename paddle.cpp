#include "paddle.h"

#include "game.h"
#include "graphics.h"
#include "sprite.h"

namespace {
  const std::string kSpriteFilePath("BallPaddle");
  
  const int kPaddleLeft = 32;
  const int kPaddleTop = 0;
  const int kPaddleWidth = 16;
  const int kPaddleHeight = 32 * 5;

  const float kPaddleVelocity = 0.300f;
}

Paddle::Paddle(Graphics& graphics, float x, float y)
    : x_(x),
      y_(y),
      velocity_x_(0.0f),
      velocity_y_(0.0f) {
  initializeSprite(graphics);
}

void Paddle::update(int elapsed_time) {
  y_ += velocity_y_ * elapsed_time;
  if (y_ < 0) {
    y_ = 0;
  } else if (y_ > Game::kScreenHeight - kPaddleHeight) {
    y_ = Game::kScreenHeight - (float)kPaddleHeight;
  }
}

void Paddle::draw(Graphics& graphics) {
  sprite_->draw(graphics, x_, y_);
}

void Paddle::moveUp() {
  velocity_y_ = -kPaddleVelocity;
}

void Paddle::moveDown() {
  velocity_y_ = kPaddleVelocity;
}

void Paddle::stopMoving() {
  velocity_y_ = 0.0f;
}

Rectangle Paddle::collisionRectangle() const {
  return Rectangle(x_, y_, (float)kPaddleWidth, (float)kPaddleHeight);
}

void Paddle::initializeSprite(Graphics& graphics) {
  sprite_ = boost::shared_ptr<Sprite>(new Sprite(
      graphics,
      kSpriteFilePath,
      kPaddleLeft,
      kPaddleTop,
      kPaddleWidth,
      kPaddleHeight));
}
