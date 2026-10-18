// Unmatched: func_0010BC10: EE128 color-by-value ABI and FP argument
// scheduling.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
extern "C" {
extern unsigned char D_0040D9A2;
extern FrontendSaveState *D_0040F4F0;
extern void *D_0040F0E4;
extern char **D_0040F53C;
int func_0026F4A8(void *);
int func_0026F4B8(void *);
int func_0010B610(FrontendSaveState *);
const char *func_0010B8B0(FrontendSaveState *, int);
int func_0035D728(char *, const char *, ...);
int func_0035D1A0(char *, const char *, int);
int func_00275128(const void *, char *, int);
int func_0027C370(float, float, float, void *, const char *,
                  FrontendDebugColor);
extern char D_003F3688[];
extern char D_003F3698[];
extern char D_003F36A8[];
extern char D_003F36C0[];
extern char D_003F36D8[];
extern char D_003F36F0[];
extern char D_003F3700[];
extern char D_003F3718[];
extern char D_003F3730[];
extern char D_003F3748[];
extern char D_003F3760[];
extern char D_003F3778[];
extern char D_003F3790[];
extern char D_003F37A8[];
extern char D_003F37B8[];
extern char D_003F37C8[];
extern char D_003F37D8[];
extern char D_003F37F8[];
extern char D_003F3808[];
extern char D_003F3818[];
}
extern "C" void func_0010BC10() {
  char line[256], name[256];
  FrontendDebugColor white = {1, 1, 1, 1};
  FrontendDebugColor green = {0.3f, 1, 0.3f, 1};
  FrontendDebugColor colors[10];
  if (D_0040D9A2) {
    func_0035D728(line, D_003F3688, func_0026F4A8(D_0040F4F0->io));
    func_0027C370(20, 40, 20, D_0040F0E4, line, white);
    func_0035D728(line, D_003F3698, func_0026F4B8(D_0040F4F0->io));
    func_0027C370(20, 60, 20, D_0040F0E4, line, white);
    func_0035D728(line, D_003F36A8, D_0040F4F0->flag510);
    func_0027C370(20, 80, 20, D_0040F0E4, line, white);
    func_0035D728(line, D_003F36C0, D_0040F4F0->activeSlot);
    func_0027C370(20, 100, 20, D_0040F0E4, line, white);
    func_0035D728(line, D_003F36D8, D_0040F4F0->waiting);
    func_0027C370(20, 120, 20, D_0040F0E4, line, white);
    func_0035D728(line, D_003F36F0, func_0010B610(D_0040F4F0));
    func_0027C370(20, 140, 20, D_0040F0E4, line, white);
    func_0035D728(line, D_003F3700, D_0040F4F0->reserved4);
    func_0027C370(20, 160, 20, D_0040F0E4, line, white);
    func_0035D728(line, D_003F3718, D_0040F4F0->mode);
    func_0027C370(20, 180, 20, D_0040F0E4, line, white);
    for (int i = 9; i >= 0; --i)
      colors[i] = white;
    if ((unsigned)D_0040F4F0->mode < 10)
      colors[D_0040F4F0->mode] = green;
    float y = 200;
    func_0035D728(line, D_003F3730, D_0040F4F0->loadState);
    func_0027C370(40, y, 15, D_0040F0E4, line, white);
    y += 15;
    func_0035D728(line, D_003F3748, D_0040F4F0->saveState);
    func_0027C370(40, y, 15, D_0040F0E4, line, white);
    y += 15;
    func_0035D728(line, D_003F3760, D_0040F4F0->profileState);
    func_0027C370(40, y, 15, D_0040F0E4, line, white);
    y += 15;
    func_0035D728(line, D_003F3778, D_0040F4F0->overwriteState);
    func_0027C370(40, y, 15, D_0040F0E4, line, white);
    y += 15;
    func_0035D728(line, D_003F3790, D_0040F4F0->createState);
    func_0027C370(40, y, 15, D_0040F0E4, line, white);
    y += 15;
    y += 20;
    func_00275128((char *)D_0040F4F0 + 0x44a, line, 256);
    func_0035D728(line, D_003F37A8, line);
    func_0027C370(20, y, 15, D_0040F0E4, line, white);
    y += 15;
    func_00275128((char *)D_0040F4F0 + 0x3a, line, 256);
    func_0035D728(line, D_003F37B8, line);
    func_0027C370(20, y, 15, D_0040F0E4, line, white);
    y += 15;
    for (int i = 0; i < 4; ++i) {
      colors[i] = i == D_0040F4F0->selected ? green : white;
      func_00275128((char *)D_0040F4F0 + 0x34a + i * 0x40, line, 256);
      func_0035D728(line, D_003F37C8, i + 1, line);
      func_0027C370(20, y, 15, D_0040F0E4, line, colors[i]);
      y += 15;
    }
    func_0035D728(line, D_003F37D8, D_0040F4F0->itemCount, D_0040F4F0->selected,
                  D_0040F4F0->choice);
    func_0027C370(20, y, 15, D_0040F0E4, line, white);
    y += 15;
    float x = 40;
    for (int i = 0; i < 3; ++i) {
      func_0035D1A0(name, func_0010B8B0(D_0040F4F0, i), 64);
      func_0035D728(line, D_003F37F8, i, name);
      func_0027C370(400, x, 15, D_0040F0E4, line, white);
      x += 15;
    }
    func_0035D728(name, D_003F3808);
    if (*D_0040F53C)
      func_0035D1A0(name, *D_0040F53C + 8, 64);
    func_0035D728(line, D_003F3818, name);
    func_0027C370(400, x, 15, D_0040F0E4, line, white);
  }
}

#endif
