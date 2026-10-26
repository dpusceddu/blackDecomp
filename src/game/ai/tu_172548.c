#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/action_views.h"


extern s32 func_00176F00();
extern s32 func_0017B6F8();
extern void * D_0040F4D4;
extern void * D_0040F4D0;
extern s32 func_00173610(f32*);
extern void func_00173640(f32*, f32);
extern f32 AIManager_RandomRange(void*, f32, f32);
extern s32 func_00172548(f32*);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_00172548);

void func_001725B8(void *arg0) {
    if ((M2C_FIELD(arg0, void **, 0x10) != NULL) && (func_00176F00(arg0 + 0x14) != 0)) {
        M2C_FIELD(arg0, s32 *, 0xC) = func_0017B6F8(D_0040F4D4 + 0x1290, M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s128 *, 0xA0));
    }
}

s32 func_00172610(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

void func_00172618(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg1;
}

s32 func_00172620(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

s32 func_00172628(void) {
    return 1;
}

s32 func_00172630(void) {
    return 1;
}

void func_00172638(void) {

}

s32 func_00172640(Recovered_ActionTimerPair* self) {
    f32* timer = &self->unk_04;
    s32 result;
    if (func_00173610(timer)) {
        func_00173640(timer, AIManager_RandomRange(D_0040F4D4, 1.0f, 2.0f));
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
s32 func_001726A0(Recovered_ActionTimerPair* self) {
    f32* timer = &self->unk_08;
    s32 result;
    if (func_00173610(timer)) {
        func_00173640(timer, AIManager_RandomRange(D_0040F4D4, 1.0f, 2.0f));
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_00172700(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_00172708);
#ifdef NON_MATCHING
// Unmatched: native short loop has one fewer assembler NOP.
s32 func_001727C0(f32* self) {
    f32* value;
    s32 count;
    if (!func_00172548(self)) return 0;
    value = (f32*)((u8*)self + 0x4C);
    count = 3;
    do {
        *value = 0.0f;
        count--;
        value--;
    } while (count >= 0);
    return 1;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_001727C0);

s32 func_00172818(void) {
    return 1;
}

s32 func_00172820(void) {
    return 1;
}

void func_00172828(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_00172830);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_001729F8);

s32 func_00172C00(s32 arg0, s32 arg1, s32 arg2)
{
  s8 *new_var;
  new_var = (s8 *) (arg0 + (arg1 * 4));
  *((s32 *) (new_var + 0x64)) = arg2;
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_00172C18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_00172C50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_00172C88);
s32 func_00172E28(void* self, s32 kind) {
    switch (kind) {
    case 0: return 2;
    case 1: return 0;
    case 2: return 1;
    default: return 4;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_00172E80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548", func_00172ED8);

void func_00173190(void *arg0, s128 arg1) {
    M2C_FIELD(arg0, s128 *, 0x230) = arg1;
}


s32 func_001735E0(f32 *arg0) {
    s32 var_2;

    var_2 = 1;
    if (*arg0 == -1.0f) {
        var_2 = 0;
    }
    return var_2;
}

s32 func_00173610(f32 *arg0) {
    s32 var_2;

    var_2 = 1;
    if (!(*arg0 <= M2C_FIELD(D_0040F4D0, f32 *, 0x20))) {
        var_2 = 0;
    }
    return var_2;
}

void func_00173640(f32 *arg0, f32 fparg0) {
    *arg0 = M2C_FIELD(D_0040F4D0, f32 *, 0x20) + fparg0;
}


f32 func_00173678(f32 *arg0) {
    return *arg0 - M2C_FIELD(D_0040F4D0, f32 *, 0x20);
}

void func_00173690(f32 *arg0) {
    *arg0 = -1.0f;
}

void func_001736A0(f32 *arg0, f32 fparg0) {
    *arg0 += fparg0;
}

void func_001736B0(void) {

}
