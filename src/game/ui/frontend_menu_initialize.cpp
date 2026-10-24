#include "include_asm.h"

#include "game/frontend_resources.hpp"
extern "C" {
void func_00109640(void *);
void func_00109FB0(void *);
void func_0020CCF8(void *, void *);
extern void *D_0040F544;
}

void FrontendMenuState::Initialize() {
  archive = 0;
  mode = 0;
  initialized = 0;
  func_00109640(loader);
  func_00109FB0(message);
  func_0020CCF8(D_0040F544, loader);
  musicStarted = 0;
  state = 1;
}

#ifdef NON_MATCHING
// Unmatched: native state/callback lifetimes and branch scheduling.
#include "game/frontend_resources.hpp"
struct MenuMovie {
  const char *format;
  int kind;
  unsigned char music;
  char pad[3];
};
extern "C" {
extern char *D_0040F0E0 __attribute__((section(".bss")));
extern FrontendScreenManager *D_0040F544 __attribute__((section(".bss")));
extern void *D_0040F4E8 __attribute__((section(".bss")));
extern char D_0048EFA8[];
extern char D_0048EF88[];
extern MenuMovie D_003BC3C8[];
extern signed char D_0040EAD8;
extern char D_0040D990[], D_0040D998[];
extern int D_003BC50C;
unsigned char D_0040D986 __attribute__((weak))=0; extern unsigned char D_0040EAE0;
extern int D_0040EAE4;
extern char *D_0040F510 __attribute__((section(".bss")));
extern void *D_0040F524 __attribute__((section(".bss")));
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
extern void *D_0040F0E8 __attribute__((section(".bss")));
extern FrontendResourceCache *D_0040F4C4 __attribute__((section(".bss")));
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
extern const char *D_003BC3B4 __attribute__((section(".bss")));
extern const char *D_003BC3C0 __attribute__((section(".bss")));
void func_001AEBB0(void *, float);
extern void *D_0040F4C0 __attribute__((section(".bss")));
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00104210);
#endif

#ifdef NON_MATCHING
// Unmatched: func_00104210: menu entry callback types and fallthrough state
// scheduling.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00104210);
#endif

#ifdef NON_MATCHING
// Unmatched: native state/callback lifetimes and branch scheduling.
#include "game/frontend_resources.hpp"
struct MenuMovie {
  const char *format;
  int kind;
  unsigned char music;
  char pad[3];
};
extern "C" {
extern char *D_0040F0E0 __attribute__((section(".bss")));
extern FrontendScreenManager *D_0040F544 __attribute__((section(".bss")));
extern void *D_0040F4E8 __attribute__((section(".bss")));
extern char D_0048EFA8[];
extern char D_0048EF88[];
extern MenuMovie D_003BC3C8[];
extern signed char D_0040EAD8;
extern char D_0040D990[], D_0040D998[];
extern int D_003BC50C;
unsigned char D_0040D986 __attribute__((weak))=0; extern unsigned char D_0040EAE0;
extern int D_0040EAE4;
extern char *D_0040F510 __attribute__((section(".bss")));
extern void *D_0040F524 __attribute__((section(".bss")));
char *func_0035CBC0(char *, const char *);
int func_0035D728(char *, const char *, ...);
const char *func_00108A20();
void func_0010A848(void *);
int func_00123BD0(void *, int, int);
signed char func_001228E0(void *, int);
void func_001050A8(FrontendMenuState *, const char *);
}
extern "C" {
void func_0020E338(void *);
void func_00109550(void *);
int *func_00123C90(void *, int, int);
int func_0012D158(void *, int, int);
extern void *D_0040F4D0 __attribute__((section(".bss")));
int func_00109F68(void *, int);
void func_001D8BC0(float, void *, int, int, int);
void func_001D8DF0(void *);
void func_001D8DE8(void *);
unsigned char func_0026BC30(void *, int);
int func_0035CFD8(const char *, const char *, int);
void func_0035D1A0(char *, const char *, int);
void func_00103F50(int);
void func_00109918(void *);
void func_0021A480(const char *, int, void *, int);
void func_0010A268(void *);
void func_00205180(void *);
void func_00105268(FrontendMenuState *);
int func_00124D20();
int func_0020B950(void *);
void func_00209A58(void *);
const char *func_0020B980(void *);
int func_0035CCD8(const char *);
void func_00216AF0(void (*)());
void func_00104050();
void func_0020B8C0(void *);
void func_001E8980(void *);
extern char D_003F2540[], D_003F2850[], D_003F2698[];
}
static inline void *MusicChannel() {
  return *(void **)(*(char **)(D_0040F510 + 0xcbd8) + 0x34);
}
void FrontendMenuState::Update() {
  char name[16];
  if (D_0040D986) {
    func_0020E338((char *)this + 0xc);
    int next = requestedScreen;
    if (currentScreen != next) {
      if (next == 0) {
        func_00109550(loader);
      } else {
        if (next == 2) {
          int mission = *(int *)(D_0040F0E0 + 0x2014c);
          if (*func_00123C90(D_0048EFA8, 7, mission) < 1) {
            if (func_00123BD0(D_0048EFA8, 7, mission) ||
                func_00123BD0(D_0048EFA8, 6, mission))
              next = 26;
            else if (func_00123BD0(D_0048EFA8, 5, mission) ||
                     func_00123BD0(D_0048EFA8, 4, mission))
              next = 25;
            else if (func_00123BD0(D_0048EFA8, 3, mission) ||
                     func_00123BD0(D_0048EFA8, 2, mission))
              next = 24;
            else
              next = 23;
          } else
            next = func_0012D158(D_0040F4D0, 0, 3) + 23;
        }
        if (!D_0040EAD8)
          func_0035D728(name, D_003BC3C8[next].format, D_0040D998,
                        func_00108A20());
        else
          func_0035D728(name, D_003BC3C8[next].format, D_0040D990,
                        func_00108A20());
        if (name[0] == 'F' && D_0040EAE4 != 4)
          Load((const char *)((unsigned)name | 1), D_003BC3C8[next].kind,
               forced != 0);
        else if (!musicStarted || !func_00109F68(loader, D_003BC3C8[next].kind))
          Load(name, D_003BC3C8[next].kind, forced != 0);
        else
          Load(name, 0, forced != 0);
      }
      if (D_003BC3C8[requestedScreen].kind == 3)
        musicStarted = 1;
      if (!D_003BC3C8[requestedScreen].music) {
        func_001D8BC0(0.1f, MusicChannel(), -1, 0, 1);
        func_001D8DE8(MusicChannel());
      } else {
        if (requestedScreen == 6) {
          func_001D8BC0(0, MusicChannel(), 2, 1, 0);
          func_001D8DF0(MusicChannel());
        }
        if (musicStarted) {
          func_001D8BC0(0, MusicChannel(), requestedScreen == 21, 1, 0);
          func_001D8DF0(MusicChannel());
        }
      }
      currentScreen = requestedScreen;
    }
    char *controller = *(char **)(D_0040F0E0 + 0x21060);
    if (controller && func_0026BC30(*(void **)(controller + 0xc), 10) &&
        func_0026BC30(*(void **)(controller + 0xc), 12) &&
        func_0026BC30(*(void **)(controller + 0xc), 1) &&
        func_0026BC30(*(void **)(controller + 0xc), 5) &&
        func_0026BC30(*(void **)(controller + 0xc), 11) &&
        func_0026BC30(*(void **)(controller + 0xc), 13) &&
        !func_0035CFD8((char *)D_0040F544 + 0x3840, D_003F2540, 14)) {
      D_0040EAE0 = 1;
      func_0035D1A0(D_0048EF88, (char *)D_0040F544 + 0x3840, 30);
      func_00103F50(0);
    }
  }
  func_00109918(loader);
  if (*(int *)((char *)this + 0x1f4) == 55)
    func_0021A480(D_003F2850, 0, (char *)D_0040F544 + 0x38e7, 0);
  func_0010A268(message);
  if (message[8])
    func_0021A480(D_003F2850, 0, (char *)D_0040F544 + 0x38e7, 0);
  if (!D_0040D986)
    func_00205180(D_0040F524);
  else
    func_00105268(this);
  if (!*(void **)(D_0040F0E0 + 0x21060) || !func_00124D20()) {
    elapsed += *(float *)(D_0040F0E0 + 0x2013c);
    if (func_0020B950(D_0040F544)) {
      D_0040EAE0 = 1;
      elapsed = 0;
      func_00209A58((char *)D_0040F544 + 0x44c);
      if (!func_0035CCD8(func_0020B980(D_0040F544))) {
        func_00216AF0(func_00104050);
        func_0020B8C0(D_0040F544);
        ((FrontendMenuState*)(D_0040F0E0 + 0x20220))->Request(3, 0);
        FrontendScreenManager *screen = D_0040F544;
        func_0035CBC0(screen->requestedName, D_003F2698);
        if (screen->alternate)
          screen->alternatePending = 1;
        else
          screen->primaryPending = 1;
      } else {
        const char *name = func_0020B980(D_0040F544);
        FrontendScreenManager *screen = D_0040F544;
        func_0035CBC0(screen->requestedName, name);
        if (screen->alternate)
          screen->alternatePending = 1;
        else
          screen->primaryPending = 1;
      }
    }
  } else
    elapsed = 0;
  func_001E8980(*(void **)(D_0040F510 + 0xcbd8));
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001046B0);
#endif

#ifdef NON_MATCHING
// Unmatched: func_001046B0: movie selection control flow, audio argument
// ordering and register allocation.
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
void func_0020E338(void *);
void func_00109550(void *);
int *func_00123C90(void *, int, int);
int func_0012D158(void *, int, int);
extern void *D_0040F4D0;
int func_00109F68(void *, int);
void func_001D8BC0(float, void *, int, int, int);
void func_001D8DF0(void *);
void func_001D8DE8(void *);
unsigned char func_0026BC30(void *, int);
int func_0035CFD8(const char *, const char *, int);
void func_0035D1A0(char *, const char *, int);
void func_00103F50(int);
void func_00109918(void *);
void func_0021A480(const char *, int, void *, int);
void func_0010A268(void *);
void func_00205180(void *);
void func_00105268(FrontendMenuState *);
int func_00124D20();
int func_0020B950(void *);
void func_00209A58(void *);
const char *func_0020B980(void *);
int func_0035CCD8(const char *);
void func_00216AF0(void (*)());
void func_00104050();
void func_0020B8C0(void *);
void func_001E8980(void *);
extern char D_003F2540[], D_003F2850[], D_003F2698[];
}
static inline void *MusicChannel() {
  return *(void **)(*(char **)(D_0040F510 + 0xcbd8) + 0x34);
}
void FrontendMenuState::Update() {
  char name[16];
  if (D_0040D986) {
    func_0020E338((char *)this + 0xc);
    int next = requestedScreen;
    if (currentScreen != next) {
      if (next == 0) {
        func_00109550(loader);
      } else {
        if (next == 2) {
          int mission = *(int *)(D_0040F0E0 + 0x2014c);
          if (*func_00123C90(D_0048EFA8, 7, mission) < 1) {
            if (func_00123BD0(D_0048EFA8, 7, mission) ||
                func_00123BD0(D_0048EFA8, 6, mission))
              next = 26;
            else if (func_00123BD0(D_0048EFA8, 5, mission) ||
                     func_00123BD0(D_0048EFA8, 4, mission))
              next = 25;
            else if (func_00123BD0(D_0048EFA8, 3, mission) ||
                     func_00123BD0(D_0048EFA8, 2, mission))
              next = 24;
            else
              next = 23;
          } else
            next = func_0012D158(D_0040F4D0, 0, 3) + 23;
        }
        if (!D_0040EAD8)
          func_0035D728(name, D_003BC3C8[next].format, D_0040D998,
                        func_00108A20());
        else
          func_0035D728(name, D_003BC3C8[next].format, D_0040D990,
                        func_00108A20());
        if (name[0] == 'F' && D_0040EAE4 != 4)
          Load((const char *)((unsigned)name | 1), D_003BC3C8[next].kind,
               forced != 0);
        else if (!musicStarted || !func_00109F68(loader, D_003BC3C8[next].kind))
          Load(name, D_003BC3C8[next].kind, forced != 0);
        else
          Load(name, 0, forced != 0);
      }
      if (D_003BC3C8[requestedScreen].kind == 3)
        musicStarted = 1;
      if (!D_003BC3C8[requestedScreen].music) {
        func_001D8BC0(0.1f, MusicChannel(), -1, 0, 1);
        func_001D8DE8(MusicChannel());
      } else {
        if (requestedScreen == 6) {
          func_001D8BC0(0, MusicChannel(), 2, 1, 0);
          func_001D8DF0(MusicChannel());
        }
        if (musicStarted) {
          func_001D8BC0(0, MusicChannel(), requestedScreen == 21, 1, 0);
          func_001D8DF0(MusicChannel());
        }
      }
      currentScreen = requestedScreen;
    }
    char *controller = *(char **)(D_0040F0E0 + 0x21060);
    if (controller && func_0026BC30(*(void **)(controller + 0xc), 10) &&
        func_0026BC30(*(void **)(controller + 0xc), 12) &&
        func_0026BC30(*(void **)(controller + 0xc), 1) &&
        func_0026BC30(*(void **)(controller + 0xc), 5) &&
        func_0026BC30(*(void **)(controller + 0xc), 11) &&
        func_0026BC30(*(void **)(controller + 0xc), 13) &&
        !func_0035CFD8((char *)D_0040F544 + 0x3840, D_003F2540, 14)) {
      D_0040EAE0 = 1;
      func_0035D1A0(D_0048EF88, (char *)D_0040F544 + 0x3840, 30);
      func_00103F50(0);
    }
  }
  func_00109918(loader);
  if (*(int *)((char *)this + 0x1f4) == 55)
    func_0021A480(D_003F2850, 0, (char *)D_0040F544 + 0x38e7, 0);
  func_0010A268(message);
  if (message[8])
    func_0021A480(D_003F2850, 0, (char *)D_0040F544 + 0x38e7, 0);
  if (!D_0040D986)
    func_00205180(D_0040F524);
  else
    func_00105268(this);
  if (!*(void **)(D_0040F0E0 + 0x21060) || !func_00124D20()) {
    elapsed += *(float *)(D_0040F0E0 + 0x2013c);
    if (func_0020B950(D_0040F544)) {
      D_0040EAE0 = 1;
      elapsed = 0;
      func_00209A58((char *)D_0040F544 + 0x44c);
      if (!func_0035CCD8(func_0020B980(D_0040F544))) {
        func_00216AF0(func_00104050);
        func_0020B8C0(D_0040F544);
        Request(3, 0);
        FrontendScreenManager *screen = D_0040F544;
        func_0035CBC0(screen->requestedName, D_003F2698);
        if (screen->alternate)
          screen->alternatePending = 1;
        else
          screen->primaryPending = 1;
      } else {
        const char *name = func_0020B980(D_0040F544);
        FrontendScreenManager *screen = D_0040F544;
        func_0035CBC0(screen->requestedName, name);
        if (screen->alternate)
          screen->alternatePending = 1;
        else
          screen->primaryPending = 1;
      }
    }
  } else
    elapsed = 0;
  func_001E8980(*(void **)(D_0040F510 + 0xcbd8));
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001046B0);
#endif
