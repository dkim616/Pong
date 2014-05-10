#ifndef MAP_H_
#define MAP_H_

#include <boost/shared_ptr.hpp>

class Graphics;
class Sprite;

class Map {
public:
  static Map* createMap(Graphics& graphics);
  std::string getRandomBackground();

  void update(int elapsed_time);
  void drawBackground(Graphics& graphics) const;
  void draw(Graphics& graphics) const;

private:
  boost::shared_ptr<Sprite> background_;
};

#endif // MAP_H_
