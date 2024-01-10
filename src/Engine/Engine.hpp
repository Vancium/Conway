#pragma once
#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>
#include <string>

namespace Conway {

class Engine {
public:
  Engine(std::string title, int width, int height);
  ~Engine();
  void Run();

private:
  void Init();
  void HandleEvents();
  SDL_Window *m_Window;
  std::string m_Title;
  int m_Width;
  int m_Height;
  bool m_Running = true;
};
} // namespace Conway
