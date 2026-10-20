#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F4C0 __attribute__((section(".bss")));
void *func_0035C6EC(void *, int, int);
void func_002A9108(int, void *, int);
void func_001C4FB0(void *, int);
// Supply small-data TU context; the retained strong definition owns storage.
unsigned char D_0040D986 __attribute__((weak))=0;
void func_0020B170(void *);
extern void *D_0040F544 __attribute__((section(".bss")));
void func_0010A820(void *);
void func_00205210(void *);
extern void *D_0040F524 __attribute__((section(".bss")));
int func_001C50E0(void *);
}
int FrontendMenuState::PrepareExit() {
  char *io = D_0040F4C0 + 0xd360;
  int mode;
  func_0035C6EC(&mode, 0, 4);
  func_002A9108(*(int *)(io + 0x58), &mode, 3);
  func_001C4FB0(D_0040F4C0, 0);
  if (D_0040D986) {
    func_0020B170(D_0040F544);
    func_0010A820(this->message);
  } else
    func_00205210(D_0040F524);
  return func_001C50E0(D_0040F4C0);
}
