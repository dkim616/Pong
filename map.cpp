#include "map.h"

#include "game.h"
#include "sprite.h"
#include "graphics.h"
#include <string>

Map* Map::createMap(Graphics& graphics) {
  Map* map = new Map();
  const std::string file_name = map->getRandomBackground();
  boost::shared_ptr<Sprite> background_(new Sprite(graphics,
                                                   file_name,
                                                   0,
                                                   0,
                                                   Game::kScreenWidth,
                                                   Game::kScreenHeight));
  map->background_ = background_;

  return map;
}

std::string Map::getRandomBackground() {
  srand(SDL_GetTicks());

  int file_number = rand() % 12 + 1;
  const std::string number = std::to_string(file_number);

  const std::string file_name("background/background" + number);

  return file_name;
}

void Map::update(int elapsed_time) {}

void Map::drawBackground(Graphics& graphics) const {
  background_->draw(graphics, 0, 0);
}

void Map::draw(Graphics& graphics) const {}
