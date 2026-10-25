#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00204F30();
extern s32 func_00206A58();
extern s32 func_00206B88();
extern void * D_0040F0E0;
extern void func_00204F90();
extern s32 func_00206B30(s32);
extern s32 func_00206F08(s32);
extern s32 func_00204FF0();
extern s32 func_002050B0();

s32 func_00205CA0(void *arg0) {
    func_00204F30();
    func_00206A58(arg0 + 0x60);
    func_00206B88(arg0 + 0x88);
    M2C_FIELD(D_0040F0E0, u8 *, 0x2020C) = (u8) M2C_FIELD(((M2C_FIELD(arg0, s8 *, 0xC9) * 0x24) + M2C_FIELD(M2C_FIELD(D_0040F0E0, void **, 0x2106C), s32 *, 4)), u8 *, 0x10);
    M2C_FIELD(D_0040F0E0, s8 *, 0x2020D) = (s8) (M2C_FIELD(arg0, u8 *, 0xCA) + 1);
    M2C_FIELD(D_0040F0E0, s8 *, 0x2020E) = 1;
    M2C_FIELD(arg0, s8 *, 0xC8) = 1;
    M2C_FIELD(arg0, s32 *, 0xCC) = 2;
    M2C_FIELD(arg0, s8 *, 0xD0) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_205ca0", func_00205D40);

void func_002060B8(void) {
    func_00204F90();
}

s32 func_002060D8(s32 arg0) {
    func_00206B30(arg0 + 0x60);
    func_00206F08(arg0 + 0x88);
    return 1;
}

void func_00206110(void) {
    func_00204FF0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_205ca0", func_00206130);

void func_002061E8(void) {

}

s32 func_002061F0(void) {
    func_002050B0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_205ca0", func_00206210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_205ca0", func_00206218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_205ca0", func_00206248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_205ca0", func_002066E0);

s32 func_00206A00(void) {
    func_002050B0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_204a50_205ca0", func_00206A20);
