#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>

class Ball;
class Graphics;
class Map;
class Paddle;

class Game {
public:
  explicit Game();
  ~Game();

  static int kScreenWidth;
  static int kScreenHeight;

private:
  void loop();
  void update(int elapsed_time);
  void draw(Graphics& graphics);

  boost::scoped_ptr<Map> map_;
  boost::scoped_ptr<Ball> ball_;
  boost::scoped_ptr<Paddle> paddle_one_;
  boost::scoped_ptr<Paddle> paddle_two_;
};

#endif // GAME_H_
