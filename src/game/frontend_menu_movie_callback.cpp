#include "game/frontend_resources.hpp"
struct ControllerStatus {
  char prefix[8];
  unsigned char active;
};
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
int func_0010A848(void *);
int func_00123BD0(void *, int, int);
signed char func_001228E0(void *, int);
void func_001050A8(FrontendMenuState *, const char *);
}
static inline bool ControllerActive(ControllerStatus *status) {
  return status->active != 0;
}
extern "C" void func_00103DF0(int forced) {
  char name[16];
  if (!ControllerActive((ControllerStatus *)(D_0040F0E0 + 0x20438)) &&
      !forced) {
    if (++D_003BC50C > 26)
      D_003BC50C = 23;
    if (D_0040EAD8)
      func_0035D728(name, D_003BC3C8[D_003BC50C].format, D_0040D990,
                    func_00108A20());
    else
      func_0035D728(name, D_003BC3C8[D_003BC50C].format, D_0040D998,
                    func_00108A20());
    ((FrontendMenuState *)(D_0040F0E0 + 0x20220))->Load(name, 0, 0);
  } else {
    func_0010A848(D_0040F0E0 + 0x20438);
    FrontendScreenManager *screen = D_0040F544;
    func_0035CBC0(screen->requestedName, D_0048EF88);
    if (!screen->alternate)
      screen->primaryPending = 1;
    else
      screen->alternatePending = 1;
  }
}
