#include "Engine.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_log.h"
#include <cstdio>
#include <stdexcept>

namespace Conway {

Engine::Engine(std::string title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height) {
  Init();
}
Engine::~Engine() {}

void Engine::Run() {
  while (m_Running) {
    HandleEvents();
  }
}

void Engine::HandleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYDOWN: {
      m_Running = false;
    }
    default:
      break;
    }
  }
}

void Engine::Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    throw ::std::runtime_error("Failed to initialize SDL");
  }
}

} // namespace Conway
