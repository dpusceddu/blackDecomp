// Unmatched: func_001046B0: movie selection control flow, audio argument
// ordering and register allocation.
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

#endif
