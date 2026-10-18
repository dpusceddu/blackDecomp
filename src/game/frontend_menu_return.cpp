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
extern void *D_0040EADC;
void func_00103DB0(int);
}
extern "C" void func_00103990(int unused) {
  D_0040EADC = D_0040F0E0 + 0x20f78;
  D_0040EAE0 = 1;
  func_00216AF0(func_00103DB0);
  func_0020E118(D_0040F0E0 + 0x20260, 1);
  FrontendScreenManager *screen = D_0040F544;
  func_0035CBC0(screen->requestedName, D_003F2698);
  if (!screen->alternate)
    screen->primaryPending = 1;
  else
    screen->alternatePending = 1;
}
