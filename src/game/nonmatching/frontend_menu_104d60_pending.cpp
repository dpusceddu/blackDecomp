// Unmatched: func_00104D60: small-data access selection for the initialized
// flag.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F4C0;
void *func_0035C6EC(void *, int, int);
void func_002A9108(int, void *, int);
void func_001C4FB0(void *, int);
extern unsigned char D_0040D986;
void func_0020B170(void *);
extern void *D_0040F544;
void func_0010A820(void *);
void func_00205210(void *);
extern void *D_0040F524;
int func_001C50E0(void *);
}
extern "C" int func_00104D60(FrontendMenuState *menu) {
  char *io = D_0040F4C0 + 0xd360;
  int mode;
  func_0035C6EC(&mode, 0, 4);
  func_002A9108(*(int *)(io + 0x58), &mode, 3);
  func_001C4FB0(D_0040F4C0, 0);
  if (D_0040D986) {
    func_0020B170(D_0040F544);
    func_0010A820(menu->message);
  } else
    func_00205210(D_0040F524);
  return func_001C50E0(D_0040F4C0);
}

#endif
