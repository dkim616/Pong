#ifndef SCORE_H_
#define SCORE_H_

#include <boost/shared_ptr.hpp>
#include <vector>

class Graphics;
class Sprite;

class Score {
public:
  Score(Graphics& graphics, bool player_one);
  
  void draw(Graphics& graphics);
  void addScore();
  int getScore();
  
private:
  void initialize_sprites_(Graphics& graphics);
  
  int score_;
  bool player_one_;
  std::vector<boost::shared_ptr<Sprite> > score_sprites_;
  boost::shared_ptr<Sprite> score_empty_;
  boost::shared_ptr<Sprite> score_full_;
};

#endif // SCORE_H_
