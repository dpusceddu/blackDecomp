#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_003D81C0;

void * func_0036DFB8(void *arg0) {
    void **temp_2;
    void *temp_3;

    temp_2 = M2C_FIELD(arg0, void ***, 4);
    temp_3 = M2C_FIELD(arg0, void **, 0);
    if (temp_2 != NULL) {
        *temp_2 = temp_3;
    } else {
        D_003D81C0 = temp_3;
    }
    if (temp_3 != NULL) {
        M2C_FIELD(temp_3, void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 4);
    }
    M2C_FIELD(arg0, void ***, 4) = NULL;
    return temp_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36dfb8", func_0036DFF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36dfb8", func_0036E298);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36dfb8", func_0036E2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36db08_36dfb8", func_0036E2F0);
