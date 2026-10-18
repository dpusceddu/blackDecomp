#include "game/frontend_resources.hpp"
extern "C" int func_001094C0(void *, const char *, int, int);
int FrontendMenuState::Load(const char *name, int kind, int force) {
  return func_001094C0(loader, name, kind, force != 0);
}
