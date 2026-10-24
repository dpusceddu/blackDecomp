#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_AIRouteFollower: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_AIRouteFollower {
    void * unk_0;
    void * unk_4;
    s32 unk_8;
    u8 unk_C[24];
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    u8 unk_3C[40];
    void * unk_64;
    s32 unk_68;
    u8 unk_6C[8];
    s32 unk_74;
    s32 unk_78;
    s32 unk_7C;
    void * unk_80;
    s32 unk_84;
    u8 unk_88[4];
    u8 unk_8C;
    u8 unk_8D[7];
    s32 unk_94;
    s32 unk_98;
    u8 unk_9C[4];
    s32 unk_A0;
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    u8 unk_B0;
    u8 unk_B1;
    u8 unk_B2;
    u8 unk_B3;
    u8 unk_B4;
    u8 unk_B5[3];
    f32 unk_B8;
    f32 unk_BC;
    f32 unk_C0;
    f32 unk_C4;
    f32 unk_C8;
    f32 unk_CC;
    f32 unk_D0;
    f32 unk_D4;
    f32 unk_D8;
    f32 unk_DC;
    f32 unk_E0;
    f32 unk_E4;
    f32 unk_E8;
    f32 unk_EC;
    f32 unk_F0;
    f32 unk_F4;
    f32 unk_F8;
    f32 unk_FC;
    f32 unk_100;
    f32 unk_104;
    f32 unk_108;
    u8 unk_10C[16];
    f32 unk_11C;
    f32 unk_120;
    f32 unk_124;
    f32 unk_128;
    f32 unk_12C;
    f32 unk_130;
    u8 unk_134;
    u8 unk_135;
    u8 unk_136[2];
    s32 unk_138;
    s32 unk_13C;
    s32 unk_140;
    s32 unk_144;
    f32 unk_148;
    f32 unk_14C;
    f32 unk_150;
    s32 unk_154;
    s32 unk_158;
    void * unk_15C;
    u8 unk_160[4];
    void * unk_164;
    u8 unk_168[24];
    s32 unk_180;
    void * unk_184;
    s32 unk_188;
    u8 unk_18C[4];
    s32 unk_190;
    s32 unk_194;
    u8 unk_198;
    u8 unk_199[23];
    void * unk_1B0;
    u8 unk_1B4;
    u8 unk_1B5;
} Recovered_AIRouteFollower;

/* Recovered_RouteRequest: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_RouteRequest {
    void * unk_0;
    u8 unk_4[4];
    s32 unk_8;
    u32 unk_C;
    s128 unk_10;
    s128 unk_20;
    void * unk_30;
    void * unk_34;
    f32 unk_38;
    f32 unk_3C;
    f32 unk_40;
    f32 unk_44;
    f32 unk_48;
    f32 unk_4C;
    void * unk_50;
    s32 unk_54;
    u8 unk_58;
    u8 unk_59[7];
    u8 unk_60;
} Recovered_RouteRequest;

#include "ps2/recovered_types.h"
extern void * func_00300278(Recovered_AIRouteFollower *, Recovered_RouteRequest *);

s32 func_00304E38(void *arg0, s32 arg1, void *arg2, void *arg3) {
    void **temp_2;
    void *temp_16;
    void *temp_18;
    void *temp_3;
    void *temp_9;

    temp_18 = func_00300278((Recovered_AIRouteFollower *) arg0, (Recovered_RouteRequest *) arg2);
    temp_16 = func_00300278((Recovered_AIRouteFollower *) arg0, (Recovered_RouteRequest *) arg3);
    if (temp_18 != NULL) {
        if (temp_16 != NULL) {
            temp_3 = M2C_FIELD(arg0, void **, 0);
            temp_2 = M2C_FIELD(temp_3, void **(**)(void *), 0x84)((void *) (((s8 *) arg0) + M2C_FIELD(temp_3, s16 *, 0x80)));
            temp_9 = *temp_2;
            return M2C_FIELD(temp_9, s32 (**)(void *, s32, void *, void *, s32, void *), 0x14)((void *) (((s8 *) temp_2) + M2C_FIELD(temp_9, s16 *, 0x10)), M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x14), temp_18, temp_16, arg1, temp_9);
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
