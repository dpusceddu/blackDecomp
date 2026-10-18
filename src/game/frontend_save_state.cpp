#include "game/frontend_resources.hpp"
extern "C" int func_0010BC00() { return 1; }
extern "C" void func_0010BC08() {}

extern "C" int func_0010B5B0(FrontendSaveState *);
void FrontendSaveState::Finish() {
  complete = 1;
  func_0010B5B0(this);
}

extern "C" int func_0010B160(FrontendSaveState *);
int FrontendSaveState::Begin(int next) {
  func_0010B160(this);
  operation = next;
  return 1;
}

int FrontendSaveState::Ready() { return operation == 31; }
