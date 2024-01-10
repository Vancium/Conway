#include "Engine.hpp"
#include <iostream>
#include <memory>

namespace Conway {

Engine::Engine(std::string title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height) {
  Init();
}
Engine::~Engine() {}

void Engine::Run() {
  while (m_Running) {

    Display();
    std::cout << "\033[2J\033[1;1H";
  }
}

void Engine::Init() {
  m_GameBoard = std::make_unique<GameBoard>();
  m_GameBoard->Blinker();
}

void Engine::Display() {
  std::pair<int, int> gameSize(m_GameBoard->GRID_WIDTH,
                               m_GameBoard->GRID_HEIGHT);
  m_GameBoard->Update();
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
}

} // namespace Conway
