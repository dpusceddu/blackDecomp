#include "include_asm.h"

#include "game/frontend_resources.hpp"
extern "C" {
extern unsigned char D_0040EAE0;
extern FrontendScreenManager *D_0040F544;
extern char D_0048EF88[];
char *func_0035CBC0(char *, const char *);
}

extern "C" int func_00103FF0(int conditional) {
  unsigned char result;
  if (!conditional || (result = D_0040EAE0) != 0) {
    FrontendScreenManager *screen = D_0040F544;
    func_0035CBC0(screen->requestedName, D_0048EF88);
    result = 1;
    if (!screen->alternate)
      screen->primaryPending = 1;
    else
      screen->alternatePending = 1;
  }
  return result;
}
