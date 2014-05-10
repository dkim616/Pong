#include "graphics.h"

#include <SDL2/SDL.h>

#include "game.h"

namespace {
  //const int kBitsPerPixel = 32;

  enum FlipDirection {
    VERTICAL = 1,
    HORIZONTAL = 2,
  };
}

Graphics::Graphics() {
  window_ = SDL_CreateWindow("Prototype",
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             Game::kScreenWidth, Game::kScreenHeight,
                             0);
  if (window_ == NULL) {
    printf("SDL_CreateWindow error: \n%s\n", SDL_GetError());
  } else {
    screen_ = SDL_GetWindowSurface(window_);
    if (screen_ == NULL) {
      printf("SDL_GetWindowSurface error: \n%s\n", SDL_GetError());
    }
  }
}

Graphics::~Graphics() {
  for (SpriteMap::iterator iter = sprite_sheets_.begin(); iter != sprite_sheets_.end(); ++iter) {
    SDL_FreeSurface(iter->second);
  }

  SDL_FreeSurface(screen_);
  SDL_DestroyWindow(window_);
}

Graphics::SurfaceID Graphics::loadImage(const std::string& file_path, bool transparent) {
  const std::string file_path_fixed("content/" + file_path + ".bmp");
  if (sprite_sheets_.count(file_path_fixed) == 0) {
    sprite_sheets_[file_path_fixed] = SDL_LoadBMP(file_path_fixed.c_str());

    if (transparent) {
      const Uint32 cyan_color = SDL_MapRGB(
        sprite_sheets_[file_path_fixed]->format, 0, 255, 255);
      SDL_SetColorKey(sprite_sheets_[file_path_fixed], SDL_TRUE, cyan_color);
    }
  }

  return sprite_sheets_[file_path_fixed];
}

void Graphics::blitSurface(SurfaceID source,
                           SDL_Rect* source_rectangle,
                           SDL_Rect* destination_rectangle) {
  SDL_BlitSurface(source, source_rectangle, screen_, destination_rectangle);
}

void Graphics::clear() {
  SDL_FillRect(screen_, NULL, 0);
}

void Graphics::flip() {
  SDL_UpdateWindowSurface(window_);
}

