#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_004549C4;
extern s32 func_003071A8();
extern f32 D_003CD89C;

#include "ps2/recovered_types.h"
extern void * func_0030D0E0(void *, s8 *, s32);
extern M2C_UNK D_00455BE8;
extern void * func_003067A0(void *);
extern M2C_UNK D_003F07A0;
extern M2C_UNK * D_00455CF8;

void * func_0030B750(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = (M2C_UNK *)0xFFFF;
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            return func_0030D0E0(&D_00455BE8, "CGapDynamicAvoidance", (s32) func_003067A0);
        }
        var_2 = &D_003F07A0;
        D_00455CF8 = &D_003F07A0;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_2;
    }
    return var_2;
}

s32 func_0030B7A8(s32 arg0)
{
  s32 *var_2;
  var_2 = &D_004549C4;
  if ((M2C_FIELD(arg0, s32 *, 0x1C)) & D_004549C4)
  {
    var_2 = func_003071A8();
    return (s32) var_2;
    var_2 = &D_004549C4;
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030B7E0);

void func_0030B898(void) {
    func_003071A8();
}

void func_0030B8B8(f32 fparg0) {
    if (fparg0 >= 0.0f) {
        D_003CD89C = fparg0;
    }
}

void func_0030B8E0(void *arg0, f32 fparg0) {
    if (fparg0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xE8) = fparg0;
    }
}

void func_0030B900(void *arg0, f32 fparg0) {
    if (fparg0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xEC) = fparg0;
    }
}

void func_0030B920(void *arg0, f32 fparg0) {
    if (fparg0 > 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xF0) = (f32) (fparg0 * 0.5f);
    }
}

void func_0030B958(void *arg0, f32 fparg0) {
    if (fparg0 > 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xF4) = (f32) (fparg0 * M2C_FIELD(arg0, f32 *, 8));
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030B988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030BA10);

void func_0030BA18(void) {
    func_0030B750(1, 0xFFFF);
}

void func_0030BA38(void) {
    func_0030B750(0, 0xFFFF);
}
