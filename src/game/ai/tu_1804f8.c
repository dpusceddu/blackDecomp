#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001806D0();
extern s32 func_001808D0();
extern s32 func_001808D8();
extern void func_001809C8();
extern s32 func_00180CD8();
extern s32 func_00173640(void *, f32);
extern void func_0017B358(void *);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8", func_001804F8);

void func_00180610(void *arg0) {
    func_001806D0();
    func_001808D0(arg0);
    func_001808D8(arg0);
    func_001809C8(arg0);
    if ((M2C_FIELD(arg0, u8 *, 0x14C) != 0) && (func_00180CD8(arg0) == 0)) {
        func_00173640(arg0 + 0x148, 1.0f);
    }
}

// Unmatched: 00180678: short-loop assembler NOP and setup scheduling.
#ifdef NON_MATCHING
void func_00180678(void *state) {
    u8 *channel;
    s32 count;
    count = 1;
    channel = state;
    do {
        M2C_FIELD(channel, s32 *, 0x18) = 0;
        count--;
        M2C_FIELD(channel, u8 *, 0x70) = 1;
        M2C_FIELD(channel, u8 *, 0x71) = 0;
        channel += 0x80;
    } while (count >= 0);
    func_0017B358((u8 *) state + 0x110);
    M2C_FIELD(state, u8 *, 0x14F) = 0;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8", func_00180678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8", func_001806D0);
