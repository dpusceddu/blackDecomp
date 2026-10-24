#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0031A9E0();
extern s32 D_0040E1CC;
extern M2C_UNK * D_0040E798;

s32 func_00317868(void) {
    s32 temp_v0;

    temp_v0 = func_0031A9E0();
    D_0040E1CC = 0;
    return temp_v0;
}

s32 func_00317888(void *arg0) {
    M2C_UNK *temp_2;
    M2C_UNK *temp_3;

    temp_3 = arg0 + 0x40;
    M2C_FIELD(temp_3, M2C_UNK ***, 4) = NULL;
    M2C_FIELD(arg0, M2C_UNK **, 0x40) = NULL;
    M2C_FIELD(arg0, M2C_UNK **, 0x40) = (M2C_UNK *) D_0040E798;
    M2C_FIELD(temp_3, M2C_UNK ***, 4) = &D_0040E798;
    temp_2 = D_0040E798;
    M2C_FIELD(temp_2, M2C_UNK **, 4) = temp_3;
    D_0040E798 = temp_3;
    return (s32) temp_2;
}
