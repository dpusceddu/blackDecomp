#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00311278(s32, void *);
extern s32 func_00311498(void *, void *);

s32 func_00311248(void *arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    *(void * *)(sp + 0) = arg0;
    *(s32 *)(sp + 4) = 0;
    func_00311278((s32) func_00311498, sp);
    return *(s32 *)(sp + 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311248", func_00311278);

s32 func_003112E0(s32 *arg0, void *arg1) {
    if (*arg0 == M2C_FIELD(arg1, s32 *, 4)) {
        M2C_FIELD(arg1, s32 **, 0) = arg0;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311248", func_00311300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_310978_311248", func_00311398);
