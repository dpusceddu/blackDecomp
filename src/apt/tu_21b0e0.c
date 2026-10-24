#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00250058(void *, s32);
extern void * D_0043DEE0;
extern s32 func_002519D0(void *);

s32 func_0021B0E0(void *arg0, void *arg1) {
    s32 temp_5;
    s32 temp_5_2;
    s32 temp_5_3;
    s32 temp_5_4;
    void *temp_19;
    void *temp_20;
    void *temp_21;

    temp_19 = (void *) (((s8 *) arg0) + 0xC);
    temp_20 = (void *) (((s8 *) arg0) + 0x18);
    temp_21 = (void *) (((s8 *) arg0) + 0x24);
    temp_5 = M2C_FIELD(arg1, s32 *, 0x20);
    M2C_FIELD(arg0, s32 *, 4) = temp_5;
    M2C_FIELD(arg0, s32 *, 8) = func_00250058(D_0043DEE0, temp_5 * 4);
    temp_5_2 = M2C_FIELD(arg1, s32 *, 0x24);
    M2C_FIELD(temp_19, s32 *, 4) = temp_5_2;
    M2C_FIELD(temp_19, s32 *, 8) = func_00250058(D_0043DEE0, temp_5_2 * 4);
    temp_5_3 = M2C_FIELD(arg1, s32 *, 0x24);
    M2C_FIELD(temp_20, s32 *, 4) = temp_5_3;
    M2C_FIELD(temp_20, s32 *, 8) = func_00250058(D_0043DEE0, temp_5_3 * 4);
    temp_5_4 = M2C_FIELD(arg1, s32 *, 0x24);
    M2C_FIELD(temp_21, s32 *, 4) = temp_5_4;
    M2C_FIELD(temp_21, s32 *, 8) = func_00250058(D_0043DEE0, temp_5_4 * 4);
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    M2C_FIELD(arg0, s8 *, 0x5C) = 0;
    return func_002519D0(arg1);
}
