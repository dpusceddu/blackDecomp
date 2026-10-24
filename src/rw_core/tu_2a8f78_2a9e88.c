#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "rw_core/layouts/Recovered_RwErrorRecordPS2.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 (*D_0044944C)();
extern s32 func_002A5548(s32, ...);
extern Recovered_RwErrorRecordPS2 * func_002A55D8(Recovered_RwErrorRecordPS2 *);

void * func_002A9E88(s32 arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 temp_2;

    temp_2 = D_0044944C(6, (s32 *) arg0, 0, arg1);
    if (temp_2 == 0) {
        *(s32 *)(sp + 0) = 1;
        *(s32 *)(sp + 4) = func_002A5548(0x18, 6);
        func_002A55D8(sp);
    }
    return (void *) ((temp_2 != 0) ? arg0 : 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9F00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A9F08);
