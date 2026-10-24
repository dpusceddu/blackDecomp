#include "ps2/prelude.h"
#include "types_ghidra.h"

void * func_003284E0(void *arg0, s32 arg1, s32 *arg2) {
    void *temp_3;
    void *temp_4;

    if (*arg2 != 0) {
        temp_3 = M2C_FIELD(arg0, void **, 0x30);
        M2C_FIELD(temp_3, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_3, s32 *, 0x1C) | 1);
    } else {
        temp_4 = M2C_FIELD(arg0, void **, 0x30);
        M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFFFFFFFE);
    }
    return arg0;
}

s32 func_00328520(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 0x1C) & 1);
    return arg0;
}

void *func_00328538(void *arg0, s32 arg1, void *arg2)
{
  void **new_var;
 do { new_var = (void **) (((s8 *) arg0) + 0x38); if ((*new_var) != NULL) { *(*((s32 **) (((s8 *) arg0) + 0x30))) = 1; if (0) { } } if (arg2 != NULL) { M2C_FIELD(arg0, s32 *, 0xBC) = (s32) ((((s32) (M2C_FIELD(arg2, s32 *, 0x54))) >> 1) & 1); } *((void **) (((s8 *) arg0) + 0x38)) = arg2; M2C_FIELD(arg0, u16 *, 0x5C) = (u16) ((M2C_FIELD(arg0, u16 *, 0x5C)) | 0x40); return arg0; } while (0);
}

s32 func_00328580(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x38);
    return arg0;
}
