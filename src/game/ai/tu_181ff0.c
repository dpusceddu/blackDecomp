#include "include_asm.h"
#include "ps2/prelude.h"

/* Recovered_MovementModeBase: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_MovementModeBase {
    u8 unk_0[8];
    u8 unk_8;
    u8 unk_9[7];
    s128 unk_10;
    u128 unk_20;
    s32 unk_30;
    void * unk_34;
    u8 unk_38;
    u8 unk_39[3];
    f32 unk_3C;
    u8 unk_40[8];
    f32 unk_48;
    f32 unk_4C;
    u8 unk_50;
    u8 unk_51[15];
    s128 unk_60;
    s128 unk_70;
    void * unk_80;
} Recovered_MovementModeBase;

/* Recovered_RouteMode: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_RouteMode {
    f32 unk_0;
    f32 unk_4;
    u8 unk_8[8];
    s128 unk_10;
    u8 unk_20[16];
    s32 unk_30;
    void * unk_34;
    u8 unk_38[4];
    f32 unk_3C;
    u8 unk_40[48];
    u128 unk_70;
    void * unk_80;
    u8 unk_84[12];
    void * unk_90;
    u8 unk_94;
    u8 unk_95;
    u8 unk_96[2];
    u32 unk_98;
    u8 unk_9C[228];
    void * unk_180;
    void * unk_184;
} Recovered_RouteMode;

#include "ps2/recovered_types.h"
extern void func_00191C20(Recovered_RouteMode *, void *);
extern void func_00191568(Recovered_MovementModeBase *, void *);

void func_00181FF0(void *arg0, void *arg1) {
    Recovered_MovementModeBase *temp_18;
    Recovered_MovementModeBase *temp_19;
    Recovered_RouteMode *temp_20;

    temp_19 = (Recovered_MovementModeBase *) (((s8 *) arg0) + 0x1F0);
    temp_20 = (Recovered_RouteMode *) (((s8 *) arg0) + 0x60);
    M2C_FIELD(arg0, void **, 0x310) = arg1;
    temp_18 = (Recovered_MovementModeBase *) (((s8 *) arg0) + 0x280);
    func_00191C20(temp_20, arg1);
    func_00191568(temp_19, arg1);
    func_00191568(temp_18, arg1);
    M2C_FIELD(arg0, Recovered_MovementModeBase **, 0x50) = temp_18;
    M2C_FIELD(arg0, Recovered_MovementModeBase **, 0x4C) = temp_19;
    M2C_FIELD(arg0, Recovered_RouteMode **, 0x48) = temp_20;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
}
