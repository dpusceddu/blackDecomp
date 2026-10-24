#include "include_asm.h"

#include "game/frontend_resources.hpp"

void FrontendMenuState::Request(int screen, int force) {
  requestedScreen = screen;
  forced = force != 0;
}
