#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00107D20(M2C_UNK);
extern s32 * D_0040F4DC;
const u32 rodata_003F4228[14] __asm__("D_003F4228") __attribute__((aligned(8))) = { 0x00000032, 0x00000078, 0x0000008C, 0x00000082, 0x0000007D, 0x0000006E, 0x00000064, 0x00000096, 0x3F800000, 0x3E99999A, 0x3F800000, 0x3F19999A, 0x3F800000, 0x00000000 };
extern volatile char D_003F4228;
extern s32 * D_0040F53C;
extern void func_00122DF0(M2C_UNK *);
extern M2C_UNK D_0048EFA8;
extern s32 func_00122E38(M2C_UNK *, s32);
extern s32 func_00123020(M2C_UNK *, s32);
extern s32 func_00123248(M2C_UNK *);
extern void func_00123960(M2C_UNK *);
extern s32 func_00123980(M2C_UNK *, M2C_UNK, s32, s32);

void func_00121EF0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) | arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00121F00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122120);

s16 func_00122368(void **arg0, s32 arg1) {
    if (arg1 & 1) {
        return M2C_FIELD(*arg0, s16 *, 0x1C);
    }
    if (arg1 & 2) {
        return M2C_FIELD(*arg0, s16 *, 0x22);
    }
    if (arg1 & 4) {
        return M2C_FIELD(*arg0, s16 *, 0x24);
    }
    if (arg1 & 8) {
        return M2C_FIELD(*arg0, s16 *, 0x26);
    }
    if (arg1 & 0x10) {
        return M2C_FIELD(*arg0, s16 *, 0x28);
    }
    if (arg1 & 0x20) {
        return M2C_FIELD(*arg0, s16 *, 0x2A);
    }
    if (arg1 & 0x40) {
        return M2C_FIELD(*arg0, s16 *, 0x2C);
    }
    if (arg1 & 0x80) {
        return M2C_FIELD(*arg0, s16 *, 0x2E);
    }
    if (arg1 & 0x100) {
        return M2C_FIELD(*arg0, s16 *, 0x30);
    }
    if (arg1 & 0x200) {
        return M2C_FIELD(*arg0, s16 *, 0x32);
    }
    if (arg1 & 0x400) {
        return M2C_FIELD(*arg0, s16 *, 0x34);
    }
    if (arg1 & 0x800) {
        return M2C_FIELD(*arg0, s16 *, 0x36);
    }
    if (arg1 & 0x1000) {
        return M2C_FIELD(*arg0, s16 *, 0x38);
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122520);

void func_001225B8(void **arg0, s32 arg1) {
    void *temp_3;
    void *temp_3_2;
    void *temp_3_3;
    void *temp_3_4;
    void *temp_3_5;

    if (arg1 & 4) {
        temp_3 = *arg0;
        M2C_FIELD(temp_3, u8 *, 0x17) = (u8) (M2C_FIELD(temp_3, u8 *, 0x17) + 1);
        return;
    }
    if (arg1 & 8) {
        temp_3_2 = *arg0;
        M2C_FIELD(temp_3_2, u8 *, 0x18) = (u8) (M2C_FIELD(temp_3_2, u8 *, 0x18) + 1);
        return;
    }
    if (arg1 & 0x10) {
        temp_3_3 = *arg0;
        M2C_FIELD(temp_3_3, u8 *, 0x19) = (u8) (M2C_FIELD(temp_3_3, u8 *, 0x19) + 1);
        return;
    }
    if (arg1 & 2) {
        temp_3_4 = *arg0;
        M2C_FIELD(temp_3_4, u8 *, 0x16) = (u8) (M2C_FIELD(temp_3_4, u8 *, 0x16) + 1);
        return;
    }
    temp_3_5 = *arg0;
    if (arg1 & 0x20) {
        M2C_FIELD(temp_3_5, u8 *, 0x1A) = (u8) (M2C_FIELD(temp_3_5, u8 *, 0x1A) + 1);
        return;
    }
    M2C_FIELD(temp_3_5, u8 *, 0x15) = (u8) (M2C_FIELD(temp_3_5, u8 *, 0x15) + 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122658);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122660);

void func_00122708(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = func_00107D20(0x280);
}

s32 func_00122738(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s8 *, 0x15) = 1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), f32 *, 4) = 300.0f;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0x1C) = 0x1E;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0x1E) = 0x1E;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), f32 *, 0xC) = 20.0f;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122780);

void func_001227A8(s32 *arg0) {
    *arg0 = *D_0040F4DC;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_001227C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_001228E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122980);

s32 func_001229F8(void) {
    return 8;
}

s32 func_00122A00(s32 arg0, s32 arg1)
{
  M2C_UNK *new_var;
  new_var = &(*((((s32) (arg1 << 0x18)) >> 0x16) + (&D_003F4228)));
  return *new_var;
}

void func_00122A20(void) {
    func_00122BB0(*D_0040F53C);
}

void func_00122A48(void) {
    func_00122BD0(*D_0040F53C);
}

void func_00122A70(void) {
    func_00122BF0(*D_0040F53C);
}

void func_00122A98(void) {
    func_00122C20(*D_0040F53C);
}

void func_00122AC0(void) {
    func_00122C50(*D_0040F53C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122AE8);

void func_00122AF0(void) {
    func_00122DF0(&D_0048EFA8);
}


void func_00122B60(s32 arg0) {
    func_00122E38(&D_0048EFA8, arg0);
}

void func_00122B88(s32 arg0) {
    func_00123020(&D_0048EFA8, arg0);
}

void func_00122BB0(void) {
    func_00123248(&D_0048EFA8);
}

void func_00122BD0(void) {
    func_00123960(&D_0048EFA8);
}

void func_00122BF0(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 1, arg1, arg2);
}

void func_00122C20(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 0, arg1, arg2);
}

void func_00122C50(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 2, arg1, arg2);
}
