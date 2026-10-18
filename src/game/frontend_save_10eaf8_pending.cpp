// Unmatched: func_0010EAF8: helper return-register liveness and branch
// scheduling.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
extern "C" {
int func_0010B8E8(FrontendSaveState *);
void func_0010B160(FrontendSaveState *);
}
int FrontendSaveState::Wait() {
  if (timer > 0 && !waiting && (events & 0xffffffff0000UL)) {
    int current = operation;
    if (current < 31)
      return 0;
    if (current > 31)
      return 0;
    if (func_0010B8E8(this) != 1)
      return 0;
    operation = 32;
    return 0;
  }
  int current = operation;
  if (current < 31)
    return 0;
  if (current < 32)
    func_0010B160(this);
  return 1;
}

#endif
