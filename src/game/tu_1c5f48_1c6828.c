#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_BkActorRenderPS2.h"
#include "ps2/recovered_types.h"
extern s32 func_001C6FA0(void *, s32);
extern s32 func_001C5F48(s32);
extern Recovered_BkActorRenderPS2 * D_0040F4C0;

s32 func_001C6828(s32 arg0, s32 arg1, s32 arg2) {
    func_001C6FA0((arg1 * 0x38) + arg0, arg2);
    return func_001C5F48((s32) D_0040F4C0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C6860);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C6A68);
