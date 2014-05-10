#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Sprite {
public:
  explicit Sprite(Graphics& graphics, 
         const std::string& file_path,
         int source_x, 
         int source_y,
         int width, 
         int height);

  virtual void update(int /*elapsed_time*/) {}
  void draw(Graphics& graphics, float x, float y);

protected:
  SDL_Rect source_rect_;

private:
  SDL_Surface* sprite_sheet_;
};

#endif // SPRITE_H_
