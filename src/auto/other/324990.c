#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_003248A8();
extern s8 * func_0035CBC0(s8 *, s32);
extern s32 * D_0040E258;
extern s32 * D_0040E264;
extern s32 * func_003680A0(s32 *, s32);
extern void * func_003242B0(s32 *, s32 *, s32, s32, s32, s32, s32 *, s32);
extern s32 D_0040E7F0;

s32 func_00324990(s8 *arg0) {
    s32 temp_2;

    temp_2 = func_003248A8();
    func_0035CBC0((s8 *) (((s8 *) ((void *) (((s8 *) D_0040E258) + ((temp_2 - 1) * 0x70)))) + 0x24), (s32) arg0);
    return temp_2;
}

void * func_003249E8(s32 arg0) {
    s32 *temp_16;
    s32 temp_17;
    s32 temp_18;
    void *temp_2;

    temp_17 = arg0 - 1;
    temp_18 = temp_17 * 0x70;
    temp_2 = (void *) (((s8 *) D_0040E264) + (temp_17 * 0x14));
    temp_16 = (s32 *) (((s8 *) D_0040E258) + temp_18);
    M2C_FIELD(temp_2, s32 *, 4) = arg0;
    M2C_FIELD(temp_2, s32 *, 8) = 3;
    M2C_FIELD(temp_2, s32 *, 0x10) = 0;
    M2C_FIELD(temp_16, s32 *, 0) = temp_17;
    M2C_FIELD(temp_16, s32 *, 0x10) = 1;
    func_003680A0(temp_16, (s32) ((void *) (((s8 *) temp_16) + 0x6F)));
    return func_003242B0(D_0040E7F0 + temp_18, temp_16, 0x70, 0x32, 0, 0, (s32 *) temp_17, 0);
}
