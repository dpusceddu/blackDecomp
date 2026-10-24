#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_0027F6D8(void *arg0) {
    void *temp_2;

    temp_2 = (void *) (((u32) arg0) + ((u32) M2C_FIELD(arg0, void **, 0)));
    M2C_FIELD(arg0, void **, 0) = temp_2;
    M2C_FIELD(arg0, void **, 4) = (void *) ((void *) (((u32) arg0) + ((u32) M2C_FIELD(arg0, void **, 4))));
    return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027F6F8);

#include "ps2/recovered_types.h"

s32 func_0027F708(void *arg0) {
    void *temp_2;

    temp_2 = (void *) (((u32) arg0) + ((u32) M2C_FIELD(arg0, void **, 0)));
    M2C_FIELD(arg0, void **, 0) = temp_2;
    M2C_FIELD(arg0, void **, 4) = (void *) ((void *) (((u32) arg0) + ((u32) M2C_FIELD(arg0, void **, 4))));
    return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027F728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027F730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027F778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027F790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027F7D0);
