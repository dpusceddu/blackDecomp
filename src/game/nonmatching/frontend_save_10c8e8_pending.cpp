// Unmatched: func_0010C8E8: profile aggregate copy allocation and state/callee
// types.
#ifdef NONMATCHING
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
#endif
