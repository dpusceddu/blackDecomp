#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern void func_00188148(void *, s8);
extern void func_0019C7D8(void *);
extern void func_00193980(void);
extern s32 func_00185FE8(void *);
extern s32 func_00187FE0(s32, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19c558", func_0019C558);
void func_0019C6E8(s32 *action) {
    s32 owner;
    u8 *movement;
    func_00193980();
    owner = *action;
    movement = (u8 *) (owner + 0x290);
    if (*movement == 0) {
        func_00187FE0((s32) movement, 0);
    }
    func_00188148((void *) (*action + 0x290), 0);
    M2C_FIELD(M2C_FIELD(*action, void **, 0x694), u8 *, 0x30) = 0;
    M2C_FIELD(action, s128 *, 0x10) = *(s128 *) func_00185FE8((void *) (*action + 0x90));
    func_0019C7D8(action);
}

void func_0019C760(s32 *arg0) {
    func_00193988();
    func_00188148(*arg0 + 0x290, 1);
}

void func_0019C798(s32 *arg0, s32 arg1) {
    if (arg1 == 3) {
        func_0019C7D8(arg0);
        func_00187FE0(*arg0 + 0x290, 0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19c558", func_0019C7D8);
