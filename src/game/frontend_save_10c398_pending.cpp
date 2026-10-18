// Unmatched: func_0010C398: profile aggregate copy allocation and state/callee
// types.
#ifdef NONMATCHING
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
#endif
