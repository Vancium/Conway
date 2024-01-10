#include "GameBoard.hpp"
#include <cstdio>
#include <cstdlib>
#include <vector>

namespace Conway {
GameBoard::GameBoard() {
  int gridSize = GRID_WIDTH * GRID_HEIGHT;
  std::vector<CellState> temp(gridSize, CellState::DEAD);
  m_BoardState = temp;
  srand(time(NULL));
}
GameBoard::~GameBoard() {}

void GameBoard::Update() {

  std::vector<CellState> temp(m_BoardState);

  for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      int count = CountLivingNeighbors({x, y});

      if (m_BoardState[GetCellIndex({x, y})] == CellState::ALIVE) {
        if (count < 2 || count > 3) {
          temp[GetCellIndex({x, y})] = CellState::DEAD;
        }
      } else {
        if (count == 3) {
          temp[GetCellIndex({x, y})] = CellState::ALIVE;
        }
      }
    }
  }
  m_BoardState = temp;
}

void GameBoard::Blinker() {
  m_BoardState[2 + GRID_HEIGHT * 3] = CellState::ALIVE;
  m_BoardState[3 + GRID_HEIGHT * 3] = CellState::ALIVE;
  m_BoardState[4 + GRID_HEIGHT * 3] = CellState::ALIVE;
}

void GameBoard::Glider() {

  m_BoardState[2 + GRID_HEIGHT * 3] = CellState::ALIVE;
  m_BoardState[3 + GRID_HEIGHT * 3] = CellState::ALIVE;
  m_BoardState[4 + GRID_HEIGHT * 3] = CellState::ALIVE;
  m_BoardState[4 + GRID_HEIGHT * 2] = CellState::ALIVE;
  m_BoardState[3 + GRID_HEIGHT * 1] = CellState::ALIVE;
}

void GameBoard::RandomizeGrid() {
  for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      int randomVal = rand() & 1;
      if (randomVal) {
        m_BoardState[GetCellIndex({x, y})] = CellState::ALIVE;
      } else {
        m_BoardState[GetCellIndex({x, y})] = CellState::DEAD;
      }
    }
  }
}

void GameBoard::Clear() {}

CellState GameBoard::GetCellStatus(std::pair<int, int> cords) {
  int idx = cords.first + GRID_HEIGHT * cords.second;
  return m_BoardState[idx];
}

int GameBoard::CountLivingNeighbors(std::pair<int, int> cords) {
  int idx = GetCellIndex(cords);
  int count = 0;

  // Loop around cell;
  for (int y = -1; y < 2; ++y) {
    for (int x = -1; x < 2; ++x) {
      int localX = cords.first + x;
      int localY = cords.second + y;

      // Check if off the board or at current cell location
      if (localX == -1 || localY == -1 || localX == GRID_WIDTH ||
          localY == GRID_HEIGHT || (x == 0 && y == 0)) {
        continue;
      }
      if (m_BoardState[GetCellIndex({localX, localY})] == CellState::ALIVE) {
        count++;
      }
    }
  }
  return count;
}

int GameBoard::GetCellIndex(std::pair<int, int> cords) {
  return cords.first + GRID_HEIGHT * cords.second;
}

} // namespace Conway
