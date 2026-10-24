#include "include_asm.h"

#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern FrontendScreenManager *D_0040F544;
extern unsigned char D_0040EAE0;
extern char D_003F2698[];
char *func_0035CBC0(char *, const char *);
void func_00216AF0(void (*)(int));
void func_0020E118(void *, int);
}
extern "C" {
void func_00103DF0(int);
int func_00109FF8(void *);
}

extern "C" int func_00103F50(int check) {
  unsigned char result;
  if (!check || (result = D_0040EAE0) != 0) {
    func_00216AF0(func_00103DF0);
    ((FrontendMenuState *)(D_0040F0E0 + 0x20220))->Request(21, 0);
    func_00109FF8(D_0040F0E0 + 0x20438);
    FrontendScreenManager *screen = D_0040F544;
    func_0035CBC0(screen->requestedName, D_003F2698);
    result = 1;
    if (!screen->alternate)
      screen->primaryPending = 1;
    else
      screen->alternatePending = 1;
  }
  return result;
}
