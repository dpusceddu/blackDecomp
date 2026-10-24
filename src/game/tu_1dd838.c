#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001DFC78();
extern s32 func_001E0FE8(void *);
extern s32 func_001DEEB8();
extern s32 func_001E0D28();
extern s32 func_001E0F28(void *);
extern s32 func_001E0E70(void *);
extern s32 func_001E0A30(void *);
extern f32 func_001ED820(s32);
extern void * D_0040F510;
extern s8 func_00281120();
extern f32 D_003BD390;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD9C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DDE78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DE070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DE078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DE1F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DE3D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DE520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DE598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DE6F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DEC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DED60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DEEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF3D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF4D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF7B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DF9E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFAB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFB20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFC00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFC78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFD08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFE38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFEB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DFED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0028);

void func_001E0440(void *arg0) {
    func_001DFC78();
    func_001E0FE8(arg0);
    func_001E10C0(arg0);
    func_001E1068(arg0);
}

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00280100(s32, void *);
extern void * D_0040F510;
extern f32 func_001DFE38(void *);

s32 func_001E0480(void *arg0) {
    s32 *var_16;
    s32 var_20;
    void **var_17;
    void **var_18;
    void *temp_3;
    void *temp_5;
    void *temp_5_2;

    var_17 = (void **) (((s8 *) arg0) + 0x50);
    var_16 = (s32 *) (((s8 *) arg0) + 0x30);
    var_18 = var_17;
    var_20 = 7;
    do {
        if (*var_16 != 0) {
            temp_3 = *var_17;
            M2C_FIELD(temp_3, M2C_UNK (**)(void *), 0x1C)((void *) (((s8 *) var_18) + M2C_FIELD(temp_3, s16 *, 0x18)));
            *var_16 = 0;
        }
        var_18 = (void **) (((s8 *) var_18) + 0x10);
        var_17 = (void **) (((s8 *) var_17) + 0x10);
        var_20 -= 1;
        var_16 = (s32 *) (((s8 *) var_16) + 4);
    } while (var_20 >= 0);
    temp_5 = M2C_FIELD(arg0, void **, 0x241C);
    if (temp_5 != NULL) {
        func_00280100((s32) D_0040F510, temp_5);
        M2C_FIELD(arg0, void **, 0x241C) = NULL;
    }
    temp_5_2 = M2C_FIELD(arg0, void **, 0x2420);
    if (temp_5_2 != NULL) {
        func_00280100((s32) D_0040F510, temp_5_2);
        M2C_FIELD(arg0, void **, 0x2420) = NULL;
    }
    M2C_FIELD(arg0, s32 *, 0x2434) = 0;
    M2C_FIELD(arg0, s32 *, 0x2438) = 0;
    func_001DFE38(arg0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E06F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0768);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_001E07F0(void *arg0, s32 *arg1) {
    s32 *var_4;
    s32 var_3;

    var_4 = (s32 *) (((s8 *) arg0) + 0x30);
    var_3 = 0;
loop_1:
    if (*var_4 != arg1) {
        var_3 += 1;
        var_4 = (s32 *) (((s8 *) var_4) + 4);
        if (var_3 >= 8) {
            return -1;
        }
        goto loop_1;
    }
    return var_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0820);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0928);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

void func_001E0930(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    u32 temp_3;
    void *temp_4;
    void *temp_4_2;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x2410);
    if (temp_3 < 0x40U) {
        temp_4 = (temp_3 * 0x50) + arg0;
        M2C_FIELD(temp_4, s128 *, 0xD0) = (s128) M2C_FIELD(arg1, s128 *, 0);
        temp_4_2 = temp_4 + 0xD0;
        M2C_FIELD(temp_4_2, s128 *, 0x10) = (s128) M2C_FIELD(arg1, s128 *, 0x10);
        M2C_FIELD(temp_4_2, s128 *, 0x20) = (s128) M2C_FIELD(arg1, s128 *, 0x20);
        M2C_FIELD(temp_4_2, s128 *, 0x30) = (s128) M2C_FIELD(arg1, s128 *, 0x30);
        M2C_FIELD(((M2C_FIELD(arg0, u32 *, 0x2410) * 0x50) + arg0), s8 *, 0x114) = 0;
        M2C_FIELD(((M2C_FIELD(arg0, u32 *, 0x2410) * 0x50) + arg0), s8 *, 0x115) = (s8) arg2;
        M2C_FIELD(arg0, u32 *, 0x2410) = (u32) (M2C_FIELD(arg0, u32 *, 0x2410) + 1);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E09A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0A30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0E70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0FE8);

void func_001E1068(void *arg0) {
    u8 sp[8];
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_3 != -1) {
        if (temp_3 == 0) {
            func_001DEEB8(sp, M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, u8 *, 0x24), 0);
        }
        M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) - 1);
    }
}

void func_001E10C0(void *arg0) {
    func_001E0D28();
    func_001E0F28(arg0);
    func_001E0E70(arg0);
    func_001E0A30(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E11F8);

s32 func_001E1240(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x30);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1248);

void func_001E1690(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        M2C_FIELD(arg0, f32 *, 0x242C) = func_001ED820(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x2C));
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x242C) = 0.0f;
}

void func_001E16E0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x18) = func_00281120();
}

f32 func_001E1708(s32 arg0, s32 arg1) {
    return (&D_003BD390)[arg1];
}
