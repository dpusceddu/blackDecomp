#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_0035E7D8(void *);
extern s32 func_00107A08(s8 *, s32 *, s32, s32 *);
extern s32 func_00107A40(void *);

s32 func_00125208(void *arg0) {
    s32 *temp_16;
    s32 *temp_2;
    s32 temp_18;

    M2C_FIELD(arg0, s32 *, 0x3B0) = -1;
    temp_2 = func_0035E7D8((void *)0x01A883FF);
    M2C_FIELD(arg0, s32 **, 0x3BC) = temp_2;
    if (temp_2 == NULL) {
        M2C_FIELD(arg0, u8 *, 0x3C4) = 1U;
        M2C_FIELD(arg0, s32 **, 0x3BC) = func_0035E7D8((void *)0x019883FF);
    } else {
        M2C_FIELD(arg0, u8 *, 0x3C4) = 0U;
    }
    temp_18 = (s32) ((void *) (((s8 *) M2C_FIELD(arg0, s32 **, 0x3BC)) + 0x7FF)) & 0xFFFFF800;
    M2C_FIELD(arg0, s32 *, 0x3C0) = temp_18;
    func_00107A08((s8 *) (((s8 *) arg0) + 4), (s32 *) temp_18, -1, (s32 *)0x283000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x28), temp_18 + 0x01258400, -1, (s32 *)0x16B000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x4C), temp_18 + 0x283000, -1, (s32 *)0x934000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x70), temp_18 + 0xBB7000, -1, (s32 *)0x113000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x94), temp_18 + 0xCCA000, -1, (s32 *)0xC1800);
    func_00107A08((s8 *) (((s8 *) arg0) + 0xB8), temp_18 + 0xD8B800, -1, (s32 *)0x4800);
    func_00107A08((s8 *) (((s8 *) arg0) + 0xDC), temp_18 + 0xD90000, -1, (s32 *)0x110000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x100), temp_18 + 0xEA0000, -1, (s32 *)0xD6400);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x124), temp_18 + 0xF76400, -1, (s32 *)0x2E1800);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x1D8), temp_18 + 0x01586400, -1, (s32 *)0xB2000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x1FC), temp_18 + 0x01638400, -1, (s32 *)0xB2000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x16C), temp_18 + 0x01257C00, -1, (s32 *)0x800);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x220), temp_18 + 0x016EA400, -1, (s32 *)0x113400);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x148), temp_18 + 0x013C3400, -1, (s32 *)0x28800);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x190), temp_18 + 0x013EBC00, -1, (s32 *)0xAC800);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x1B4), temp_18 + 0x01498400, -1, (s32 *)0xEE000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x244), temp_18 + 0x017FDC00, -1, (s32 *)0x800);
    temp_16 = temp_18 + 0x017FE400;
    func_00107A08((s8 *) (((s8 *) arg0) + 0x268), temp_16, -1, NULL);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x2F8), temp_18 + 0x017FD800, -1, (s32 *)0x400);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x2B0), temp_16, -1, (s32 *)0x9000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x364), temp_18 + 0x01807400, -1, (s32 *)0x25800);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x388), temp_18 + 0x0182CC00, -1, (s32 *)0x4B000);
    func_00107A08((s8 *) (((s8 *) arg0) + 0x2D4), temp_18 + 0x01877C00, -1, (s32 *)0x10000);
    if (M2C_FIELD(arg0, u8 *, 0x3C4) != 0) {
        func_00107A08((s8 *) (((s8 *) arg0) + 0x28C), temp_18 + 0x01887C00, -1, (s32 *)0x100000);
    } else {
        func_00107A08((s8 *) (((s8 *) arg0) + 0x28C), temp_18 + 0x01887C00, -1, (s32 *)0x200000);
    }
    return func_00107A40(arg0);
}
