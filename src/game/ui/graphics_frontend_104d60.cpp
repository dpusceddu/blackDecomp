#include "include_asm.h"

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

#ifdef NON_MATCHING
// Unmatched: original state/callback lifetimes and branch scheduling.
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
int func_002052A0(void *, int);
int func_0020B988(void *, int);
int func_0020B048(void *);
int func_00109DC0(void *);
int func_001E8900(void *);
void *func_0020BC00(void *, int);
int func_0027C278(const char *);
int func_00209FF8(void *, int);
void func_00209760(void *, const char *);
int func_00102080(void *);
extern FrontendResourceCache *D_0040F4C4;
extern char D_003F26C0[], D_003F26D0[], D_003F26E0[], D_003F26F0[],
    D_003F2700[], D_003F2718[], D_003F2730[], D_003F2740[], D_003F2750[];
void func_0020E4A8(void *);
void func_0020EDB0(void *);
void func_00210C40(void *);
void func_00211BD8(void *);
void func_00212008(void *);
void func_00212230(void *);
void func_00212770(void *);
void func_00217768(void *);
void func_00213468(void *);
void func_00213758(void *);
void func_00214508(void *);
void func_00215058(void *);
void func_00216878(void *);
void func_00216AC8(void *);
}
int FrontendMenuState::Exit() {
  switch (state) {
  case 28:
    func_002052A0(D_0040F524, 0);
    func_0020B988(D_0040F544, 4);
    func_0020B048(D_0040F544);
    state = 29;
  case 29:
    if (!func_00109DC0(loader)) return 0;
      state = 30;
    case 30:
      if (!func_001E8900(*(void **)(D_0040F510 + 0xcbd8)))
        return 0;
      state = 31;
    case 31:
      currentScreen = 0;
      requestedScreen = 0;
      forced = 0;
      {
        void *page = func_0020BC00(D_0040F544, 2);
        func_00209FF8(page, func_0027C278(D_003F26C0));
        func_00209FF8(page, func_0027C278(D_003F26D0));
      }
      func_00209760((char *)D_0040F544 + 4, D_003F26E0);
      func_00209760((char *)D_0040F544 + 4, D_003F26F0);
      func_00209760((char *)D_0040F544 + 4, D_003F2700);
      func_00209760((char *)D_0040F544 + 4, D_003F2718);
      func_00209760((char *)D_0040F544 + 4, D_003F2730);
      func_00209760((char *)D_0040F544 + 4, D_003F2740);
      func_00209760((char *)D_0040F544 + 4, D_003F2750);
      func_0020E4A8((char *)this + 0xc);
      func_0020EDB0((char *)this + 0x10);
      func_00210C40((char *)this + 0x14);
      func_00211BD8((char *)this + 0x18);
      func_00212008((char *)this + 0x1c);
      func_00212230((char *)this + 0x20);
      func_00212770((char *)this + 0x24);
      func_00217768((char *)this + 0x28);
      func_00213468((char *)this + 0x2c);
      func_00213758((char *)this + 0x30);
      func_00214508((char *)this + 0x34);
      func_00215058((char *)this + 0x38);
      func_00216878((char *)this + 0x3c);
      func_00216AC8((char *)this + 0x40);
      initialized = 0;
      func_00102080(archive);
      archive = 0;
      D_0040F4C4->Release(5, 0);
      state = 55;
    case 55:
    default:
      return 1;
  }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00104E10);
#endif

#ifdef NON_MATCHING
// Unmatched: func_00104E10: exit switch control flow and callback return types.
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
int func_002052A0(void *, int);
int func_0020B988(void *, int);
int func_0020B048(void *);
int func_00109DC0(void *);
int func_001E8900(void *);
void *func_0020BC00(void *, int);
int func_0027C278(const char *);
int func_00209FF8(void *, int);
void func_00209760(void *, const char *);
int func_00102080(void *);
extern FrontendResourceCache *D_0040F4C4;
extern char D_003F26C0[], D_003F26D0[], D_003F26E0[], D_003F26F0[],
    D_003F2700[], D_003F2718[], D_003F2730[], D_003F2740[], D_003F2750[];
void func_0020E4A8(void *);
void func_0020EDB0(void *);
void func_00210C40(void *);
void func_00211BD8(void *);
void func_00212008(void *);
void func_00212230(void *);
void func_00212770(void *);
void func_00217768(void *);
void func_00213468(void *);
void func_00213758(void *);
void func_00214508(void *);
void func_00215058(void *);
void func_00216878(void *);
void func_00216AC8(void *);
}
int FrontendMenuState::Exit() {
  switch (state) {
  case 28:
    func_002052A0(D_0040F524, 0);
    func_0020B988(D_0040F544, 4);
    func_0020B048(D_0040F544);
    state = 29;
  case 29:
    if (func_00109DC0(loader)) {
      state = 30;
    case 30:
      if (!func_001E8900(*(void **)(D_0040F510 + 0xcbd8)))
        goto blocked;
      state = 31;
    case 31:
      currentScreen = 0;
      requestedScreen = 0;
      forced = 0;
      {
        void *page = func_0020BC00(D_0040F544, 2);
        func_00209FF8(page, func_0027C278(D_003F26C0));
        func_00209FF8(page, func_0027C278(D_003F26D0));
      }
      func_00209760((char *)D_0040F544 + 4, D_003F26E0);
      func_00209760((char *)D_0040F544 + 4, D_003F26F0);
      func_00209760((char *)D_0040F544 + 4, D_003F2700);
      func_00209760((char *)D_0040F544 + 4, D_003F2718);
      func_00209760((char *)D_0040F544 + 4, D_003F2730);
      func_00209760((char *)D_0040F544 + 4, D_003F2740);
      func_00209760((char *)D_0040F544 + 4, D_003F2750);
      func_0020E4A8((char *)this + 0xc);
      func_0020EDB0((char *)this + 0x10);
      func_00210C40((char *)this + 0x14);
      func_00211BD8((char *)this + 0x18);
      func_00212008((char *)this + 0x1c);
      func_00212230((char *)this + 0x20);
      func_00212770((char *)this + 0x24);
      func_00217768((char *)this + 0x28);
      func_00213468((char *)this + 0x2c);
      func_00213758((char *)this + 0x30);
      func_00214508((char *)this + 0x34);
      func_00215058((char *)this + 0x38);
      func_00216878((char *)this + 0x3c);
      func_00216AC8((char *)this + 0x40);
      initialized = 0;
      func_00102080(archive);
      archive = 0;
      D_0040F4C4->Release(5, 0);
      state = 55;
    case 55:
    default:
      return 1;
    }
  blocked:
    return 0;
  }
}
#endif
