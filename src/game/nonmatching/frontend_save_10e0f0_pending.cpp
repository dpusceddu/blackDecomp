// Unmatched: func_0010E0F0: nested switch control flow and callback signatures.
#ifdef NONMATCHING
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
#endif
