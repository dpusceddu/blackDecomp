#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0011D430();

void func_0011EA40(void) {

}

s32 func_0011EA48(s32 arg0) {
    return func_0011D430(arg0, 6);
}

#include "game/animation_action.h"
extern void* func_0011D498(void*);
extern s64 func_001A7DF0(void*, s32, s32);
extern u8 func_00135CC8(void*);
extern void func_001A6330(void*, const Recovered_AnimationAction*);
extern void func_001412E8(void*, s32);
void func_0011EA68(void* self) {
    Recovered_AnimationAction action;
    void* actor = func_0011D498(self);
    if (func_001A7DF0(M2C_FIELD(actor, void**, 0x330), 0, 7) == 2) {
        action.key = 4;
        action.value = 1.0f;
        action.mode = 0xB;
        action.kind = 1;
        action.flag = func_00135CC8(actor);
        func_001A6330(M2C_FIELD(actor, void**, 0x330), &action);
        func_001412E8(M2C_FIELD(self, void**, 0), 8);
        M2C_FIELD(self, u8*, 0x48) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358_11ea40", func_0011EB08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358_11ea40", func_0011EB88);
