#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern void ** D_003C87E8;
extern s32 (*D_003C87EC)();
extern s32 * func_0035C544(s32 *, s32, s32);

void * func_002DF9B8(void *arg0, void *arg1) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 temp_16;
    s32 temp_6;
    void *temp_3;

    if (arg0 != arg1) {
        temp_16 = M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(arg0, s32 *, 8) = temp_16;
        if (temp_16 != 0) {
            *(s32 * *)(sp + 0) = NULL;
            temp_3 = *D_003C87E8;
            temp_6 = M2C_FIELD(temp_3, s32 (**)(void *, s32, void *, void **), 0x34)((void *) (((s8 *) D_003C87E8) + M2C_FIELD(temp_3, s16 *, 0x30)), temp_16, sp, D_003C87E8);
            if (D_003C87EC != NULL) {
                D_003C87EC(*(s32 * *)(sp + 0), temp_16, temp_6);
            }
            M2C_FIELD(arg0, s32 **, 4) = *(s32 * *)(sp + 0);
            func_0035C544(*(s32 * *)(sp + 0), M2C_FIELD(arg1, s32 *, 4), M2C_FIELD(arg0, s32 *, 8));
        } else {
            M2C_FIELD(arg0, s32 **, 4) = NULL;
        }
    }
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002DFA68);
