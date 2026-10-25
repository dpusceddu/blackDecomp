#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 D_0040EAE4;
extern s8 D_0040EAD8;
extern s8 D_0040EAE8;
extern s32 func_00108A70(void *);

s32 func_00108A40(void *arg0) {
    D_0040EAE4 = 1;
    D_0040EAD8 = 0;
    D_0040EAE8 = 0;
    return func_00108A70(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_108a40", func_00108A70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_108a40", func_00108BB8);
