#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern f32 func_001181C0(void*, s32);

f32 func_00118158(void* arg0) { return func_001181C0(arg0, M2C_FIELD(arg0, s32*, 0x10)) - M2C_FIELD(arg0, f32*, 8); }

void func_00118188(void* timer, s32 clock, s32 behavior, f32 duration) {
    M2C_FIELD(timer, s32*, 0xC) = behavior;
    M2C_FIELD(timer, f32*, 4) = duration;
    M2C_FIELD(timer, s32*, 0x10) = clock;
    M2C_FIELD(timer, f32*, 8) = func_001181C0(timer, clock);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_118158", func_001181C0);
f32 func_00118210(void* timer) { return func_00118158(timer) / M2C_FIELD(timer, f32*, 4); }
