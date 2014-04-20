#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>

class Graphics;
class Map;

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
};

#endif // GAME_H_
