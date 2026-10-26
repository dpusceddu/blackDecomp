#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_0017B358(void *);
extern void func_00181AD0(void *, s32);
extern void func_00173690(f32 *);

f32 func_00180A30(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x100), f32 *, 0x10);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_180a30", func_00180A40);
void func_00180A48(void *state, s128 position, u32 value) {
    M2C_FIELD(state, u32 *, 0x74) = value;
    M2C_FIELD(state, u8 *, 0x70) = 1;
    M2C_FIELD(state, s128 *, 0) = position;
    func_0017B358((s8 *) state + 0x110);
    func_00181AD0((void *) (M2C_FIELD(state, s32 *, 0x140) + 0xEC0), 5);
    func_00173690((f32 *) ((s8 *) state + 0x148));
    M2C_FIELD(state, u8 *, 0x14D) = 0;
    M2C_FIELD(state, u8 *, 0x14F) = 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_180a30", func_00180AA0);
