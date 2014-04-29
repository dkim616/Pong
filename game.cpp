#include "game.h"

#include <SDL.h>
#include <stdio.h>

#include "ball.h"
#include "graphics.h"
#include "input.h"
#include "map.h"
#include "paddle.h"

namespace {
  const int kFps = 120;
}

int Game::kScreenWidth = 852;
int Game::kScreenHeight = 480;

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  srand(SDL_GetTicks());

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
  paddle_one_.reset(new Paddle(graphics, 100, 150));
  paddle_two_.reset(new Paddle(graphics, (float)(kScreenWidth - 100), 150));
  ball_.reset(new Ball(graphics, 320, 320));

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

    if (input.isKeyHeld(SDLK_w) && input.isKeyHeld(SDLK_s)) {
      paddle_one_->stopMoving();
    } else if (input.isKeyHeld(SDLK_w)) {
      paddle_one_->moveUp();
    } else if (input.isKeyHeld(SDLK_s)) {
      paddle_one_->moveDown();
    } else {
      paddle_one_->stopMoving();
    }

    if (input.isKeyHeld(SDLK_UP) && input.isKeyHeld(SDLK_DOWN)) {
      paddle_two_->stopMoving();
    } else if (input.isKeyHeld(SDLK_UP)) {
      paddle_two_->moveUp();
    } else if (input.isKeyHeld(SDLK_DOWN)) {
      paddle_two_->moveDown();
    } else {
      paddle_two_->stopMoving();
    }

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
  paddle_one_->update(elapsed_time);
  paddle_two_->update(elapsed_time);
  ball_->update(elapsed_time);
  if (ball_->collisionRectangle().collidesWith(paddle_one_->collisionRectangle())) {
    ball_->bounce(*paddle_one_);
  }
  if (ball_->collisionRectangle().collidesWith(paddle_two_->collisionRectangle())) {
    ball_->bounce(*paddle_two_);
  }
}

void Game::draw(Graphics& graphics) {
  graphics.clear();

  map_->drawBackground(graphics);
  paddle_one_->draw(graphics);
  paddle_two_->draw(graphics);
  ball_->draw(graphics);

  graphics.flip();
}
