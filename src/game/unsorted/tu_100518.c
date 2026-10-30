#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_0040F0E8;
extern s32 func_0027C320();
extern void * D_0040F0E0;
extern s32 func_0010BC08();
extern s32 D_0040F4F0;
extern s32 func_0027C328();
extern s32 func_0027C348();
extern s32 func_001080C0();
extern s32 func_001080F0();
extern s32 func_002174E0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00100518);

void func_001005A0(void *arg0)
{
 do { M2C_FIELD(arg0, s32 *, 0x10290) = 0x200000; M2C_FIELD(arg0, s32 *, 0x10288) = 0 & 0xFFFFu; } while (0);
  M2C_FIELD(arg0, s32 *, 0x1028C) = 0;
}

void func_001005C0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xA0) = (s32) M2C_FIELD(D_0040F0E8, s32 *, 0x618);
    if (M2C_FIELD(arg0, s32 *, 0) == 0) {
        func_0027C320(arg0, M2C_FIELD(D_0040F0E0, s32 *, 0x2107C));
    }
    func_0010BC08(D_0040F4F0);
    func_0027C328(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00100628);

void func_00101040(void) {
    func_0027C348();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00101060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00101068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_001014E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00101610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_001016F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00101700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00101A90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00101A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00101F80);

void func_00101F90(void) {
    func_001080C0();
}

M2C_UNK * func_00101FB0(void) {
    if (func_001080C0() != 0) {
        return "Main";
    }
    if (func_001080F0() != 0) {
        return "Resource";
    }
    return "Unknown";
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00102000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00102080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00102930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518", func_00102BD0);
extern void func_001D5C30(void*, s32);
extern void* D_0040F510;
extern s8** D_0040F4DC;
extern void func_001078F0(void*, s32);
extern void func_0020AE20(void*);
extern s8* D_0040F544;
extern s32 func_001038A8(void*);
extern void* D_0040F4D0;
extern void func_0027F858(void*);
extern void func_0027F818(void*);

static inline void ApplyFrameState(void* self) {
    if (M2C_FIELD(self, s64*, 0x21090) == 0x200000002LL) {
        M2C_FIELD(self, s32*, 0x21094) = M2C_FIELD(self, s32*, 0x21090) = 1;
    } else
        M2C_FIELD(self, s32*, 0x21090) = M2C_FIELD(self, s32*, 0x21094);
}

void func_00102F68(void* arg0) {
    s32 temp_3;
    s32 temp_3_2;

    M2C_FIELD(arg0, s32*, 0x2109C) = (s32)M2C_FIELD(arg0, s32*, 0x21098);
    ApplyFrameState(arg0);
    temp_3 = M2C_FIELD(arg0, s32*, 0x21088);
    if (temp_3 == 1) {
        M2C_FIELD(arg0, s8*, 0x210C8) = 1;
        func_001D5C30(D_0040F510, 1);
        **D_0040F4DC = 0;
        func_001078F0(D_0040F0E8, 1);
        if (M2C_FIELD(arg0, u8*, 0x210CB) != 0) { func_0020AE20(D_0040F544); }
        M2C_FIELD(arg0, s32*, 0x21088) = 0;
    } else if (temp_3 == 2) {
        M2C_FIELD(arg0, s8*, 0x210C8) = 0;
        func_001D5C30(D_0040F510, 0);
        **D_0040F4DC = 1;
        func_001078F0(D_0040F0E8, 0);
        M2C_FIELD(arg0, s32*, 0x21088) = 0;
    }
    temp_3_2 = M2C_FIELD(arg0, s32*, 0x2108C);
    if (temp_3_2 == 1) {
        M2C_FIELD(arg0, s8*, 0x210C9) = 1;
        func_001D5C30(D_0040F510, 1);
        **D_0040F4DC = 0;
        M2C_FIELD(arg0, s32*, 0x2108C) = 0;
    } else if (temp_3_2 == 2) {
        M2C_FIELD(arg0, s8*, 0x210C9) = 0;
        func_001D5C30(D_0040F510, 0);
        **D_0040F4DC = 1;
        M2C_FIELD(arg0, s32*, 0x2108C) = 0;
    }
    if ((func_001038A8(arg0) != 0) && (M2C_FIELD(D_0040F4D0, u8*, 0x28) != 0)) {
        func_0027F858(D_0040F4D0);
    } else if (func_001038A8(arg0) == 0) {
        if (M2C_FIELD(D_0040F4D0, u8*, 0x28) == 0) {
            if (M2C_FIELD(arg0, s32*, 0x2109C) != 3) { func_0027F818(D_0040F4D0); }
        }
    }
}


s32 func_00103158(void *arg0)
{
  func_002174E0(arg0 + 0x210A0);
  M2C_FIELD(arg0, s32 *, 0x21080) = (M2C_FIELD(arg0, s32 *, 0x2107C) = 0);
  return 1;
}


void func_00103800(void *arg0, s8 arg1)
{
  M2C_FIELD(arg0, s32 *, 0x21088) = 1;
  M2C_FIELD(arg0, s8 *, 0x210CB) = arg1;
}
