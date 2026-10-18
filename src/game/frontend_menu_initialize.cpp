#include "game/frontend_resources.hpp"
extern "C" {
void func_00109640(void *);
void func_00109FB0(void *);
void func_0020CCF8(void *, void *);
extern void *D_0040F544;
}
void FrontendMenuState::Initialize() {
  archive = 0;
  mode = 0;
  initialized = 0;
  func_00109640(loader);
  func_00109FB0(message);
  func_0020CCF8(D_0040F544, loader);
  musicStarted = 0;
  state = 1;
}
