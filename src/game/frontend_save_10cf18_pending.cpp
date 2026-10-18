// Unmatched: func_0010CF18: profile/IO types, register allocation and state
// control flow.
#ifdef NONMATCHING
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
#endif
