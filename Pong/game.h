#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>

class Ball;
class Graphics;
class Map;
class Paddle;
class Score;

class Game {
public:
  explicit Game();
  ~Game();

  static int kScreenWidth;
  static int kScreenHeight;

private:
  void loop();
  void reset();
  void update(int elapsed_time);
  void draw(Graphics& graphics);
  
  bool game_reset_;
  bool player_one_win_;
  bool player_two_win_;

  boost::scoped_ptr<Map> map_;
  boost::scoped_ptr<Ball> ball_;
  boost::scoped_ptr<Paddle> paddle_one_;
  boost::scoped_ptr<Paddle> paddle_two_;
  boost::scoped_ptr<Score> score_one_;
  boost::scoped_ptr<Score> score_two_;
};

#endif // GAME_H_
