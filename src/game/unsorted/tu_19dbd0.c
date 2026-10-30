#include "include_asm.h"
#include "ps2/prelude.h"
extern void func_00193980(void *, const void *);
extern void* func_00193B98(void *);
extern s32 func_00187FE0(void *, s32);
extern void func_00173658(f32 *);


extern f32 func_0019EF08(void *, f32);

extern s32 func_0018AB08(void *);
extern u8 func_001892C8(void *);
extern void func_00173640(f32 *, f32);
extern f32 func_0016DE70(void *, f32, f32);
extern void * D_0040F4D4;
extern s32 func_00176F00(s32 *);
extern void func_0019EE30(void *);
extern void func_001736A0(f32 *, f32);
extern void * D_0040F4D0;
extern s32 func_00173610(f32 *);
extern s32 func_0019E060(void *);
extern s32 func_00188F58(void *);
extern s32 func_00177B48(void *, s32);
extern s32 func_00177B20(void *, s32);
extern void func_0019E380(void **);
extern f32 func_0019EEA0(void *, f32);
extern s32 func_0016DFB0(void *, f32);

extern s32 func_00193988();
extern s32 func_001880D8();
extern s32 func_001823B0();
extern s32 func_001829A8();
extern s32 func_001829E8(void *);
extern s32 func_00181028();
extern s32 func_00180FE0();
extern void func_00193A28(void *, u32, s32);
extern f32 func_001891A8(void*);
extern s32 func_001863A0();
extern s32 func_0019DFE8();
extern s32 func_0019DF50(void *);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19dbd0", func_0019DBD0);
void func_0019DD08(void* self, const void* event) {
    int enabled;
    func_00193980(self, event);
    M2C_FIELD(func_00193B98(self), f32*, 0x5C) = -5.0f;
    M2C_FIELD(func_00193B98(self), f32*, 0x60) = 5.0f;
    M2C_FIELD(func_00193B98(self), s32*, 0x6C) = 0;
    M2C_FIELD(func_00193B98(self), s32*, 0x70) = 0;
    M2C_FIELD(func_00193B98(self), s32*, 0x74) = 0;
    M2C_FIELD(func_00193B98(self), f32*, 0x1C) = -1.0f;
    M2C_FIELD(func_00193B98(self), f32*, 0x18) = 1.0f;
    M2C_FIELD(func_00193B98(self), f32*, 8) = -2.0f;
    M2C_FIELD(func_00193B98(self), f32*, 0x10) = 4.0f;
    M2C_FIELD(func_00193B98(self), f32*, 0xC) = 2.0f;
    M2C_FIELD(func_00193B98(self), f32*, 0x14) = -3.0f;
    M2C_FIELD(func_00193B98(self), s32*, 0x3C) = 0;
    M2C_FIELD(func_00193B98(self), s32*, 0x40) = 0;
    M2C_FIELD(func_00193B98(self), s32*, 0x4C) = 0;
    M2C_FIELD(func_00193B98(self), s32*, 0x50) = 0;
    M2C_FIELD(func_00193B98(self), f32*, 0x54) = 1.0f;
    M2C_FIELD(func_00193B98(self), f32*, 4) = -1.0f;
    enabled = 1;
    M2C_FIELD(M2C_FIELD(self, void**, 0), u8*, 0x104) = enabled;
    M2C_FIELD(func_00193B98(self), s32*, 0) = 2;
    M2C_FIELD(func_00193B98(self), s32*, 0x7C) = enabled;
    func_00187FE0((void*)(((s8*)M2C_FIELD(self, void**, 0)) + 0x290), 0);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(self, void**, 0), void**, 0x694), s8*, 0x30) = 0;
    M2C_FIELD(self, u32*, 0x40) = 2;
    func_00173640((f32*)((u8*)self + 0x30), func_0019EEA0(self, func_0016DE70(D_0040F4D4, 1.0f, 2.0f)));
    func_00173658((f32*)((u8*)self + 0x34));
    func_00173658((f32*)((u8*)self + 0x3C));
    func_00173640((f32*)((u8*)self + 0x38), 10.0f);
    M2C_FIELD(self, u8*, 0x46) = 0;
    M2C_FIELD(self, u8*, 0x45) = 0;
    func_0019EE30(self);
}

void func_0019DF10(void **arg0)
{
  int new_var2;
  void *temp_3;
  int new_var;
  func_00193988();
  new_var = 0;
  new_var2 = 0x290;
  temp_3 = *arg0;
  if ((*((u8 *) (temp_3 + new_var2))) != new_var)
  {
    func_001880D8(temp_3 + new_var2);
  }
}

s32 func_0019DF50(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x44) != 0) {
        M2C_FIELD(arg0, s8 *, 0x45) = 0;
        return 1;
    }
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x694), s8 *, 0x30) = 0;
    if ((func_001823B0(M2C_FIELD(arg0, void **, 0) + 0x810, M2C_FIELD(arg0, s128 *, 0x10), 0) == 0) || (func_001829A8(M2C_FIELD(arg0, void **, 0) + 0x810) == 0) || (func_001829E8(M2C_FIELD(arg0, void **, 0) + 0x810) != 0)) {
        M2C_FIELD(arg0, s8 *, 0x45) = 0;
        M2C_FIELD(arg0, u8 *, 0x44) = 1U;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19dbd0", func_0019DFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19dbd0", func_0019E060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19dbd0", func_0019E2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19dbd0", func_0019E318);

void func_0019E380(void **arg0)
{
  unsigned char new_var2;
  void *temp_3;
  s8 *new_var;
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
  new_var2 = func_00181028((*arg0) + 0x140) != 0;
  if (new_var2)
  {
    func_00180FE0((*arg0) + 0x140);
  }
  func_00193A28(arg0, 3, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19dbd0", func_0019E3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19dbd0", func_0019E510);
void func_0019EA58(void* self) {
    switch (M2C_FIELD(self, u32*, 0x40)) {
        case 0:
            if (func_001829E8(M2C_FIELD(self, s32*, 0) + 0x810)) {
                M2C_FIELD(self, u32*, 0x40) = 3;
                func_00173640((f32*)((u8*)self + 0x30), func_0019EEA0(self, func_0016DE70(D_0040F4D4, 1.0f, 2.0f)));
            }
            break;
        case 1:
            if (func_001829E8(M2C_FIELD(self, s32*, 0) + 0x810)) {
                M2C_FIELD(self, u32*, 0x40) = 2;
                func_00173640((f32*)((u8*)self + 0x30), func_0019EEA0(self, func_0016DE70(D_0040F4D4, 1.0f, 2.0f)));
            }
            break;
        case 2:
            func_00173640((f32*)((u8*)self + 0x30), func_0019EF08(self, func_0016DE70(D_0040F4D4, 5.0f, 7.0f)));
            M2C_FIELD(self, u32*, 0x40) = 0;
            break;
        case 3:
            func_00173640((f32*)((u8*)self + 0x30), func_0019EF08(self, func_0016DE70(D_0040F4D4, 5.0f, 7.0f)));
            M2C_FIELD(self, u32*, 0x40) = 1;
            break;
        case 4:
            func_00173640((f32*)((u8*)self + 0x30), func_0019EEA0(self, func_0016DE70(D_0040F4D4, 5.0f, 7.0f)));
            M2C_FIELD(self, u32*, 0x40) = func_0016DFB0(D_0040F4D4, 0.5f) ? 2 : 3;
            break;
    }
}
void func_0019EC00(void* self) {
    s32 temp_2;
    u32 temp_3;

    temp_3 = M2C_FIELD(self, u32*, 0x40);
    switch (temp_3) {
        case 0:
        case 1:
            if ((func_0018AB08((void*)(((s8*)M2C_FIELD(self, void**, 0)) + 0x150)) != 0) &&
                (func_001892C8((void*)(((s8*)M2C_FIELD(self, void**, 0)) + 0x150)) != 0)) {
                if (func_001891A8((void*)(((s8*)M2C_FIELD(self, void**, 0)) + 0x150)) < 2.0f) {
                    f32 duration;
                    M2C_FIELD(self, u32*, 0x40) = (u32)(3 - M2C_FIELD(self, u32*, 0x40));
                    duration = func_0016DE70(D_0040F4D4, 1.0f, 2.0f);
                    func_00173640((f32*)(((s8*)self) + 0x30), duration);
                }
                if (!(func_00176F00((s32*)(((s8*)M2C_FIELD(self, void**, 0)) + 0x1FCC)) & 0xFF)) {
                    if (func_001829E8((void*)(((s8*)M2C_FIELD(self, void**, 0)) + 0x810)) != 0) {
                        func_0019EE30(self);
                        func_001736A0((f32*)(((s8*)self) + 0x30), M2C_FIELD(D_0040F4D0, f32*, 0x1C));
                    }
                } else if (func_00173610((f32*)(((s8*)self) + 0x30)) == 0) {
                    func_0019E060(self);
                }
            }
            break;
        case 2:
        case 3: func_0019EE30(self); break;
        case 4:
            if (func_0019DF50(self) != 0) {
                temp_2 = func_00188F58((void*)(((s8*)M2C_FIELD(self, void**, 0)) + 0x150));
                if ((func_00177B48(M2C_FIELD(M2C_FIELD(self, void**, 0), void**, 0x100), temp_2) == 0) &&
                    (func_00177B20(M2C_FIELD(M2C_FIELD(self, void**, 0), void**, 0x100), temp_2) == 0)) {
                    if ((M2C_FIELD(M2C_FIELD(self, void**, 0), u8*, 0x131) ^ 1) != 0) {
                        func_00193A28((void*)self, 0x11U, 0);
                    } else {
                        func_0019E380(self);
                    }
                }
                func_00173640((f32*)(((s8*)self) + 0x30), func_0019EEA0(self, func_0016DE70(D_0040F4D4, 5.0f, 7.0f)));
                M2C_FIELD(self, u32*, 0x40) = (u32)((func_0016DFB0(D_0040F4D4, 0.5f) != 0) ? 2U : 3U);
            }
            break;
        default: break;
    }
}

void func_0019EE30(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x45) != 0) {
        if (func_001891A8(M2C_FIELD(arg0, s32 *, 0) + 0x150) < 2.0f) {
            goto block_3;
        }
    } else {
block_3:
        func_001863A0(M2C_FIELD(arg0, s32 *, 0) + 0x90);
        func_0019DFE8(arg0);
    }
    func_0019DF50(arg0);
}

f32 func_0019EEA0(void* self, f32 scale) {
    f32 value = func_001891A8((u8*)M2C_FIELD(self, void**, 0) + 0x150) - 12.0f;
    return scale * (__ee_max_s(value * value, 0.0f) * 0.008f + 0.1f);
}
f32 func_0019EF08(void* self, f32 scale) {
    f32 value = __ee_min_s(func_001891A8((u8*)M2C_FIELD(self, void**, 0) + 0x150) - 17.0f, 10.0f);
    return scale * __ee_max_s(1.0f - value * value * 0.005f, 0.2f);
}
