#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00173640(void *, f32);
extern f32 func_0018DD78();
extern s32 func_00173610(void *);
extern s32 func_001A6840(s32, M2C_UNK, M2C_UNK);
extern s32 func_00158088();
extern s32 func_00181F48(void *arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1);
extern s32 func_00181AD0(void *, M2C_UNK);

void func_0017E710(void *arg0, s128 arg1) {
    func_00173640(arg0 + 0x18, func_0018DD78(M2C_FIELD(arg0, s32 *, 0x48)));
    M2C_FIELD(arg0, s8 *, 0x82) = 1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s128 *, 0x20) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017E770);

s32 func_0017E800(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x82) == 0) {
        if (func_00173610(arg0 + 0x18) != 0) {
            return func_001A6840(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), void **, 0x7C), s32 *, 0x330), 0, 0) == 0;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    return 1;
}

#ifdef NON_MATCHING
static inline f32 NormalizeAngle(f32 value) {
    if (value < 0.0f) {
        f32 magnitude = -value;
        value = -(magnitude - (f32)(s32)(magnitude / 360.0f) * 360.0f);
    } else {
        value = value - (f32)(s32)(value / 360.0f) * 360.0f;
    }
    if (value < -180.0f)
        value += 360.0f;
    else if (value > 180.0f)
        value -= 360.0f;
    return value;
}

#endif

#ifdef NON_MATCHING
// Unmatched: wrapped-angle result and absolute-value/tolerance registers differ.
s32 func_0017E860(void* self) {
    f32 angle = M2C_FIELD(self, f32*, 0x54) - *M2C_FIELD(self, f32**, 0x44);
    angle = NormalizeAngle(angle);
    return __builtin_fabsf(angle) < M2C_FIELD(self, f32*, 0x64);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017E860);
#endif
#ifdef NON_MATCHING
// Unmatched: wrapped-angle result and absolute-value/tolerance registers differ.
s32 func_0017E968(void* self) {
    f32 angle = M2C_FIELD(self, f32*, 0x68) - M2C_FIELD(M2C_FIELD(self, void**, 0x44), f32*, 4);
    angle = NormalizeAngle(angle);
    return __builtin_fabsf(angle) < M2C_FIELD(self, f32*, 0x64);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017E968);
#endif
#ifdef NON_MATCHING
// Unmatched: normalization join duplicates the absolute value into a likely-branch delay slot.
extern f32 func_0018DA88(void*);
extern f32 func_0018D9F8(void*);
extern f32 func_0018DA40(void*);
f32 func_0017EAD0(void* self, f32 target, f32 current, f32 maximum) {
    f32 angle = __builtin_fabsf(NormalizeAngle(target - current));
    f32 speed;
    if (angle < 5.0f) {
        if (M2C_FIELD(self, u8*, 0x7D))
            speed = func_0018DA88(M2C_FIELD(self, void**, 0x48));
        else
            speed = func_0018D9F8(M2C_FIELD(self, void**, 0x48));
    } else {
        f32 lower;
        f32 upper;
        if (angle > 90.0f) angle = 180.0f - angle;
        angle = __ee_max_s(angle, 0.0f);
        lower = func_0018DA88(M2C_FIELD(self, void**, 0x48));
        angle = __ee_min_s(angle, 45.0f);
        upper = func_0018DA40(M2C_FIELD(self, void**, 0x48));
        speed = lower + (upper - lower) * (angle / 45.0f);
    }
    return __ee_min_s(maximum, speed);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017EAD0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017EC98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017F000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017F298);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017F498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017F720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017F868);

u8 func_0017FA58(void *arg0) {
    u8 var_5;
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x44);
    var_5 = 0;
    if (M2C_FIELD(temp_4, s32 *, 0x80) == 1) {
        var_5 = M2C_FIELD(temp_4, u8 *, 0x84A);
    }
    return var_5;
}

void func_0017FA78(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x44);
    if ((M2C_FIELD(temp_3, u8 *, 0x3B) != 0) && (func_001A6840(M2C_FIELD(M2C_FIELD(temp_3, void **, 0x7C), s32 *, 0x330), 0, 1) != 0)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), u8 *, 0x3B) = 0U;
    }
}

void func_0017FAC8(void *arg0) {
    void *temp_3;
    void *temp_3_2;

    temp_3 = M2C_FIELD(arg0, void **, 0x44);
    if ((M2C_FIELD(temp_3, u8 *, 0x31) == 0) && (func_00158088(M2C_FIELD(M2C_FIELD(temp_3, void **, 0x7C), s32 *, 0x2A4)) == 0)) {
        if (M2C_FIELD(arg0, u8 *, 0x82) != 0) {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s8 *, 0x33) = 1;
            M2C_FIELD(arg0, u8 *, 0x82) = 0U;
            temp_3_2 = M2C_FIELD(arg0, void **, 0x44);
            if (M2C_FIELD(temp_3_2, s32 *, 0x80) == 1) {
                func_00181F48(temp_3_2 + 0xC80, 0, 0xB, 0.0f, 2.0f);
            }
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s8 *, 0x33) = 0;
        }
    }
}

void func_0017FB68(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x7C) = 0;
}

s32 func_0017FB70(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017FB78);

void func_0017FC28(void) {

}

void func_0017FC30(void *arg0, s32 arg1) {
    void *temp_4;

    if (arg1 == 2) {
        temp_4 = M2C_FIELD(arg0, void **, 0x44);
        if (M2C_FIELD(temp_4, s32 *, 0x80) == 1) {
            func_00181AD0(temp_4 + 0xEC0, 4);
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017FC70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_0017FCD8);

void func_00180028(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x44);
    if (M2C_FIELD(temp_4, s32 *, 0x80) == 1) {
        func_00181F48(temp_4 + 0xC80, 0, 0x13, 0.0f, 1.0f);
    }
}

void func_00180070(void) {

}

s32 func_00180078(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x8C) == 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e710", func_00180088);
