#include "Engine.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_video.h"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace Conway {

Engine::Engine(std::string title, int width, int height, bool useSDL,
               bool darkMode)
    : m_Title(title), m_Width(width), m_Height(height), m_UseSDL(useSDL) {
  Init();
}
Engine::~Engine() {}

void Engine::Run() {
  while (m_Running) {

    Display();
  }
}

void Engine::Init() {
  m_GameBoard = std::make_unique<GameBoard>();
  m_GameBoard->Blinker();
  // TODO ask for user input for specific conway pattern, random distrubtion of
  // cells, or create custom board
  if (m_UseSDL) {
    InitSDL();
  }
  SetTheme();
}

void Engine::InitSDL() {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    throw std::runtime_error("Could not initialize SDL2");
  }

  m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, m_Width, m_Height,
                              SDL_WINDOW_SHOWN);

  m_Renderer = SDL_CreateRenderer(
      m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Engine::DisplayTerminal() {
  std::pair<int, int> gameSize(m_GameBoard->GRID_WIDTH,
                               m_GameBoard->GRID_HEIGHT);
  for (int y = 0; y < gameSize.first; y++) {
    for (int x = 0; x < gameSize.second; x++) {
      if (m_GameBoard->GetCellStatus({x, y}) == CellState::DEAD) {
        printf(".");
      } else {
        printf("X");
      }
    }
    printf("\n");
  }
  std::cout << "\033[2J\033[1;1H";
}

void Engine::DisplaySDL() {
  SDL_RenderClear(m_Renderer);

  // Draw Game Board
  for (int y = 0; y < m_GameBoard->GRID_HEIGHT; y++) {
    for (int x = 0; x < m_GameBoard->GRID_WIDTH; x++) {
      if (m_GameBoard->GetCellStatus({x, y}) == CellState::ALIVE) {
        SDL_SetRenderDrawColor(m_Renderer, m_Theme.alive.r, m_Theme.alive.g,
                               m_Theme.alive.b, m_Theme.alive.a);
      } else {
        SDL_SetRenderDrawColor(m_Renderer, m_Theme.dead.r, m_Theme.dead.g,

                               m_Theme.dead.b, m_Theme.dead.a);
      }
      DrawCell(x, y);
      DrawLines();
    }
  }
  SDL_RenderPresent(m_Renderer);
}

void Engine::DrawCell(int x, int y) {
  int cellSizeX = m_Width / m_GameBoard->GRID_WIDTH;
  int cellSizeY = m_Height / m_GameBoard->GRID_HEIGHT;

  SDL_Rect cell;
  cell.h = cellSizeY;
  cell.w = cellSizeX;
  cell.x = cellSizeY * x;
  cell.y = cellSizeX * y;
  SDL_RenderFillRect(m_Renderer, &cell);
}

void Engine::DrawLines() {
  int cellSizeX = m_Width / m_GameBoard->GRID_WIDTH;
  int cellSizeY = m_Height / m_GameBoard->GRID_HEIGHT;
  SDL_SetRenderDrawColor(m_Renderer, m_Theme.line.r, m_Theme.line.g,
                         m_Theme.line.b, m_Theme.line.a);
  for (int y = 0; y < m_Height; y++) {
    if (y != 0) {
      SDL_RenderDrawLine(m_Renderer, 0, cellSizeY * y, m_Width, cellSizeY * y);
    }
  }

  for (int x = 0; x < m_Height; x++) {
    if (x != 0) {
      SDL_RenderDrawLine(m_Renderer, cellSizeX * x, 0, cellSizeX * x, m_Height);
    }
  }
}

void Engine::Display() {
  // TODO call terminalDIsplay or SDL Display, for terminal use ncruses
  // https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/intro.html

  if (!m_UseSDL) {
    DisplayTerminal();
  } else {
    Uint32 timeout = SDL_GetTicks() + 100;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
      HandleEvents();
      DisplaySDL();
    }
  }
  m_GameBoard->Update();
}

void Engine::HandleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT: {
      m_Running = false;
      break;
    }
    case SDL_KEYDOWN: {
      m_Running = false;
      break;
    }
    default: {
      break;
    }
    }
  }
}

void Engine::SetTheme() {
  if (m_DarkMode) {
    m_Theme = {
        .background = {22, 22, 22, 255},
        .line = {44, 44, 44, 255},
        .alive = {255, 255, 255, 255},
        .dead = {22, 22, 22, 255},
    };
  }
}

} // namespace Conway
