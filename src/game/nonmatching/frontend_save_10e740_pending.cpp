// Unmatched: func_0010E740: nested switch control flow and callback signatures.
#ifdef NONMATCHING
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
#endif
