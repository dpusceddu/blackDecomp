#include "include_asm.h"

#include "game/frontend_resources.hpp"
struct MenuMovie {
  const char *format;
  int kind;
  unsigned char music;
  char pad[3];
};
extern "C" {
extern char *D_0040F0E0;
extern FrontendScreenManager *D_0040F544;
extern void *D_0040F4E8;
extern char D_0048EFA8[];
extern char D_0048EF88[];
extern MenuMovie D_003BC3C8[];
extern signed char D_0040EAD8;
extern char D_0040D990[], D_0040D998[];
extern int D_003BC50C;
extern unsigned char D_0040D986, D_0040EAE0;
extern int D_0040EAE4;
extern char *D_0040F510;
extern void *D_0040F524;
char *func_0035CBC0(char *, const char *);
int func_0035D728(char *, const char *, ...);
const char *func_00108A20();
void func_0010A848(void *);
int func_00123BD0(void *, int, int);
signed char func_001228E0(void *, int);
void func_001050A8(FrontendMenuState *, const char *);
}
extern "C" {
extern int *D_0040F53C;
extern char D_003F2540[], D_003F28D0[];
}

extern "C" void func_001050A8(FrontendMenuState *menu, const char *name) {
  menu->pending = 0;
  menu->elapsed = 0;
  if (name) {
    FrontendScreenManager *screen = D_0040F544;
    func_0035CBC0(screen->requestedName, name);
    if (!screen->alternate)
      screen->primaryPending = 1;
    else
      screen->alternatePending = 1;
    return;
  }
  int title = 0;
  if (*D_0040F53C) {
    if (!func_00123BD0(D_0048EFA8, 1, 0) && !func_00123BD0(D_0048EFA8, 1, 1) &&
        !func_00123BD0(D_0048EFA8, 1, 2))
      title = func_00123BD0(D_0048EFA8, 1, 3) == 0;
  } else
    title = 1;
  if (title == 1) {
    D_0040F0E0[0x2020c] = func_001228E0(D_0040F4E8, 0);
    D_0040F0E0[0x2020d] = 1;
    D_0040F0E0[0x2020e] = 1;
    FrontendScreenManager *screen = D_0040F544;
    func_0035CBC0(screen->requestedName, "blacktitlemenu2");
    if (!screen->alternate)
      screen->primaryPending = 1;
    else
      screen->alternatePending = 1;
  } else {
    FrontendScreenManager *screen = D_0040F544;
    func_0035CBC0(screen->requestedName, D_003F2540);
    if (!screen->alternate)
      screen->primaryPending = 1;
    else
      screen->alternatePending = 1;
  }
}
