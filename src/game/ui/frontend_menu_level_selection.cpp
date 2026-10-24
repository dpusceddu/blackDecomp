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
extern char D_0048EF88[];
void func_0035D1A0(char *, const char *, int);
int func_0035E750(const char *);
int func_00103FF0(int);
}

extern "C" void func_00103D08(const char *selection) {
  D_0040EAE0 = 0;
  func_0035D1A0(D_0048EF88, selection + 60, 30);
  func_00216AF0((void (*)(int))func_00103FF0);
  ((FrontendMenuState *)(D_0040F0E0 + 0x20220))
      ->Request(func_0035E750(selection), 0);
  FrontendScreenManager *screen = D_0040F544;
  func_0035CBC0(screen->requestedName, D_003F2698);
  if (!screen->alternate)
    screen->primaryPending = 1;
  else
    screen->alternatePending = 1;
}
