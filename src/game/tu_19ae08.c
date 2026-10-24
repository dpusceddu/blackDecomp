/* Translation unit tu_19ae08 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00193980();
extern s32 func_00193B98();
extern s32 func_0019B0C0();
extern s32 func_00193988();

s32 func_0019AE08(s32 arg0) {
    func_00193980();
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x44) = 0.5f;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x4C) = 0;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x50) = 0;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x40) = 2.0f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x3C) = 0.5f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x68) = 0.25f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x64) = 2.0f;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x6C) = 0;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x60) = 0.1f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x5C) = 10.0f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 8) = -10.0f;
    M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), s8 *, 0x104) = 1;
    M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), s8 *, 0x110) = 1;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), void **, 0x694), s8 *, 0x35) = 1;
    return func_0019B0C0(arg0);
}

void func_0019AF20(void) {
    func_00193988();
}

/* Assembly between the functions: func_0019AF40 (176 bytes), func_0019AFF0 (208 bytes), func_0019B0C0 (112 bytes) */

void func_0019B130(void) {
    func_0019B0C0();
}
