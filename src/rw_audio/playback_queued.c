#include "include_asm.h"

#include "rw_audio/voice.h"

void *func_0031CCE8(void *state, s32 *queued) {
    s32 bytes = M2C_FIELD(state, s32 *, 0x70);
    if (bytes) {
        *queued = 1;
        return state;
    }
    *queued = 0;
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0031CE50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0031CE58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0031CEC8);
