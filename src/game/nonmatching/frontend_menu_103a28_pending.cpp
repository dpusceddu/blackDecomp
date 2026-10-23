// Unmatched: func_00103A28: title-mode branch layout and call scheduling.
#ifdef NONMATCHING
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
extern void *D_0040F4E8;
extern char D_0048EF88[];
int func_001227C0(void *);
void func_0035D1A0(char *, const char *, int);
int func_00103F50(int);
int func_0020B678(void *, const char *, int);
}
extern "C" int func_00103A28(const char *name) {
  if ((unsigned char)D_0040F0E0[0x2020c] == 8 &&
      func_001227C0(D_0040F4E8) == 2) {
    D_0040EAE0 = 0;
    func_0035D1A0(D_0048EF88, name, 30);
    func_00216AF0((void (*)(int))func_00103F50);
    func_0020E118(D_0040F0E0 + 0x20260, 0);
    return func_0020B678(D_0040F544, D_003F2698, 4);
  }
  FrontendScreenManager *screen = D_0040F544;
  func_0035CBC0(screen->requestedName, name);
  if (!screen->alternate)
    screen->primaryPending = 1;
  else
    screen->alternatePending = 1;
  return 1;
}

#endif
