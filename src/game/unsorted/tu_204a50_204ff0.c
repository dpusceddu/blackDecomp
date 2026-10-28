#include "include_asm.h"
#include "ps2/prelude.h"

void func_00204FF0(void* arg0, void* manager) {
    M2C_FIELD(arg0, void**, 8) = manager;
    M2C_FIELD(arg0, s8*, 0x12) = 0;
    M2C_FIELD(arg0, s32*, 0) = 0;
}

#ifdef NON_MATCHING
extern s32 func_00204FB0(void*, void*, s32, s32, s32);
extern s32 func_002761E8(void*, const void*, const void*, s128);
// Unmatched: constructor argument setup and instruction scheduling differ.
s32 func_00205000(void* self, s32 index, s32 first, s32 last) {
    if (M2C_FIELD(self, u8*, 0x12) == 0) {
        f32 position[2] __attribute__((aligned(16)));
        f32 scale[2] __attribute__((aligned(16)));
        union {
            f32 lanes[4];
            s128 bits;
        } color;
        M2C_FIELD(self, s16*, 0x10) = index;
        func_00204FB0(M2C_FIELD(self, void**, 8), self, index, first, last + 1);
        position[0] = 0.0f;
        position[1] = 0.0f;
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        color.lanes[0] = 1.0f;
        color.lanes[1] = 1.0f;
        color.lanes[2] = 1.0f;
        color.lanes[3] = 1.0f;
        M2C_FIELD(self, s32*, 0xC) =
            func_002761E8(M2C_FIELD(M2C_FIELD(self, void**, 8), void**, 0x14), position, scale, color.bits);
        M2C_FIELD(self, u8*, 0x12) = 1;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_204ff0", func_00205000);
#endif
