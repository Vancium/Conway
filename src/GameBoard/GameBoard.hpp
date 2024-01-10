#pragma once

#include <vector>
namespace Conway {

enum class CellState {
  ALIVE,
  DEAD,
};

class GameBoard {
public:
  GameBoard();
  ~GameBoard();
  void Update();
  static constexpr int GRID_WIDTH = 80;
  static constexpr int GRID_HEIGHT = 80;
  CellState GetCellStatus(std::pair<int, int> cords);

  void Clear();

  void Glider();
  void Blinker();

  void RandomizeGrid();

private:
  int GetCellIndex(std::pair<int, int> cords);
  int CountLivingNeighbors(std::pair<int, int> cords);
  void UpdateCell(std::pair<int, int> cords);
  std::vector<CellState> m_BoardState;
};
} // namespace Conway
