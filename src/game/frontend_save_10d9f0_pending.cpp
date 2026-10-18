// Unmatched: func_0010D9F0: profile/IO types, register allocation and state
// control flow.
#ifdef NONMATCHING
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
#endif
