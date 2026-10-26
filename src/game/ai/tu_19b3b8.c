#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00193980();
extern s32 func_0019B6D8();
extern s32 func_00193988();
extern s32 func_00181028();
extern void func_00180FE0(void *);
extern void func_001880D8(void *);
extern s32 func_00188F10(void *);
extern u8 func_0018D608(void *);
extern s32 func_00185F00(void *);
extern s16 func_001580E0(void *);
extern void func_0019B638(void *);
extern s32 func_00185F18(void *);

s32 func_0019B3B8(s32 arg0) {
    void **temp_16;

    temp_16 = arg0;
    func_00193980();
    M2C_FIELD(M2C_FIELD(*temp_16, void **, 0x694), s8 *, 0x35) = 1;
    return func_0019B6D8((s32) temp_16);
}

void func_0019B3F8(void **arg0)
{
  s8 *new_var;
  void *temp_3;
  func_00193988();
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    temp_3 = (*arg0) + 0x140;
    func_00180FE0(temp_3);
  }
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
}

// Unmatched: 0019B458: switch dispatch and shared exit scheduling.
#ifdef NON_MATCHING
void func_0019B458(void **action, s32 event, s32 value) {
    u32 next;
    switch (event) {
    case 0x3B:
        if (value != 0) {
    case 3:
            func_0019B6D8(action, event);
            return;
        }
        goto complete;
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
        if (func_001580E0(M2C_FIELD(M2C_FIELD(*action, void **, 0x7C), void **, 0x2A4)) < 3 || value != 0) {
            func_0019B638(action);
            return;
        }
        if (func_00188F10((u8 *) *action + 0x150)) {
            next = 0x3B;
            goto transition;
        }
        goto complete;
    case 0xF:
        if (func_00188F10((u8 *) *action + 0x150)) {
            next = func_00185F18((u8 *) *action + 0x90) ? 0x14 : 0x3B;
            goto transition;
        }
complete:
        func_00193990((RecoveredAIActionHeader *) action, 1);
        return;
    case 0xA:
        next = 3;
transition:
        func_00193A28((RecoveredAIActionHeader *) action, next, 0);
        return;
    case 7:
    case 8:
    case 0xD:
    case 0x16:
    case 0x1A:
        func_0019B6D8(action, event);
        return;
    default:
        return;
    }
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19b3b8", func_0019B458);
s32 func_0019B580(void **action, s32 *event) {
    s32 type = *event;
    if (type == 4) goto alert;
    if (type < 5) {
        if (type == 3) goto check_target;
        return 0;
    }
    if (type != 0x13) return 0;
alert:
    if (func_0018D608((u8 *) *action + 0xD10) &&
        func_00185F00((u8 *) *action + 0x90)) {
        func_00193A28((RecoveredAIActionHeader *) action, 0x1A, 0);
    }
    return 0;
check_target:
    if (func_00188F10((u8 *) *action + 0x150) == 0) {
        func_00193990((RecoveredAIActionHeader *) action, 1);
    }
    return 0;
}
