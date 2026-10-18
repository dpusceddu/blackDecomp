/* Translation unit kynapse/tu_2e5358 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_002E5358();
extern M2C_UNK D_003E9BB0;
extern s8 D_004513C8;
extern M2C_UNK D_003E9C08;
extern s32 func_002E5AE8();
extern M2C_UNK D_003E9A98;
extern M2C_UNK D_003E9AF0;
extern s32 func_002E5E58();

s32 func_002E5848(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002E5358(arg0, arg1);
    M2C_FIELD(arg0, s32 *, 0x10) = arg2;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) arg3;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E9BB0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    return arg0;
}

/* Assembly between the functions: func_002E58A0 (584 bytes), func_002E5AE8 (336 bytes), func_002E5C38 (344 bytes), func_002E5D90 (200 bytes), func_002E5E58 (352 bytes), func_002E5FB8 (1928 bytes), func_002E6740 (680 bytes), func_002E69E8 (376 bytes), func_002E6B60 (400 bytes) */

void func_002E6CF0(s32 arg0, s32 arg1) {
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        D_004513C8 = 0;
    }
}

/* Assembly between the functions: func_002E6D10 (128 bytes) */

s32 func_002E6D90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    func_002E5358(arg0, arg2);
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E9C08;
    return arg0;
}

/* Assembly between the functions: func_002E6DD8 (136 bytes), func_002E6E60 (176 bytes), func_002E6F10 (128 bytes) */

void func_002E6F90(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x10)(arg1);
}

void * func_002E6FB0(void *arg0, s32 arg1) {
    void *temp_3;
    void *var_2;

    temp_3 = M2C_FIELD(arg0, void **, 0);
    var_2 = M2C_FIELD(temp_3, void *(**)(void *), 0x1C)(arg0 + M2C_FIELD(temp_3, s16 *, 0x18));
    if (var_2 == NULL) {
        M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x14)(arg1);
        var_2 = arg0;
    }
    return var_2;
}

void func_002E7008(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x14)(arg1);
}

/* Assembly between the functions: func_002E7028 (96 bytes) */

void func_002E7088(void) {

}

/* Assembly between the functions: func_002E7090 (96 bytes) */

s32 func_002E70F0(s32 arg0, s32 arg1) {
    func_002E5AE8(arg0, M2C_FIELD(arg1, s32 *, 0xC), arg1 + 0x10, 0);
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E9A98;
    M2C_FIELD(arg0, M2C_UNK **, 0x28) = &D_003E9AF0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    return arg0;
}

/* Assembly between the functions: func_002E7158 (136 bytes) */

s32 func_002E71E0(void *arg0) {
    s32 temp_2;

    temp_2 = func_002E5E58();
    if (temp_2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + 1);
    }
    return temp_2;
}

/* Assembly between the functions: func_002E7220 (176 bytes) */

void func_002E72D0(void) {
    func_002E6CF0(1, 0xFFFF);
}
