#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00193980();
extern s32 * func_00193B98();

void func_0019D768(RecoveredAIActionHeader *arg0) {
    func_00193980();
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x34) = -1.0f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x30) = -1.0f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x20) = 1.0f;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x28) = 1.0f;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x5C) = 0;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x60) = 2.5f;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x6C) = 0;
    M2C_FIELD(func_00193B98(arg0), s32 *, 0x70) = 0;
    M2C_FIELD(func_00193B98(arg0), f32 *, 0x74) = 1.0f;
    M2C_FIELD(func_00193B98(arg0), s32 *, 4) = 0;
    *func_00193B98(arg0) = 1;
    M2C_FIELD(arg0->brain, s8 *, 0x104) = 0;
    M2C_FIELD(arg0->brain, s8 *, 0x110) = 1;
    M2C_FIELD(arg0->brain, s8 *, 0x112) = 1;
    M2C_FIELD(M2C_FIELD(arg0->brain, void **, 0x694), s8 *, 0x35) = 1;
    func_00193A28(arg0, 0x16U, 0);
}
