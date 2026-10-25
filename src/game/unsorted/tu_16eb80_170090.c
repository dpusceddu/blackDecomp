#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00170680();
extern M2C_UNK D_003DD018;
extern s32 func_002DFE40();
extern M2C_UNK D_0044F7C0;
extern M2C_UNK D_0044F9F0;
extern s32 func_00171A08();
extern M2C_UNK D_003DCF60;
extern s32 func_00171A40();

void * func_00170090(void *arg0) {
    func_00170680();
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003DD018;
    M2C_FIELD(arg0, s32 *, 0xC) = func_002DFE40(arg0, &D_0044F7C0);
    M2C_FIELD(arg0, s32 *, 0x10) = func_002DFE40(arg0, &D_0044F9F0);
    return arg0;
}

void func_001700F0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170090", func_001700F8);

M2C_UNK ** func_00170178(M2C_UNK **arg0) {
    func_00171A08();
    *arg0 = &D_003DCF60;
    return arg0;
}

s32 func_001701B0(void *arg0, void *arg1) {
    return func_00171A40(arg0, arg1) != 0;
}

s32 func_001701D0(void) {
    return 1;
}
