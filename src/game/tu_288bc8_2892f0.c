#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00288E28();
extern s32 func_00289028();
extern s32 func_00288FB0();
extern void * func_0035E7D8(M2C_UNK);
extern s32 func_002F4A48();
extern M2C_UNK D_003E28D8;

s32 func_002892F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[24] __attribute__((aligned(16)));

    func_00288E28((s32) sp, arg1 + 0x10, arg2, 0, (s32) "Periodic", 1);
    func_00289028((s32) (sp + 16), (s32) sp, (s32) "Period", arg3);
    M2C_FIELD(arg0, s32 *, 0) = *(s32 *)(sp + 0);
    return arg0;
}

s32 func_00289360(s32 arg0, s32 arg1, s32 arg2) {
    func_00288FB0(arg0, arg1 + 0x28, arg2);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289390);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289398);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002895E0);

void func_00289660(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x6C) = 0x7F;
    M2C_FIELD(arg0, void **, 0x60) = func_0035E7D8(0x7F0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002897D8);

void func_00289948(void) {

}

M2C_UNK ** func_00289950(M2C_UNK **arg0) {
    func_002F4A48();
    *arg0 = &D_003E28D8;
    return arg0;
}

s32 func_00289988(void) {
    return 1;
}

s32 func_00289990(void) {
    return 0;
}

s32 func_00289998(void) {
    return 0;
}
