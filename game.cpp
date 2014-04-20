#include "game.h"

#include <SDL.h>
#include <stdio.h>

#include "input.h"
#include "graphics.h"
#include "map.h"

namespace {
  const int kFps = 60;
}

int Game::kScreenWidth = 852;
int Game::kScreenHeight = 480;

Game::Game() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("SDL_Init Error: \n%s\n", SDL_GetError());
  }

  loop();
}

Game::~Game() {
  SDL_Quit();
}

void Game::loop() {
  Input input;
  Graphics graphics;

  SDL_Event event;

  map_.reset(Map::createMap(graphics));

  bool running = true;
  int last_update_time = SDL_GetTicks();

  while (running) {
    const int start_time_ms = SDL_GetTicks();

    input.reset();

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          input.keyDownEvent(event);
          break;
        case SDL_KEYUP:
          input.keyUpEvent(event);
          break;
        default:
          break;
      }
    }

    if (input.wasKeyPressed(SDLK_ESCAPE)) running = false;

    const int current_time_ms = SDL_GetTicks();
    const int elapsed_time = current_time_ms - last_update_time;

    update(elapsed_time);

    last_update_time = current_time_ms;

    draw(graphics);

    const int ms_per_frame = 1000 / kFps;
    const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;

    if (elapsed_time_ms < ms_per_frame) {
      SDL_Delay(ms_per_frame - elapsed_time_ms);
    }
  }
}

void Game::update(int elapsed_time) {

}

void Game::draw(Graphics& graphics) {
  graphics.clear();

  map_->drawBackground(graphics);

  graphics.flip();
}
