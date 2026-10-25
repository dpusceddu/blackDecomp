#include "include_asm.h"
#include "ps2/prelude.h"

s64 func_001EC768(void *arg0) {
    return *M2C_FIELD(arg0, s64 **, 0x1E10);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ec768", func_001EC778);
