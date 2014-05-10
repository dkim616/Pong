#include "paddle.h"

#include "animated_sprite.h"
#include "game.h"
#include "graphics.h"

namespace {
  const std::string kSpriteFilePath("BallPaddle");

  const int kPaddleLeftLeft = 16;
  const int kPaddleLeftTop = 0;
  const int kPaddleRightLeft = 16;
  const int kPaddleRightTop = 16 * 10;
  const int kPaddleWidth = 16;
  const int kPaddleHeight = 16 * 10;
  
  const int kAnimUpPaddleLeftLeft = 16 * 2;
  const int kAnimUpPaddleLeftTop = 0;
  const int kAnimUpPaddleRightLeft = 16 * 2;
  const int kAnimUpPaddleRightTop = 16 * 10;
  
  const int kAnimDownPaddleLeftLeft = 16 * 5;
  const int kAnimDownPaddleLeftTop = 0;
  const int kAnimDownPaddleRightLeft = 16 * 5;
  const int kAnimDownPaddleRightTop = 16 * 10;
  
  const unsigned int kAnimPaddleFps = 13;
  const unsigned int kAnimPaddleFrame = 3;

  const float kPaddleVelocity = 0.300f;
}

Paddle::Paddle(Graphics& graphics, float x, float y, bool flip_sprite)
    : x_(x),
      y_(y),
      velocity_x_(0.0f),
      velocity_y_(0.0f),
      flip_sprite_(flip_sprite),
      paddle_motion_(PaddleMotion::STANDING) {
  initializeSprite(graphics);
}

void Paddle::update(int elapsed_time) {
  y_ += velocity_y_ * elapsed_time;
  if (y_ < 0) {
    y_ = 0;
  } else if (y_ > Game::kScreenHeight - kPaddleHeight) {
    y_ = Game::kScreenHeight - (float)kPaddleHeight;
  }
  switch (paddle_motion_) {
    case PaddleMotion::UP:
      sprite_up_->update();
      break;
    case PaddleMotion::DOWN:
      sprite_down_->update();
      break;
    default:
      break;
  }
}

void Paddle::draw(Graphics& graphics) {
  switch (paddle_motion_) {
    case PaddleMotion::STANDING:
      sprite_->draw(graphics, x_, y_);
      break;
    case PaddleMotion::UP:
      sprite_up_->draw(graphics, x_, y_);
      break;
    case PaddleMotion::DOWN:
      sprite_down_->draw(graphics, x_, y_);
      break;
    default:
      sprite_->draw(graphics, x_, y_);
      break;
  }
  
  sprite_->draw(graphics, x_, y_);
}

void Paddle::moveUp() {
  velocity_y_ = -kPaddleVelocity;
  paddle_motion_ = PaddleMotion::UP;
}

void Paddle::moveDown() {
  velocity_y_ = kPaddleVelocity;
  paddle_motion_ = PaddleMotion::DOWN;
}

void Paddle::stopMoving() {
  velocity_y_ = 0.0f;
  paddle_motion_ = PaddleMotion::STANDING;
}

Rectangle Paddle::collisionRectangle() const {
  if (flip_sprite_) {
    return Rectangle(x_, y_, (float)kPaddleWidth / 4.0f, (float)kPaddleHeight);
  } else {
    return Rectangle(x_ + (3.0f * (float)kPaddleWidth / 4.0f), y_, (float)kPaddleWidth / 4.0f, (float)kPaddleHeight);
  }
}

void Paddle::initializeSprite(Graphics& graphics) {
  if (flip_sprite_) {
    sprite_ = boost::shared_ptr<Sprite>(new Sprite(graphics,
                                                   kSpriteFilePath,
                                                   kPaddleRightLeft,
                                                   kPaddleRightTop,
                                                   kPaddleWidth,
                                                   kPaddleHeight));
    sprite_up_ = boost::shared_ptr<AnimatedSprite>(new AnimatedSprite(graphics,
                                                                      kSpriteFilePath,
                                                                      kAnimUpPaddleRightLeft,
                                                                      kAnimUpPaddleRightTop,
                                                                      kPaddleWidth,
                                                                      kPaddleHeight,
                                                                      kAnimPaddleFps,
                                                                      kAnimPaddleFrame));
    sprite_down_ = boost::shared_ptr<AnimatedSprite>(new AnimatedSprite(graphics,
                                                                        kSpriteFilePath,
                                                                        kAnimDownPaddleRightLeft,
                                                                        kAnimDownPaddleRightTop,
                                                                        kPaddleWidth,
                                                                        kPaddleHeight,
                                                                        kAnimPaddleFps,
                                                                        kAnimPaddleFrame));
  } else {
    sprite_ = boost::shared_ptr<Sprite>(new Sprite(graphics,
                                                   kSpriteFilePath,
                                                   kPaddleLeftLeft,
                                                   kPaddleLeftTop,
                                                   kPaddleWidth,
                                                   kPaddleHeight));
    sprite_up_ = boost::shared_ptr<AnimatedSprite>(new AnimatedSprite(graphics,
                                                                      kSpriteFilePath,
                                                                      kAnimUpPaddleLeftLeft,
                                                                      kAnimUpPaddleLeftTop,
                                                                      kPaddleWidth,
                                                                      kPaddleHeight,
                                                                      kAnimPaddleFps,
                                                                      kAnimPaddleFrame));
    sprite_down_ = boost::shared_ptr<AnimatedSprite>(new AnimatedSprite(graphics,
                                                                        kSpriteFilePath,
                                                                        kAnimDownPaddleLeftLeft,
                                                                        kAnimDownPaddleLeftTop,
                                                                        kPaddleWidth,
                                                                        kPaddleHeight,
                                                                        kAnimPaddleFps,
                                                                        kAnimPaddleFrame));
  }
}
