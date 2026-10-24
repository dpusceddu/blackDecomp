#include "include_asm.h"

#include "game/frontend_resources.hpp"

extern "C" int func_0010BC00() { return 1; }
extern "C" void func_0010BC08() {}

extern "C" int func_0010B5B0(FrontendSaveState *);
void FrontendSaveState::Finish() {
  complete = 1;
  func_0010B5B0(this);
}

extern "C" int func_0010B160(FrontendSaveState *);
int FrontendSaveState::Begin(int next) {
  func_0010B160(this);
  operation = next;
  return 1;
}

int FrontendSaveState::Ready() { return operation == 31; }

#ifdef NON_MATCHING
// Unmatched: func_0010BC10: EE128 color-by-value ABI and FP argument
// scheduling.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010BC10);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010C2F8);

#ifdef NON_MATCHING
// Unmatched: func_0010C398: profile aggregate copy allocation and state/callee
// types.
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern char *D_0040F4EC;
int func_001050A8(...);
int func_0010B338(...);
int func_0010B3A8(...);
int func_0010B4D8(...);
int func_0010B5B0(...);
int func_0010B630(...);
int func_0010B6B8(...);
int func_0010B7A0(...);
int func_0010B7F0(...);
int func_0010B8E8(...);
int func_0010B9B0(...);
int func_0010EAC0(...);
int func_0010EAF8(...);
int func_0010EBC0(...);
FrontendSaveProfile *func_0010F280(...);
int func_0010F470(...);
int func_0026F4B8(...);
int func_0035D728(...);
}

void FrontendSaveState::Load()

{
  bool multipleChoices;
  int scratch;
  int requiredBytes;
  int ioStatus;
  unsigned long selectedSlot;
  long result;

  char message[1024];

  const unsigned address = (unsigned)this;
  switch (loadState) {
  case 0:
    func_0010B338(this, *(int *)(address + 0xa8c));
    func_0010B4D8(this, 0);
    func_0010B6B8(this);
    complete = 0;
    flag510 = 0;
    activeSlot = 0xffffffff;
    func_0010EAC0(this, 0);
    loadState = 1;
    break;
  case 1:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      func_0010EAC0(this, 2);
      loadState = 2;
      return;
    }
    goto LAB_0010c5fc;
  case 2:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result == 0) {
      result = func_0026F4B8(address + 0x9b0);
      if (result != 9)
        goto LAB_0010c5fc;
    } else if (status != 0) {
      func_0010B5B0(this);
      func_0010EAC0(this, 0x17);
      func_0010B338(this, *(int *)(address + 0xaac));
      func_0010B4D8(this, 0);
      loadState = 4;
      return;
    }
    func_0010EAC0(this, 4);
    loadState = 3;
    break;
  case 3:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result == 0) {
      loadState = 5;
      return;
    }
    goto LAB_0010c89c;
  case 4:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      func_0010B7F0(this);
      func_0010B7A0(this);
      selectedSlot = func_0010B630(this);
      slot = (int)selectedSlot;
      if (((selectedSlot < 3) && (scratch = address + (int)selectedSlot,
                                  *(char *)(scratch + 0x528) != '\0')) &&
          (*(char *)(scratch + 0x52b) != '\x01')) {
        *func_0010F280(D_0040F4EC) = profiles[slot];
        func_0010F470(D_0040F4EC);
        flag510 = 1;
        loadState = 0xb;
        activeSlot = slot;
        return;
      }
      goto switchD_0010c878_caseD_2;
    }
  LAB_0010c5fc:
    loadState = 10;
    break;
  case 5:
    if (waiting == '\0') {
      requiredBytes = func_0010B9B0(this);
      scratch = requiredBytes + 0x3ff;
      if (-1 < requiredBytes) {
        scratch = requiredBytes;
      }
      func_0035D728(message, *(int *)(address + 0xa94), scratch >> 10);
      func_0010B338(this, message);
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 1;
      multipleChoices = 1 < itemCount;
    LAB_0010c78c:
      if (!multipleChoices) {
        selected = 0;
      }
      func_0010B4D8(this, 2);
      return;
    }
    result = func_0010B8E8(this);
    if (result != 1) {
      scratch = choice;
      if (scratch == 0)
        goto LAB_0010c690;
    joined_r0x0010c740:
      if (scratch != 1) {
        return;
      }
    }
    goto LAB_0010c7c8;
  case 6:
    if (waiting == '\0') {
      requiredBytes = func_0010B9B0(this);
      scratch = requiredBytes + 0x3ff;
      if (-1 < requiredBytes) {
        scratch = requiredBytes;
      }
      func_0035D728(message, *(int *)(address + 0xa90), scratch >> 10);
      func_0010B338(this, message);
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 1;
      multipleChoices = 1 < itemCount;
      goto LAB_0010c78c;
    }
    result = func_0010B8E8(this);
    if (result != 1)
      goto LAB_0010c7c8;
    scratch = choice;
    if (scratch != 0)
      goto joined_r0x0010c740;
  LAB_0010c690:
    func_0010B5B0(this);
    goto LAB_0010c89c;
  case 7:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xabc));
      func_0010B3A8(this, *(int *)(address + 0xb44), *(int *)(address + 0xb40),
                    0, 0);
      selected = 0;
      multipleChoices = 0 < itemCount;
      goto LAB_0010c78c;
    }
    result = func_0010B8E8(this);
    if ((result != 1) && (choice != 0)) {
      if (choice != 1) {
        return;
      }
      goto LAB_0010c690;
    }
  LAB_0010c7c8:
    func_0010B5B0(this);
    loadState = 0;
    break;
  case 8:
    if (waiting == '\0') {
      func_0010B5B0(this);
      func_0010B338(this, 0x3f3858);
      func_0010B3A8(this, *(int *)(address + 0xb40), 0, 0, 0);
      func_0010B4D8(this, 5);
      return;
    }
    if (choice != 0) {
      return;
    }
    func_0010B5B0(this);
    goto LAB_0010c8d0;
  case 10:
    ioStatus = func_0026F4B8(address + 0x9b0);
    if (true) {
      switch (ioStatus) {
      case 1:
        loadState = 6;
        return;
      case 4:
      case 5:
      case 9:
      case 10:
        loadState = 7;
        return;
      }
    }
  switchD_0010c878_caseD_2:
  LAB_0010c89c:
    loadState = 0xb;
    break;
  case 0xb:
    func_0010B5B0(this);
    func_001050A8(D_0040F0E0 + 0x20220, 0x3f2530);
  LAB_0010c8d0:
    complete = 1;
  }
  return;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010C398);
#endif

#ifdef NON_MATCHING
// Unmatched: func_0010C8E8: profile aggregate copy allocation and state/callee
// types.
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F4EC;
int func_0010B338(...);
int func_0010B3A8(...);
int func_0010B4D8(...);
int func_0010B5B0(...);
int func_0010B630(...);
int func_0010B6B8(...);
int func_0010B7A0(...);
int func_0010B7F0(...);
const char *func_0010B8B0(...);
int func_0010B8E8(...);
int func_0010B9B0(...);
int func_0010EAC0(...);
int func_0010EAF8(...);
int func_0010EBC0(...);
FrontendSaveProfile *func_0010F280(...);
int func_0010F470(...);
int func_0026F4B8(...);
int func_0035D728(...);
}

void FrontendSaveState::SelectProfile()

{
  unsigned selectedSlot;
  int requiredBytes;
  int textOrStatus;
  long result;
  int scratch;
  long uVar10;
  int alternateText;
  long uVar12;
  long uVar13;

  char message[1024];

  const unsigned address = (unsigned)this;
  switch (profileState) {
  case 0:
    profileState = 6;
    break;
  case 1:
    func_0010B5B0(this);
    func_0010B338(this, *(int *)(address + 0xa8c));
    func_0010B4D8(this, 0);
    func_0010B6B8(this);
    func_0010EAC0(this, 0);
    profileState = 2;
    break;
  case 2:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      func_0010EAC0(this, 2);
      profileState = 3;
      return;
    }
    goto LAB_0010cde8;
  case 3:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      if (status != 0) {
        func_0010B338(this, *(int *)(address + 0xaac));
        func_0010EAC0(this, 0x17);
        profileState = 4;
        return;
      }
      profileState = 4;
      return;
    }
    goto LAB_0010cde8;
  case 4:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      func_0010B7F0(this);
      func_0010B7A0(this);
      func_0010B5B0(this);
      func_0010B338(this, *(int *)(address + 0xb48));
      uVar10 = (long)func_0010B8B0(this, 0);
      uVar12 = (long)func_0010B8B0(this, 1);
      uVar13 = (long)func_0010B8B0(this, 2);
      func_0010B3A8(this, uVar10, uVar12, uVar13, 0);
      scratch = func_0010B630(this);
      selected = scratch;
      if ((scratch < 0) || (itemCount <= scratch)) {
        selected = 0;
      }
      func_0010B4D8(this, 1);
      profileState = 5;
      return;
    }
    result = func_0026F4B8(address + 0x9b0);
    if (result == 1) {
      func_0010B5B0(this);
      profileState = 9;
      return;
    }
    goto LAB_0010cde8;
  case 5:
    if (waiting == '\0') {
      *func_0010F280(D_0040F4EC) = profiles[slot];
      func_0010F470(D_0040F4EC);
      profileState = 0xc;
      activeSlot = slot;
      return;
    }
    result = func_0010B8E8(this);
    if (result == 1)
      goto LAB_0010cddc;
    selectedSlot = *(unsigned *)(address + 0x500);
    if (selectedSlot < 3) {
      if ((*(char *)(address + selectedSlot + 0x528) == '\x01') &&
          (*(char *)(address + 0x52b + selectedSlot) == '\0')) {
        *(unsigned *)(address + 0x50c) = selectedSlot;
        func_0010B5B0(this);
      } else if (*(char *)(address + 0x52b + selectedSlot) == '\x01') {
        func_0010B5B0(this);
        profileState = 10;
      }
      choice = 0xffffffff;
      return;
    }
    if (selectedSlot != 3) {
      return;
    }
    goto LAB_0010ce78;
  case 6:
    if (waiting == '\0') {
      func_0010B5B0(this);
      func_0010B338(this, *(int *)(address + 0xacc));
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 1;
      if (itemCount < 2) {
        selected = 0;
      }
      goto LAB_0010ce24;
    }
    scratch = choice;
    if (scratch == 0) {
      profileState = 1;
      return;
    }
    goto joined_r0x0010ce70;
  case 7:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xab4));
      textOrStatus = *(int *)(address + 0xb44);
      alternateText = *(int *)(address + 0xb40);
    LAB_0010ce14:
      func_0010B3A8(this, textOrStatus, alternateText, 0, 0);
    LAB_0010ce24:
      func_0010B4D8(this, 2);
      return;
    }
    result = func_0010B8E8(this);
    if (result != 1) {
      scratch = choice;
      goto joined_r0x0010ce58;
    }
  LAB_0010cddc:
    func_0010B5B0(this);
  LAB_0010cde8:
    profileState = 0xd;
    break;
  case 8:
    if (waiting == '\0') {
      requiredBytes = func_0010B9B0(this);
      scratch = requiredBytes + 0x3ff;
      if (-1 < requiredBytes) {
        scratch = requiredBytes;
      }
      func_0035D728(message, *(int *)(address + 0xab0), scratch >> 10);
      func_0010B338(this, message);
      textOrStatus = *(int *)(address + 0xb44);
      alternateText = *(int *)(address + 0xb40);
      goto LAB_0010ce14;
    }
    result = func_0010B8E8(this);
    if (result != 1) {
    LAB_0010ce48:
      func_0010B5B0(this);
      profileState = 1;
      return;
    }
    scratch = choice;
    goto joined_r0x0010ce58;
  case 9:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xac8));
      textOrStatus = *(int *)(address + 0xb38);
      alternateText = *(int *)(address + 0xb3c);
      goto LAB_0010ce14;
    }
    result = func_0010B8E8(this);
    if (result != 1)
      goto LAB_0010ce48;
    scratch = choice;
  joined_r0x0010ce58:
    if (scratch == 0) {
      func_0010B5B0(this);
      profileState = 1;
    } else {
    joined_r0x0010ce70:
      if (scratch == 1) {
      LAB_0010ce78:
        func_0010B5B0(this);
      LAB_0010ce84:
        profileState = 0xe;
      }
    }
    break;
  case 10:
    if (waiting == '\0') {
      textOrStatus = *(int *)(address + 0xac0);
      goto LAB_0010cce8;
    }
    if (choice != 0) {
      return;
    }
    goto LAB_0010ce84;
  case 0xb:
    if (waiting != '\0') {
      scratch = choice;
    joined_r0x0010ccc8:
      if (scratch != 0) {
        return;
      }
      goto LAB_0010ce78;
    }
    textOrStatus = *(int *)(address + 0xabc);
    goto LAB_0010cce8;
  case 0xc:
    if (waiting != '\0') {
      scratch = choice;
      goto joined_r0x0010ccc8;
    }
    textOrStatus = *(int *)(address + 0xab8);
  LAB_0010cce8:
    func_0010B338(this, textOrStatus);
    func_0010B3A8(this, *(int *)(address + 0xb40), 0, 0, 0);
    func_0010B4D8(this, 5);
    break;
  case 0xd:
    textOrStatus = func_0026F4B8(address + 0x9b0);
    func_0010B5B0(this);
    if (false) {
    switchD_0010cec0_caseD_2:
      profileState = 0xb;
    } else {
      switch (textOrStatus) {
      case 1:
        profileState = 8;
        break;
      default:
        goto switchD_0010cec0_caseD_2;
      case 3:
      case 4:
      case 9:
        profileState = 7;
      }
    }
    break;
  case 0xe:
    complete = 1;
    func_0010B5B0(this);
  }
  return;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010C8E8);
#endif

#ifdef NON_MATCHING
// Unmatched: func_0010CF18: profile/IO types, register allocation and state
// control flow.
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern char *D_0040F4EC;
extern char **D_0040F53C;
int func_0010B200(...);
int func_0010B2C0(...);
int func_0010B338(...);
int func_0010B3A8(...);
int func_0010B4D8(...);
int func_0010B530(...);
int func_0010B590(...);
int func_0010B5B0(...);
int func_0010B630(...);
int func_0010B6B8(...);
int func_0010B7A0(...);
int func_0010B7F0(...);
const char *func_0010B8B0(...);
int func_0010B8E8(...);
int func_0010B9B0(...);
int func_0010EAC0(...);
int func_0010EAF8(...);
int func_0010EBC0(...);
FrontendSaveProfile *func_0010F280(...);
int func_0010F288(...);
int func_0010F470(...);
int func_00215D68(...);
int func_0026F4B8(...);
int func_00275128(...);
int func_0035D728(...);
}

/* WARNING: Type propagation algorithm not settling */

void FrontendSaveState::Save()

{
  unsigned uVar1;
  int previousChoice;
  bool sizeIsNonnegative;
  int choiceValue;
  int textOrStatus;
  long result;
  const char *puVar9;
  long uVar10;
  int value;
  long uVar12;
  long uVar13;

  char message[1024];
  char profileName[80];

  puVar9 = message;
  const unsigned address = (unsigned)this;
  switch (saveState) {
  case 0:
    func_0010B6B8(this);
    func_0010B338(this, *(int *)(address + 0xa8c));
    func_0010B4D8(this, 0);
    func_0010EAC0(this, 0);
    saveState = 1;
    break;
  case 1:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      func_0010EAC0(this, 2);
      saveState = 2;
      return;
    }
    goto LAB_0010d758;
  case 2:
    result = func_0010EAF8(this);
    if (result != 0) {
      result = func_0010EBC0(this);
      if (result == 0) {
        func_0010EAC0(this, 4);
        saveState = 3;
      } else if (status == 0) {
        saveState = 4;
      } else {
        func_0010EAC0(this, 0x17);
        saveState = 4;
      }
    }
    break;
  case 3:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result == 0) {
      func_0010B5B0(this);
      saveState = 0x15;
      return;
    }
    if ((formatState != 4) && (deleteState != 4)) {
      func_0010B5B0(this);
      func_0010B200(this);
      formatState = 1;
      return;
    }
    func_0010B7F0(this);
  LAB_0010d0cc:
    saveState = 5;
    break;
  case 4:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      func_0010B7F0(this);
      func_0010B7A0(this);
      goto LAB_0010d0cc;
    }
    goto LAB_0010d758;
  case 5:
    func_0010B5B0(this);
    func_0010B338(this, *(int *)(address + 0xb4c));
    uVar10 = (long)func_0010B8B0(this, 0);
    uVar12 = (long)func_0010B8B0(this, 1);
    uVar13 = (long)func_0010B8B0(this, 2);
    func_0010B3A8(this, uVar10, uVar12, uVar13, 0);
    value = func_0010B630(this);
    selected = value;
    if ((value < 0) || (itemCount <= value)) {
      selected = 0;
    }
    func_0010B4D8(this, 1);
    saveState = 6;
    break;
  case 6:
    if (waiting == '\0') {
      if (*(char *)(address + 0x518) != '\0') {
        func_0010B338(this, *(int *)(address + 0xad0));
        func_0010B4D8(this, 0);
        func_0010EAC0(this, 6);
        saveState = 8;
        return;
      }
      if (*(char *)(address + slot + 0x528) == '\x01') {
        func_0010B5B0(this);
        saveState = 0xc;
        return;
      }
    LAB_0010d604:
      func_0010B5B0(this);
      goto LAB_0010d610;
    }
    result = func_0010B8E8(this);
    if (result != 1) {
      uVar1 = *(unsigned *)(address + 0x500);
      if (uVar1 < 3) {
        *(unsigned *)(address + 0x50c) = uVar1;
        choice = 0xffffffff;
        func_0010B5B0(this);
        return;
      }
      if (uVar1 != 3) {
        return;
      }
      saveState = 0x17;
      formatState = 9;
      choice = 0xffffffff;
      func_0010B5B0(this);
      if (overwriteState != 0xe) {
        return;
      }
      func_0010B2C0(this, 0);
      return;
    }
  LAB_0010d74c:
    func_0010B5B0(this);
    goto LAB_0010d758;
  case 7:
    if (flag514 == '\0') {
      return;
    }
    result = func_0010B8E8(this);
    if (result == 1) {
      func_0010B5B0(this);
      flag514 = 0;
      saveState = 0x16;
      return;
    }
    if (choice == 0) {
      result = func_0010B590(this);
      if (result == 1) {
        flag514 = 0;
        func_0010B338(this, *(int *)(address + 0xad0));
        func_0010B4D8(this, 0);
        func_00275128(address + 0x4ca, profileName, 0x50);
        func_0010F288(D_0040F4EC, profileName, 0);
        profiles[slot] = *func_0010F280(D_0040F4EC);
        goto LAB_0010d4a0;
      }
      value = choice;
    } else {
      value = choice;
    }
    if (value == 1) {
      func_0010B5B0(this);
      saveState = 0;
      flag514 = 0;
      return;
    }
    if (value != 2) {
      return;
    }
  LAB_0010d610:
    saveState = 9;
    break;
  case 8:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0)
      goto LAB_0010d610;
    result = func_0026F4B8(address + 0x9b0);
    if (result == 1) {
      func_0010B5B0(this);
      saveState = 0x13;
      return;
    }
  LAB_0010d758:
    saveState = 0x16;
    break;
  case 9:
    if ((deleteState != 4) && (formatState != 4)) {
      func_00215D68(D_0040F0E0 + 0x20258, *D_0040F53C + 8);
      func_0010B5B0(this);
      func_0010B3A8(this, 0, 0, 0, 0);
      func_0010B530(this, 0);
      saveState = 7;
      flag514 = 1;
      return;
    }
    func_00275128(address + 0x4ca, profileName, 0x50);
    func_0010F288(D_0040F4EC, profileName, 0);
    func_0010B338(this, *(int *)(address + 0xad0));
    func_0010B4D8(this, 0);
    profiles[slot] = *func_0010F280(D_0040F4EC);
  LAB_0010d4a0:
    func_0010EAC0(this, 0xe);
    saveState = 10;
    break;
  case 10:
    result = func_0010EAF8(this);
    if (result != 0) {
      result = func_0010EBC0(this);
      if (result == 0) {
        result = func_0026F4B8(address + 0x9b0);
        textOrStatus = 0x16;
        if (result == 1) {
          func_0010B5B0(this);
          textOrStatus = 0x13;
        }
      } else {
        func_0010F470(D_0040F4EC);
        activeSlot = slot;
        func_0010B5B0(this);
        textOrStatus = 0x11;
      }
      saveState = textOrStatus;
      func_0010B7F0(this);
    }
    break;
  case 0xb:
    result = func_0010EAF8(this);
    if (result != 0) {
      result = func_0010EBC0(this);
      if (result == 0) {
        func_0010B5B0(this);
        saveState = 0x10;
      } else {
        func_0010B5B0(this);
        saveState = 0xf;
      }
    }
    break;
  case 0xc:
    if (waiting != '\0') {
      result = func_0010B8E8(this);
      value = 1;
      if (result != 1) {
        choiceValue = choice;
        if (choiceValue != 0)
          goto LAB_0010d8f8;
        goto LAB_0010d604;
      }
      goto LAB_0010d74c;
    }
    value = (int)func_0010B8B0(this, slot);
    textOrStatus = *(int *)(address + 0xaec);
    goto LAB_0010d86c;
  case 0xd:
    if (waiting != '\0') {
      result = func_0010B8E8(this);
      value = 1;
      if (result != 1) {
        choiceValue = choice;
        if (choiceValue == 0) {
          func_0010B5B0(this);
          saveState = 0xe;
          return;
        }
        goto LAB_0010d8f8;
      }
      goto LAB_0010d74c;
    }
    result = func_0010B9B0(this);
    value = (int)result + 0x3ff;
    sizeIsNonnegative = -1 < result;
    textOrStatus = *(int *)(address + 0xadc);
    goto LAB_0010d860;
  case 0xe:
    if (waiting != '\0') {
      result = func_0010B8E8(this);
      value = 1;
      if (result != 1) {
        choiceValue = choice;
        if (choiceValue == 0) {
          func_0010B5B0(this);
          func_0010B338(this, *(int *)(address + 0xa98));
          func_0010B4D8(this, 0);
          func_0010EAC0(this, 0xb);
          saveState = 0xb;
          return;
        }
        goto LAB_0010d8f8;
      }
      goto LAB_0010d74c;
    }
    puVar9 = *(const char **)(address + 0xaa8);
    goto LAB_0010d878;
  case 0xf:
    if (waiting != '\0') {
      if (choice != 0) {
        return;
      }
      goto LAB_0010d900;
    }
    textOrStatus = *(int *)(address + 0xa9c);
    goto LAB_0010d670;
  case 0x10:
    if (waiting != '\0') {
      value = choice;
    LAB_0010d650:
      choiceValue = 1;
      previousChoice = value;
    joined_r0x0010d8dc:
      if (previousChoice == 0) {
      LAB_0010d8e4:
        func_0010B5B0(this);
        saveState = 0x17;
        return;
      }
    LAB_0010d8f8:
      if (choiceValue != value) {
        return;
      }
    LAB_0010d900:
      func_0010B5B0(this);
      saveState = 0;
      return;
    }
    puVar9 = *(const char **)(address + 0xaa0);
    goto LAB_0010d878;
  case 0x11:
    if (waiting != '\0') {
      if (choice != 0) {
        return;
      }
      goto LAB_0010d8e4;
    }
    textOrStatus = *(int *)(address + 0xae0);
  LAB_0010d670:
    func_0010B338(this, textOrStatus);
    func_0010B3A8(this, *(int *)(address + 0xb40), 0, 0, 0);
    func_0010B4D8(this, 5);
    break;
  case 0x12:
    if (waiting != '\0') {
      value = choice;
      goto LAB_0010d650;
    }
    puVar9 = *(const char **)(address + 0xae4);
    goto LAB_0010d878;
  case 0x13:
    if (waiting != '\0') {
      result = func_0010B8E8(this);
      if ((result == 1) && (choice != 0)) {
        if (choice != 1) {
          return;
        }
        goto LAB_0010d8e4;
      }
      goto LAB_0010d900;
    }
    puVar9 = *(const char **)(address + 0xae8);
    goto LAB_0010d878;
  case 0x14:
    if (waiting != '\0') {
      result = func_0010B8E8(this);
      if (result != 1)
        goto LAB_0010d900;
      choiceValue = choice;
      if (choiceValue == 0)
        goto LAB_0010d8e4;
      value = 1;
      goto LAB_0010d8f8;
    }
    result = func_0010B9B0(this);
    value = (int)result + 0x3ff;
    sizeIsNonnegative = -1 < result;
    textOrStatus = *(int *)(address + 0xad4);
    goto LAB_0010d860;
  case 0x15:
    if (waiting != '\0') {
      result = func_0010B8E8(this);
      value = 1;
      if (result == 1)
        goto LAB_0010d900;
      choiceValue = choice;
      previousChoice = choiceValue;
      goto joined_r0x0010d8dc;
    }
    result = func_0010B9B0(this);
    value = (int)result + 0x3ff;
    sizeIsNonnegative = -1 < result;
    textOrStatus = *(int *)(address + 0xad8);
  LAB_0010d860:
    if (sizeIsNonnegative) {
      value = (int)result;
    }
    value = value >> 10;
  LAB_0010d86c:
    func_0035D728(message, textOrStatus, value);
  LAB_0010d878:
    func_0010B338(this, puVar9);
    func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c), 0,
                  0);
    selected = 1;
    if (itemCount < 2) {
      selected = 0;
    }
    func_0010B4D8(this, 2);
    break;
  case 0x16:
    textOrStatus = func_0026F4B8(address + 0x9b0);
    func_0010B5B0(this);
    if (false) {
    switchD_0010d944_caseD_2:
      saveState = 0x12;
    } else {
      switch (textOrStatus) {
      case 1:
        saveState = 0x14;
        break;
      default:
        goto switchD_0010d944_caseD_2;
      case 3:
        saveState = 0xd;
      }
    }
    break;
  case 0x17:
    if (deleteState == 4) {
      func_0010B5B0(this);
      mode = 2;
      deleteState = 9;
    } else if (overwriteState == 0xe) {
      func_0010B5B0(this);
      mode = 5;
      complete = 1;
      overwriteState = 0x10;
    } else {
      complete = 1;
      func_0010B5B0(this);
    }
  }
  return;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010CF18);
#endif

#ifdef NON_MATCHING
// Unmatched: func_0010D9F0: profile/IO types, register allocation and state
// control flow.
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern char *D_0040F4EC;
extern char **D_0040F53C;
int func_0010B200(...);
int func_0010B338(...);
int func_0010B3A8(...);
int func_0010B4D8(...);
int func_0010B5B0(...);
int func_0010B6B8(...);
int func_0010B7A0(...);
int func_0010B7F0(...);
int func_0010B8E8(...);
int func_0010EAC0(...);
int func_0010EAF8(...);
int func_0010EBC0(...);
FrontendSaveProfile *func_0010F280(...);
int func_0010F288(...);
int func_00215028(...);
int func_0026F4B8(...);
int func_0035C4B0(...);
int func_0035D728(...);
}

/* WARNING: Type propagation algorithm not settling */

void FrontendSaveState::Overwrite()

{
  bool multipleChoices;
  int profileAddressOrSlot;
  int textOrStatus;
  long result;
  int choiceValue;
  const char *puVar10;

  char message[1024];
  int iStack_60;
  int auStack_5c[3];

  puVar10 = message;
  const unsigned address = (unsigned)this;
  profileAddressOrSlot = (int)*D_0040F53C;
  switch (overwriteState) {
  case 0:
    if (((activeSlot < 0) || (profileAddressOrSlot == 0)) ||
        (*(char *)(profileAddressOrSlot + 0x6a5) != '\0')) {
    LAB_0010ddd4:
      func_0010B5B0(this);
      overwriteState = 0xe;
      func_0010B200(this);
      return;
    }
    if (*(char *)(D_0040F0E0 + 0x20164) != '\0') {
      if (*(char *)(address + 0x517) != '\0') {
        func_0010B5B0(this);
        *(unsigned char *)(address + 0x517) = 0;
        overwriteState = 7;
        return;
      }
    LAB_0010dd8c:
      func_0010B5B0(this);
      overwriteState = 1;
      return;
    }
    break;
  case 1:
    if (*(unsigned *)(address + 0x524) < 3) {
      func_0010B6B8(this);
      func_0010B338(this, *(int *)(address + 0xa8c));
      func_0010B4D8(this, 0);
      func_0010EAC0(this, 0);
      overwriteState = 2;
      return;
    }
    goto LAB_0010dba4;
  case 2:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      func_0010EAC0(this, 2);
      overwriteState = 3;
      return;
    }
    goto LAB_0010dba4;
  case 3:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      if (status != 0) {
        func_0010EAC0(this, 0x17);
        overwriteState = 4;
        return;
      }
      overwriteState = 4;
      return;
    }
    goto LAB_0010dba4;
  case 4:
    result = func_0010EAF8(this);
    if (result == 0) {
      return;
    }
    result = func_0010EBC0(this);
    if (result != 0) {
      func_0010B7F0(this);
      func_0010B7A0(this);
      overwriteState = 5;
      return;
    }
  LAB_0010dba4:
    overwriteState = 0xf;
    return;
  case 5:
    profileAddressOrSlot = address + activeSlot;
    if ((*(char *)(profileAddressOrSlot + 0x528) != '\0') &&
        (*(char *)(profileAddressOrSlot + 0x52b) != '\x01')) {
      multipleChoices = true;
      if ((*D_0040F4EC != *(int *)(activeSlot * 0x778 + address + 0x12c0)) &&
          (result = func_0026F4B8(address + 0x9b0), result != 2)) {
        multipleChoices = false;
      }
      iStack_60 = D_0040F4EC[1];
      auStack_5c[0] = *(int *)(activeSlot * 0x778 + address + 0xc18);
      result = func_0035C4B0(&iStack_60, auStack_5c, 4);
      if (result != 0) {
        multipleChoices = false;
      }
      if (multipleChoices) {
        func_0010B338(this, *(int *)(address + 0xafc));
        func_0010B4D8(this, 0);
        func_0010F288(D_0040F4EC, 0, 0);
        profileAddressOrSlot = activeSlot;
        profiles[profileAddressOrSlot] = *func_0010F280(D_0040F4EC);
        func_0010EAC0(this, 0xe);
        overwriteState = 6;
        return;
      }
    }
    func_0010B5B0(this);
  LAB_0010e0b0:
    overwriteState = 0xb;
    return;
  case 6:
    result = func_0010EAF8(this);
    if (result != 0) {
      result = func_0010EBC0(this);
      textOrStatus = 0x10;
      if (result == 0) {
        result = func_0026F4B8(address + 0x9b0);
        textOrStatus = 0xf;
        if (result == 1) {
          func_0010B5B0(this);
          textOrStatus = 10;
        }
      }
      overwriteState = textOrStatus;
      func_0010B7F0(this);
      return;
    }
    return;
  case 7:
    if (waiting == '\0') {
      func_0035D728(message, *(int *)(address + 0xaf8),
                    profileAddressOrSlot + 8);
    LAB_0010dd5c:
      func_0010B338(this, puVar10);
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      goto LAB_0010dff8;
    }
    if (choice == 0)
      goto LAB_0010dd8c;
    if (choice != 1) {
      return;
    }
    func_0010B5B0(this);
    break;
  case 8:
    if (waiting == '\0') {
      puVar10 = *(const char **)(address + 0xaf0);
      goto LAB_0010dd5c;
    }
    if (choice == 0)
      goto LAB_0010ddd4;
    if (choice != 1) {
      return;
    }
    func_0010B5B0(this);
    break;
  case 9:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xb08));
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 0;
      multipleChoices = 0 < itemCount;
      goto LAB_0010dfec;
    }
    result = func_0010B8E8(this);
    if (result != 1)
      goto LAB_0010e054;
    profileAddressOrSlot = choice;
    goto joined_r0x0010df4c;
  case 10:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xb04));
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 0;
      multipleChoices = 0 < itemCount;
      goto LAB_0010dfec;
    }
    result = func_0010B8E8(this);
    if (result != 1)
      goto LAB_0010e054;
    profileAddressOrSlot = choice;
    goto joined_r0x0010df4c;
  case 0xb:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xb08));
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 0;
      multipleChoices = 0 < itemCount;
      goto LAB_0010dfec;
    }
    result = func_0010B8E8(this);
    if (result == 1)
      goto LAB_0010e054;
    profileAddressOrSlot = choice;
  joined_r0x0010df4c:
    if (profileAddressOrSlot != 0) {
      if (profileAddressOrSlot != 1) {
        return;
      }
    LAB_0010df98:
      func_0010B5B0(this);
      overwriteState = 0xd;
      return;
    }
  LAB_0010e054:
    func_0010B5B0(this);
    overwriteState = 0;
    return;
  case 0xc:
    if (waiting != '\0') {
      result = func_0010B8E8(this);
      choiceValue = 1;
      if (result == 1)
        goto LAB_0010e054;
      profileAddressOrSlot = choice;
      if (profileAddressOrSlot == 0)
        goto LAB_0010df98;
    LAB_0010e04c:
      if (choiceValue != profileAddressOrSlot) {
        return;
      }
      goto LAB_0010e054;
    }
    textOrStatus = *(int *)(address + 0xb00);
  LAB_0010dfbc:
    func_0010B338(this, textOrStatus);
    func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c), 0,
                  0);
    selected = 1;
    multipleChoices = 1 < itemCount;
  LAB_0010dfec:
    if (!multipleChoices) {
      selected = 0;
    }
  LAB_0010dff8:
    func_0010B4D8(this, 2);
    return;
  case 0xd:
    if (waiting == '\0') {
      textOrStatus = *(int *)(address + 0xb0c);
      goto LAB_0010dfbc;
    }
    choiceValue = choice;
    profileAddressOrSlot = 1;
    if (choiceValue != 0)
      goto LAB_0010e04c;
    func_0010B5B0(this);
    *(unsigned char *)(D_0040F0E0 + 0x20164) = 0;
    func_00215028(D_0040F0E0 + 0x20258);
    break;
  default:
    goto switchD_0010da38_caseD_e;
  case 0xf:
    textOrStatus = func_0026F4B8(address + 0x9b0);
    func_0010B5B0(this);
    if (true) {
      switch (textOrStatus) {
      case 1:
        overwriteState = 9;
        return;
      case 2:
      case 3:
      case 4:
      case 9:
      case 0xb:
      case 0xc:
        goto LAB_0010e0b0;
      }
    }
    overwriteState = 0xc;
    return;
  case 0x10:
    complete = 1;
    func_0010B5B0(this);
    goto switchD_0010da38_caseD_e;
  }
  overwriteState = 0x10;
switchD_0010da38_caseD_e:
  return;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010D9F0);
#endif

#ifdef NON_MATCHING
// Unmatched: global clock address construction and switch register allocation.
#include "game/frontend/save_dialog.hpp"
extern "C" unsigned char func_0010B610(FrontendSaveDialog*);
extern "C" void func_0010C398(FrontendSaveDialog*);
extern "C" void func_0010E0F0(FrontendSaveDialog*);
extern "C" void func_0010CF18(FrontendSaveDialog*);
extern "C" void func_0010E720(FrontendSaveDialog*);
extern "C" void func_0010C8E8(FrontendSaveDialog*);
extern "C" void func_0010D9F0(FrontendSaveDialog*);
extern "C" void func_0010E498(FrontendSaveDialog*);
extern "C" void func_0010E5F0(FrontendSaveDialog*);
extern "C" void func_0010E740(FrontendSaveDialog*);
extern "C" void func_0010EBD0(FrontendSaveDialog*);
struct FrontendClock {char reserved[0x20];float now;};
extern "C" int D_0040F0E0;
void FrontendSaveDialog::UpdateOperation() {
    if (mode && phase != 1 && !func_0010B610(this)) {
        float now=((FrontendClock*)(D_0040F0E0+0x20120))->now;
        float delta=now-previousTime;
        previousTime=now;
        timeout-=delta;
        if(timeout<0.0f) timeout=0.0f;
        switch(mode) {
        case 1:func_0010C398(this);break;
        case 2:func_0010E0F0(this);break;
        case 3:func_0010CF18(this);break;
        case 9:func_0010E720(this);break;
        case 4:func_0010C8E8(this);break;
        case 5:func_0010D9F0(this);break;
        case 6:func_0010E498(this);break;
        case 7:func_0010E5F0(this);break;
        case 8:func_0010E740(this);break;
        }
        func_0010EBD0(this);
    }
}
#endif

#ifdef NON_MATCHING
// Unmatched: func_0010E0F0: nested switch control flow and callback signatures.
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern char **D_0040F53C;
extern unsigned char D_0048F4D5;
int func_00108A70(...);
int func_0010B238(...);
int func_0010B338(...);
int func_0010B3A8(...);
int func_0010B4D8(...);
int func_0010B530(...);
int func_0010B590(...);
int func_0010B5B0(...);
int func_0010B6B8(...);
int func_00122B10(...);
int func_00124DA8(...);
int func_00215D68(...);
}

void FrontendSaveState::Delete()

{
  bool multipleChoices;
  unsigned char savedFlag;
  int nextStateOrText;
  long result;
  int nextChoice;

  const unsigned address = (unsigned)this;
  switch (deleteState) {
  case 0:
    func_0010B6B8(this);
    func_0010B5B0(this);
    deleteState = 5;
    break;
  case 1:
    func_0010B5B0(this);
    func_0010B3A8(this, 0, 0, 0, 0);
    func_0010B530(this, 0);
    flag514 = 1;
    func_00215D68(D_0040F0E0 + 0x20258, 0x40d988);
    deleteState = 2;
    break;
  case 2:
    if (flag514 == '\0') {
      return;
    }
    if (choice == 0) {
      result = func_0010B590(this);
      savedFlag = D_0048F4D5;
      if (result != 1) {
        nextChoice = choice;
        goto LAB_0010e244;
      }
      func_00108A70(D_0040F0E0 + 0x2014c);
      func_00124DA8(*(int *)(D_0040F0E0 + 0x21060),
                    *(unsigned char *)(D_0040F0E0 + 0x20170));
      func_00122B10(*D_0040F53C);
      D_0048F4D5 = savedFlag;
      activeSlot = 0xffffffff;
      func_0010B5B0(this);
      nextStateOrText = 6;
    } else {
      nextChoice = choice;
    LAB_0010e244:
      if (nextChoice != 1) {
        if (nextChoice == 2) {
          deleteState = 1;
          return;
        }
        return;
      }
      func_0010B5B0(this);
      nextStateOrText = 9;
    }
    flag514 = 0;
    deleteState = nextStateOrText;
    break;
  case 3:
    func_0010B238(this);
    deleteState = 4;
    break;
  case 5:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xb1c));
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 1;
      multipleChoices = 1 < itemCount;
      goto LAB_0010e410;
    }
    nextChoice = choice;
    if (nextChoice == 0) {
      func_0010B5B0(this);
      deleteState = 1;
      return;
    }
    goto LAB_0010e44c;
  case 6:
    if (waiting != '\0') {
      if (choice != 0) {
        if (choice == 1) {
          func_0010B5B0(this);
          deleteState = 7;
          return;
        }
        return;
      }
      *(unsigned char *)(D_0040F0E0 + 0x20164) = 1;
    LAB_0010e438:
      func_0010B5B0(this);
      deleteState = 3;
      return;
    }
    nextStateOrText = *(int *)(address + 0xb20);
  LAB_0010e3e4:
    func_0010B338(this, nextStateOrText);
    func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c), 0,
                  0);
    selected = 0;
    multipleChoices = 0 < itemCount;
  LAB_0010e410:
    if (!multipleChoices) {
      selected = 0;
    }
    func_0010B4D8(this, 2);
    return;
  case 7:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xb24));
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 1;
      multipleChoices = 1 < itemCount;
      goto LAB_0010e410;
    }
    if (choice == 0) {
      *(unsigned char *)(D_0040F0E0 + 0x20164) = 0;
      func_0010B5B0(this);
      deleteState = 8;
    } else {
      if (choice != 1) {
        return;
      }
      func_0010B5B0(this);
      deleteState = 6;
    }
    break;
  case 8:
    if (waiting == '\0') {
      nextStateOrText = *(int *)(address + 0xaf0);
      goto LAB_0010e3e4;
    }
    nextChoice = choice;
    if (nextChoice == 0)
      goto LAB_0010e438;
  LAB_0010e44c:
    if (nextChoice != 1) {
      return;
    }
    func_0010B5B0(this);
    deleteState = 9;
    break;
  case 9:
    complete = 1;
    func_0010B5B0(this);
  }
  return;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E0F0);
#endif

#ifdef NON_MATCHING
// Unmatched: func_0010E498: two instructions in the item-count comparison.
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern char *D_0040F4EC;
int func_0010B338(FrontendSaveState *, const char *);
void func_0010B3A8(FrontendSaveState *, const char *, const char *,
                   const char *, const char *);
int func_0010B4D8(FrontendSaveState *, int);
void func_0010B5B0(FrontendSaveState *);
void func_00215028(void *);
}
void FrontendSaveState::Enable() {
  switch (enableState) {
  case 0:
    if (((unsigned char *)D_0040F0E0)[0x20164] != 1) {
      func_0010B5B0(this);
      enableState = 1;
      break;
    }
    enableState = 2;
    break;
  case 1:
    if (!waiting) {
      func_0010B338(this, text[34]);
      func_0010B3A8(this, text[43], text[44], 0, 0);
      selected = 1;
      if (itemCount <= 1)
        selected = 0;
      func_0010B4D8(this, 2);
      break;
    }
    if (choice == 0) {
      ((unsigned char *)D_0040F0E0)[0x20164] = 1;
      func_00215028(D_0040F0E0 + 0x20258);
      if (D_0040F4EC[8]) {
        func_0010B5B0(this);
        saveState = 0;
        mode = 3;
        break;
      }
    } else if (choice != 1)
      break;
    enableState = 2;
    break;
  case 2:
    complete = 1;
    func_0010B5B0(this);
    break;
  }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E498);
#endif

#ifdef NON_MATCHING
// Unmatched: func_0010E5F0: two instructions in the item-count comparison.
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern char *D_0040F4EC;
int func_0010B338(FrontendSaveState *, const char *);
void func_0010B3A8(FrontendSaveState *, const char *, const char *,
                   const char *, const char *);
int func_0010B4D8(FrontendSaveState *, int);
void func_0010B5B0(FrontendSaveState *);
void func_00215028(void *);
}
void FrontendSaveState::Disable() {
  switch (disableState) {
  case 0:
    if (((unsigned char *)D_0040F0E0)[0x20164] != 0) {
      func_0010B5B0(this);
      disableState = 1;
      break;
    }
    disableState = 2;
    break;
  case 1:
    if (!waiting) {
      func_0010B338(this, text[35]);
      func_0010B3A8(this, text[43], text[44], 0, 0);
      selected = 1;
      if (itemCount <= 1)
        selected = 0;
      func_0010B4D8(this, 2);
      break;
    }
    if (choice == 0) {
      ((unsigned char *)D_0040F0E0)[0x20164] = 0;
      func_00215028(D_0040F0E0 + 0x20258);
    } else if (choice != 1)
      break;
    disableState = 2;
    break;
  case 2:
    complete = 1;
    func_0010B5B0(this);
    break;
  }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E5F0);
#endif

#ifdef NON_MATCHING
// Unmatched: func_0010E740: nested switch control flow and callback signatures.
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern char **D_0040F53C;
int func_0010B238(...);
int func_0010B338(...);
int func_0010B3A8(...);
int func_0010B4D8(...);
int func_0010B530(...);
int func_0010B590(...);
int func_0010B5B0(...);
int func_0010B6B8(...);
int func_00215D68(...);
}

void FrontendSaveState::Format()

{
  int textOrStatus;
  bool multipleChoices;
  long result;
  int nextChoice;

  const unsigned address = (unsigned)this;
  switch (formatState) {
  case 0:
    func_0010B6B8(this);
    goto LAB_0010e784;
  case 1:
    func_0010B5B0(this);
    func_0010B3A8(this, 0, 0, 0, 0);
    func_0010B530(this, 0);
    flag514 = 1;
    func_00215D68(D_0040F0E0 + 0x20258, *D_0040F53C + 8);
    formatState = 2;
    break;
  case 2:
    if (flag514 == '\0') {
      return;
    }
    if (choice == 0) {
      result = func_0010B590(this);
      if (result == 1) {
        activeSlot = 0xffffffff;
        func_0010B5B0(this);
        flag514 = 0;
        formatState = 5;
        return;
      }
      nextChoice = choice;
    } else {
      nextChoice = choice;
    }
    if (nextChoice != 1) {
      if (nextChoice == 2) {
        formatState = 1;
        return;
      }
      return;
    }
    func_0010B5B0(this);
    flag514 = 0;
    if (saveState == 3) {
      saveState = 0x17;
      formatState = 9;
      return;
    }
    goto LAB_0010e93c;
  case 3:
    func_0010B238(this);
    formatState = 4;
    break;
  case 5:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xb20));
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 0;
      multipleChoices = 0 < itemCount;
      goto LAB_0010ea18;
    }
    if (choice != 0) {
      if (choice == 1) {
        func_0010B5B0(this);
        formatState = 6;
        return;
      }
      return;
    }
    *(unsigned char *)(D_0040F0E0 + 0x20164) = 1;
    goto LAB_0010ea54;
  case 6:
    if (waiting == '\0') {
      textOrStatus = *(int *)(address + 0xb24);
    LAB_0010e9e8:
      func_0010B338(this, textOrStatus);
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 1;
      multipleChoices = 1 < itemCount;
    LAB_0010ea18:
      if (!multipleChoices) {
        selected = 0;
      }
      func_0010B4D8(this, 2);
      return;
    }
    if (choice != 0) {
      if (choice == 1) {
        func_0010B5B0(this);
        formatState = 5;
        return;
      }
      return;
    }
    *(unsigned char *)(D_0040F0E0 + 0x20164) = 0;
  LAB_0010ea54:
    func_0010B5B0(this);
    formatState = 3;
    break;
  case 7:
    if (waiting == '\0') {
      func_0010B338(this, *(int *)(address + 0xaf0));
      func_0010B3A8(this, *(int *)(address + 0xb38), *(int *)(address + 0xb3c),
                    0, 0);
      selected = 0;
      multipleChoices = 0 < itemCount;
      goto LAB_0010ea18;
    }
    if (choice == 0) {
      func_0010B5B0(this);
      formatState = 1;
    } else {
      if (choice != 1) {
        return;
      }
      func_0010B5B0(this);
      formatState = 8;
    }
    break;
  case 8:
    if (waiting == '\0') {
      textOrStatus = *(int *)(address + 0xaf4);
      goto LAB_0010e9e8;
    }
    if (choice == 0) {
      func_0010B5B0(this);
      formatState = 9;
      return;
    }
    if (choice != 1) {
      return;
    }
  LAB_0010e784:
    func_0010B5B0(this);
  LAB_0010e93c:
    formatState = 7;
    break;
  case 9:
    complete = 1;
    func_0010B5B0(this);
  }
  return;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E740);
#endif

#ifdef NON_MATCHING
// Unmatched: func_0010EAF8: helper return-register liveness and branch
// scheduling.
#include "game/frontend_resources.hpp"
extern "C" {
int func_0010B8E8(FrontendSaveState *);
void func_0010B160(FrontendSaveState *);
}
int FrontendSaveState::Wait() {
  if (timer > 0 && !waiting && (events & 0xffffffff0000UL)) {
    int current = operation;
    if (current < 31)
      return 0;
    if (current > 31)
      return 0;
    if (func_0010B8E8(this) != 1)
      return 0;
    operation = 32;
    return 0;
  }
  int current = operation;
  if (current < 31)
    return 0;
  if (current < 32)
    func_0010B160(this);
  return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010EAF8);
#endif
