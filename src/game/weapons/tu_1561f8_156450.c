#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_Instance: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Instance {
    s32 unk_0;
    void * unk_4;
    u8 unk_8[4];
    void * unk_C;
    s32 unk_10;
    u8 unk_14[16];
    f32 unk_24;
    u8 unk_28[8];
    u128 unk_30;
    u128 unk_40;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s16 unk_5C;
    u8 unk_5E[2];
    f32 unk_60;
    f32 unk_64;
    u8 unk_68[8];
    s32 unk_70;
    u8 unk_74[340];
    s16 unk_1C8;
    u8 unk_1CA[1942];
    f32 unk_960;
    f32 unk_964;
    f32 unk_968;
    u8 unk_96C[4];
    s32 unk_970;
    u8 unk_974[12];
    u32 unk_980;
    u8 unk_984[8];
    s32 unk_98C;
    u8 unk_990[8];
    s32 unk_998;
    s32 unk_99C;
    f32 unk_9A0;
    f32 unk_9A4;
    u8 unk_9A8[4];
    void * unk_9AC;
    u8 unk_9B0[24];
    f32 unk_9C8;
} Recovered_Instance;

/* Recovered_WeaponManagerMethods: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_WeaponManagerMethods {
    void * unk_0;
    u8 unk_4[8];
    s32 unk_C;
    s32 unk_10;
    u8 unk_14[56];
    u8 unk_4C;
    u8 unk_4D[47];
    u8 unk_7C;
    u8 unk_7D[47];
    u8 unk_AC;
    u8 unk_AD[47];
    u8 unk_DC;
    u8 unk_DD[47];
    u8 unk_10C;
    u8 unk_10D[47];
    u8 unk_13C;
    u8 unk_13D[47];
    u8 unk_16C;
    u8 unk_16D[47];
    u8 unk_19C;
} Recovered_WeaponManagerMethods;

#include "ps2/recovered_types.h"
extern void func_0015D198(Recovered_WeaponManagerMethods *, Recovered_Instance *);
extern void ** D_0040F4E0;
extern void * func_0020BC00(void *, s32);
extern void * D_0040F544;
extern s32 func_00209FF8(void *, s32);
extern s32 func_0027C278(s32);
extern M2C_UNK D_003F4C40;

s32 func_00156450(void *arg0) {
    void *temp_16;

    func_0015D198(D_0040F4E0, M2C_FIELD(arg0, s32 *, 0xF4));
    func_0015D198(D_0040F4E0, M2C_FIELD(arg0, s32 *, 0xF8));
    temp_16 = func_0020BC00(D_0040F544, 2);
    func_00209FF8(temp_16, func_0027C278((s32) &D_003F4C40));
    M2C_FIELD(arg0, s32 *, 0xF0) = 0;
    M2C_FIELD(arg0, s32 *, 0xF4) = 0;
    M2C_FIELD(arg0, s32 *, 0xF8) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_156450", func_001564D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_156450", func_00156A20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_156450", func_00156A88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_156450", func_00156CA0);
