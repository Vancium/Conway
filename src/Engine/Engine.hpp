#pragma once
#include "../GameBoard/GameBoard.hpp"
#include <memory>
#include <string>

/*
 *  Top level structure, controls, windowing, events, rendering
 *
 *
 * */

namespace Conway {

class Engine {
public:
  Engine(std::string title, int width, int height);
  ~Engine();
  void Run();

private:
  void Display();
  void Init();
  std::string m_Title;
  int m_Width;
  int m_Height;
  bool m_Running = true;
  std::unique_ptr<GameBoard> m_GameBoard;
};
} // namespace Conway
