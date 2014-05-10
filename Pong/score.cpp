#include "score.h"

#include "game.h"
#include "graphics.h"
#include "sprite.h"

namespace {
  const std::string kScoreSpriteFilePath("Score");
  
  const int kScoreEmptyLeft = 0;
  const int kScoreEmptyTop = 0;
  const int kScoreEmptyWidth = 20;
  const int kScoreEmptyHeight = 20;
  
  const int kScoreFullLeft = 50;
  const int kScoreFullTop = 0;
  const int kScoreFullWidth = 20;
  const int kScoreFullHeight = 20;
  
  const float kScoreSpace = 10;
  const int kMaxScoreSize = 3;
}

Score::Score(Graphics& graphics, bool player_one)
    : score_(0), player_one_(player_one) {
  initialize_sprites_(graphics);
}

void Score::draw(Graphics& graphics) {
  int space_counter = 0;
  for (std::vector<boost::shared_ptr<Sprite> >::iterator iter = score_sprites_.begin();
       iter != score_sprites_.end();
       ++iter) {
    space_counter++;
    if (player_one_) {
      (*iter)->draw(graphics,
                 kScoreSpace * space_counter + kScoreEmptyWidth * (space_counter - 1),
                 kScoreSpace);
    } else {
      (*iter)->draw(graphics,
                 Game::kScreenWidth - kScoreSpace * space_counter - kScoreEmptyWidth * space_counter,
                 kScoreSpace);
    }
  }
  space_counter = 0;
}

void Score::addScore() {
  if (score_ < kMaxScoreSize) {
    score_++;
    for (int i = 0; i < score_; ++i) {
      score_sprites_.pop_back();
    }
    for (int i = 0; i < score_; ++i) {
      score_sprites_.push_back(score_full_);
    }
  }
}

int Score::getScore() {
  return score_;
}

void Score::initialize_sprites_(Graphics& graphics) {
  score_empty_ = boost::shared_ptr<Sprite>(new Sprite(graphics,
                                                      kScoreSpriteFilePath,
                                                      kScoreEmptyLeft,
                                                      kScoreEmptyTop,
                                                      kScoreEmptyWidth,
                                                      kScoreEmptyHeight));
  score_full_ = boost::shared_ptr<Sprite>(new Sprite(graphics,
                                                     kScoreSpriteFilePath,
                                                     kScoreFullLeft,
                                                     kScoreFullTop,
                                                     kScoreFullWidth,
                                                     kScoreFullHeight));
  for (int i = 0; i < kMaxScoreSize; ++i) {
    score_sprites_.push_back(score_empty_);
  }
}
