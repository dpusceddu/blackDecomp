#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00175A00(s32, void *, M2C_UNK);
extern s32 D_0040F4D4;
extern s32 func_0017BD10(s32, s32);
extern s32 func_00175AB8(s32, s32, M2C_UNK);

void func_0014C330(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x10);
    if (M2C_FIELD(temp_3, s32 (**)(void *), 0xD4)(arg0 + M2C_FIELD(temp_3, s16 *, 0xD0)) != 0) {
        func_00175A00(D_0040F4D4 + 0xA48, arg0, 0);
    }
}

void func_0014C380(s32 arg0) {
    func_0017BD10(D_0040F4D4 + 0xCD4, arg0);
    func_00175AB8(D_0040F4D4 + 0xA48, arg0, 0);
}

s32 func_0014C3D0(void *arg0) {
    return (u32) (M2C_FIELD(arg0, s32 *, 0xC4) - 3) < 2U;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_14be20_14c330", func_0014C3E0);
typedef struct Recovered_BkFlagAssetPS2 Recovered_BkFlagAssetPS2;

typedef struct Recovered_OwnerView Recovered_OwnerView;

extern u8 func_001AFC30(Recovered_BkFlagAssetPS2*);
extern s32 func_0014C5C8(s32*, s32);
extern void func_0025CB08(s32*, Recovered_OwnerView*);
extern s32* D_0040F4CC;
extern s128 D_004432A0;
extern void func_0025D860(Recovered_OwnerView*, s128);
extern void func_0025D910(Recovered_OwnerView*, s128);
extern void func_0025DBA8(Recovered_OwnerView*);
extern void func_0025CBA8(s32*, Recovered_OwnerView*);

void func_0014C488(s32* arg0) {
    s128 temp_16;

    if (M2C_FIELD(arg0, Recovered_OwnerView**, 0xB4) != NULL) {
        if (func_001AFC30(M2C_FIELD(arg0, Recovered_BkFlagAssetPS2**, 0x118)) != 0) {
            func_0014C5C8(arg0, 1);
            func_0025CB08(D_0040F4CC, M2C_FIELD(arg0, Recovered_OwnerView**, 0xB4));
            temp_16 = D_004432A0;
            func_0025D860(M2C_FIELD(arg0, Recovered_OwnerView**, 0xB4), temp_16);
            func_0025D910(M2C_FIELD(arg0, Recovered_OwnerView**, 0xB4), temp_16);
        } else {
            func_0025DBA8(M2C_FIELD(arg0, Recovered_OwnerView**, 0xB4));
            func_0025CBA8(D_0040F4CC, M2C_FIELD(arg0, Recovered_OwnerView**, 0xB4));
            func_0025D860(M2C_FIELD(arg0, Recovered_OwnerView**, 0xB4),
                          M2C_FIELD(M2C_FIELD(arg0, void**, 0x120), s128*, 0x50));
            func_0025D910(M2C_FIELD(arg0, Recovered_OwnerView**, 0xB4),
                          M2C_FIELD(M2C_FIELD(arg0, void**, 0x120), s128*, 0x40));
        }
    }
}
