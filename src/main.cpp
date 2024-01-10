#include "Engine/Engine.hpp"

int main() {
  Conway::Engine Engine("Conway", 720, 720, true, true);
  Engine.Run();
}
