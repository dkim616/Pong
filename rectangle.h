#ifndef RECTANGLE_H_
#define RECTANGLE_H_

struct Rectangle {
  Rectangle(float x, float y, float width, float height)
    : x_(x),
    y_(y),
    width_(width),
    height_(height) {}

  float left() const { return x_; }
  float right() const { return x_ + width_; }
  float top() const { return y_; }
  float bottom() const { return y_ + height_; }

  float width() const { return width_; }
  float height() const { return height_; }

  bool collidesWith(const Rectangle &other) const {
    return right() >= other.left() &&
      left() <= other.right() &&
      top() <= other.bottom() &&
      bottom() >= other.top();
  }

private:
  const float x_, y_, width_, height_;
};

#endif // RECTANGLE_H_
