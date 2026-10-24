#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A77D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A77E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A78C0);

#include "ps2/recovered_types.h"
extern void * func_002A7B18(void *, void *, void *);
extern u32 D_0040E5C0;
extern M2C_UNK D_00449438;
extern void * func_002A7930(void *, void *, s32, void *);
extern void * func_002A7D50(void *, void *, void *);
extern void * func_002A7BB0(void *, void *, s32, void *);

s32 func_002A78D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_4;
    s32 var_5;
    s32 var_6;
    s32 var_7;
    void *temp_3;

    var_4 = arg0;
    var_5 = arg1;
    var_6 = arg2;
    var_7 = arg3;
    if (var_4 == 0) {
        var_4 = (s32) func_002A7B18;
    }
    temp_3 = D_0040E5C0 + ((s32) &D_00449438);
    M2C_FIELD(temp_3, s32 *, 8) = var_4;
    if (var_5 == 0) {
        var_5 = (s32) func_002A7930;
    }
    M2C_FIELD(temp_3, s32 *, 0xC) = var_5;
    if (var_6 == 0) {
        var_6 = (s32) func_002A7D50;
    }
    M2C_FIELD(temp_3, s32 *, 0x10) = var_6;
    if (var_7 == 0) {
        var_7 = (s32) func_002A7BB0;
    }
    M2C_FIELD(temp_3, s32 *, 0x14) = var_7;
    return 1;
}
