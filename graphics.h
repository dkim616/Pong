#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

struct SDL_Window;
struct SDL_Surface;
struct SDL_Rect;

class Graphics {
public:
  typedef SDL_Surface* SurfaceID;

  explicit Graphics();
  ~Graphics();

  SurfaceID loadImage(const std::string& file_path,
                      bool transparent = false);

  void blitSurface(
      SurfaceID source,
      SDL_Rect* source_rectangle,
      SDL_Rect* destination_rectangle);
  void clear();
  void flip();

private:
  typedef std::map<std::string, SDL_Surface*> SpriteMap;
  SpriteMap sprite_sheets_;

  SDL_Window* window_;
  SDL_Surface* screen_;
};

#endif // GRAPHICS_H_
