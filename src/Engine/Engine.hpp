#pragma once
#include "../GameBoard/GameBoard.hpp"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>

/*
 *  Top level structure, controls, windowing, events, rendering
 *
 *
 * */

namespace Conway {

struct Theme {
  SDL_Color background;
  SDL_Color line;
  SDL_Color alive;
  SDL_Color dead;
};

class Engine {
public:
  Engine(std::string title, int width, int height, bool useSDL, bool darkMode);
  ~Engine();
  void Run();

private:
  void HandleEvents();
  void DisplayTerminal();
  void Display();
  void DisplaySDL();
  void DrawLines();
  void DrawCell(int x, int y);
  void Init();
  void InitSDL();
  void SetTheme();

private:
  std::string m_Title;
  int m_Width;
  int m_Height;
  bool m_Running = true;
  std::unique_ptr<GameBoard> m_GameBoard;
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
  bool m_UseSDL = false;
  bool m_DarkMode = true;
  Theme m_Theme;
};
} // namespace Conway
