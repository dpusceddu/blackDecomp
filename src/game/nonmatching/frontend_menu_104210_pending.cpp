// Unmatched: func_00104210: menu entry callback types and fallthrough state
// scheduling.
#ifdef NONMATCHING
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
void func_00205170(void *);
void func_00107880(void *);
extern void *D_0040F0E8;
extern FrontendResourceCache *D_0040F4C4;
void func_00104108();
void func_001080A0(void *, void (*)(), void *);
int func_00109760(void *, void *, void *);
int func_0020AB20(void *);
void *func_0020BC00(void *, int);
int func_0027C278(const char *);
void func_00209EC8(void *, int, int *);
void func_00209618(void *, const char *, void (*)());
int func_001E87A0(void *, int);
void func_002052A0(void *, int);
int func_0020E620(void *);
void func_00215788(int);
int func_00103A28(const char *);
extern const char *D_003BC3A8[];
extern const char *D_003BC3B4;
extern const char *D_003BC3C0;
void func_001AEBB0(void *, float);
extern void *D_0040F4C0;
extern float D_004432E0;
void func_0020E200(void *);
void func_0020EAC8(void *);
void func_002109E0(void *);
void func_00211AC0(void *);
void func_00211F80(void *);
void func_00212190(void *);
void func_00212528(void *);
void func_00217670(void *);
void func_002133C0(void *);
void func_002134F8(void *);
void func_00214408(void *);
void func_00214CF8(void *);
void func_002162C8(void *);
void func_00216A98(void *);
void func_00103990();
void func_00103BF8();
void func_00103C28();
void func_00103B38();
void func_00104078();
void func_00103D08();
void func_00103930();
extern char D_003F26C0[];
extern char D_003F26D0[];
extern char D_003F26E0[];
extern char D_003F26F0[];
extern char D_003F2700[];
extern char D_003F2718[];
extern char D_003F2730[];
extern char D_003F2740[];
extern char D_003F2750[];
extern char D_003F2760[];
}
static inline bool FadeActive(float value) { return value > 0; }
int FrontendMenuState::Enter() {
  switch (state) {
  case 1:
  case 55:
    pending = 0;
    func_00205170(D_0040F524);
    state = 2;
  case 2: {
    char *screen = (char *)D_0040F544;
    if (!FadeActive(*(float *)(screen + 0x3948))) {
      screen[0x394c] = 1;
      *(float *)(screen + 0x3948) = 1;
    }
    func_00107880(D_0040F0E8);
    archive = D_0040F4C4->Acquire(5, 0);
    if (!archive)
      func_001080A0(D_0040F4C4, func_00104108, 0);
    else
      D_0040F4C4->Release(5, 0);
    state = 3;
  }
  case 3:
    archive = D_0040F4C4->Acquire(5, 0);
    if (!archive)
      return 0;
    state = 4;
  case 4:
    if (!func_00109760(loader, archive, (char *)archive + 0x128))
      return 0;
    state = 5;
  case 5:
    if (!func_0020AB20(D_0040F544))
      return 0;
    ((char *)D_0040F544)[0x390f] = 1;
    if (!initialized) {
      D_0040D986 = 1;
      void *page = func_0020BC00(D_0040F544, 2);
      currentScreen = 0;
      requestedScreen = 0;
      forced = 0;
      func_00209EC8(page, func_0027C278(D_003F26C0), &requestedScreen);
      func_00209EC8(page, func_0027C278(D_003F26D0), &forced);
      func_00209618((char *)D_0040F544 + 4, D_003F26E0, func_00103990);
      func_00209618((char *)D_0040F544 + 4, D_003F26F0, func_00103BF8);
      func_00209618((char *)D_0040F544 + 4, D_003F2700, func_00103C28);
      func_00209618((char *)D_0040F544 + 4, D_003F2718, func_00103B38);
      func_00209618((char *)D_0040F544 + 4, D_003F2730, func_00104078);
      func_00209618((char *)D_0040F544 + 4, D_003F2740, func_00103D08);
      func_00209618((char *)D_0040F544 + 4, D_003F2750, func_00103930);
      func_0020E200((char *)this + 0xc);
      func_0020EAC8((char *)this + 0x10);
      func_002109E0((char *)this + 0x14);
      func_00211AC0((char *)this + 0x18);
      func_00211F80((char *)this + 0x1c);
      func_00212190((char *)this + 0x20);
      func_00212528((char *)this + 0x24);
      func_00217670((char *)this + 0x28);
      func_002133C0((char *)this + 0x2c);
      func_002134F8((char *)this + 0x30);
      func_00214408((char *)this + 0x34);
      func_00214CF8((char *)this + 0x38);
      func_002162C8((char *)this + 0x3c);
      func_00216A98((char *)this + 0x40);
      initialized = 1;
    }
    state = 6;
  case 6:
    if (!func_001E87A0(*(void **)(D_0040F510 + 0xcbd8), 1))
      return 0;
    {
      char *screen = (char *)D_0040F544;
      *(float *)(screen + 0x3948) = 1;
      screen[0x394c] = 0;
    }
    state = 7;
  case 7: {
    char *screen = (char *)D_0040F544;
    if (FadeActive(*(float *)(screen + 0x3948)))
      return 0;
    screen[0x394c] = 1;
    *(float *)(screen + 0x3948) = 1;
  }
    if (!D_0040D986)
      func_002052A0(D_0040F524, 1);
    else if (mode == 0) {
      if (func_0020E620((char *)this + 0xc))
        func_001050A8(this, D_003BC3C0);
      else if (mode == 0)
        func_00215788(0);
      else
        goto mode_changed;
    } else {
    mode_changed:
      if (mode == 3) {
        if (*(int *)(D_0040F0E0 + 0x2014c) == 0)
          func_00103A28(D_003F2760);
        else
          func_00103A28(D_003BC3B4);
      } else
        func_001050A8(this, D_003BC3A8[mode]);
    }
    elapsed = 0;
    state = 28;
  case 28:
    func_001AEBB0(D_0040F4C0, D_004432E0);
    return 1;
  default:
    return 0;
  }
}

#endif
