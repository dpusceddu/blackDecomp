#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_00122900();
extern s32 D_0040F4E8;
extern void * D_0040F0E0;
extern s32 func_0012FB48();
extern s32 D_0040F4D0;
extern s32 func_0012F880();
extern s32 func_0020DEC8();
extern M2C_UNK D_00492638;
extern s32 func_001087C8();
extern s32 D_0040F4C4;
extern M2C_UNK D_003FC250;

void func_00217408(void) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 temp_18;
    s32 temp_20;

    temp_18 = func_00122900(D_0040F4E8, M2C_FIELD(D_0040F0E0, u8 *, 0x2020C));
    *(s32 *)(sp + 0) = 0;
    temp_20 = func_0012FB48(D_0040F4D0 + 0x910, temp_18, M2C_FIELD(D_0040F0E0, s32 *, 0x2014C));
    func_0012F880(D_0040F4D0 + 0x910, temp_18, M2C_FIELD(D_0040F0E0, s32 *, 0x2014C), sp);
    func_0020DEC8(&D_00492638, func_001087C8(D_0040F4C4, &D_003FC250), *(s32 *)(sp + 0), temp_20);
}
