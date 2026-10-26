#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern void func_00188148(void *, s8);
extern void func_00193980(void);
extern void func_0019C330(void *);
extern void func_00173640(f32 *, f32);

void func_0019C298(void **action) {
    u8 *owner;
    u8 *movement;
    func_00193980();
    owner = *action;
    movement = owner + 0x290;
    if (*movement != 0) func_00188148(movement, 1);
    M2C_FIELD(M2C_FIELD(*action, void **, 0x694), u8 *, 0x30) = 0;
    func_0019C330(action);
    func_00173640((f32 *) ((s8 *) action + 8), 2.0f);
}

void func_0019C2F8(s32 *arg0) {
    func_00193988();
    func_00188148(*arg0 + 0x290, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19c298", func_0019C330);
