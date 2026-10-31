#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00193980(void*, void*);
extern void func_0018D610(void*);
extern void* func_00193B98(void*);
extern void func_001A7188(void*);
extern void func_001A0A30(void*);

void func_001A0820(void* arg0, void* arg1) {
    func_00193980(arg0, arg1);
    func_0018D610(M2C_FIELD(arg0, s32*, 0) + 0xD10);
    M2C_FIELD(func_00193B98(arg0), s32*, 0x84) = 0;
    M2C_FIELD(arg0, s32*, 8) = 0;
    func_001A7188(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32*, 0), void**, 0x7C), void**, 0x330));
    M2C_FIELD(M2C_FIELD(arg0, s32*, 0), s8*, 0x104) = 1;
    M2C_FIELD(M2C_FIELD(arg0, s32*, 0), s8*, 0x110) = 1;
    M2C_FIELD(func_00193B98(arg0), s32*, 0x44) = 0;
    M2C_FIELD(func_00193B98(arg0), s32*, 0x40) = 0;
    M2C_FIELD(func_00193B98(arg0), f32*, 0x3C) = 2.0f;
    M2C_FIELD(func_00193B98(arg0), s32*, 0x60) = 0;
    M2C_FIELD(func_00193B98(arg0), s32*, 0x68) = 0;
    M2C_FIELD(func_00193B98(arg0), f32*, 0x5C) = 2.0f;
    func_001A0A30(arg0);
}

void func_001A08E8(void* self) { func_001A0A30(self); }

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a0820", func_001A0908);
