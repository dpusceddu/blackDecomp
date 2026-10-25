#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00174218();
extern void func_0017B3C0(void *arg0);
extern s32 func_0017B198();
extern s32 func_00174228();
extern void * func_00174398();
extern u8 func_001743C0();
extern s32 func_00174320();
extern void func_0017B908(void *arg0, void *arg1);
extern void * D_0040F4D4;

s32 func_0017B0E0(s32 arg0) {
    func_00174218();
    func_0017B3C0(arg0 + 0x10);
    return 1;
}

void func_0017B110(void) {
    func_0017B198();
}

s32 func_0017B130(void) {
    return 1;
}

void func_0017B138(void) {
    func_00174228();
}

void * func_0017B158(void *arg0) {
    return func_00174398();
}

u8 func_0017B178(void *arg0, void *arg1) {
    return func_001743C0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/tu_17b0e0", func_0017B198);

void func_0017B220(void) {
    func_00174320();
}

void func_0017B240(s32 arg0) {
    func_0017B3C0(arg0 + 0x10);
}

void func_0017B260(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/tu_17b0e0", func_0017B268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/tu_17b0e0", func_0017B290);

void func_0017B310(void *arg0) {
    if ((u32) (M2C_FIELD(arg0, s32 *, 0x24) - 1) < 2U) {
        func_0017B908(D_0040F4D4 + 0x1290, arg0);
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
    }
}
