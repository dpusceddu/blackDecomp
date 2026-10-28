#ifndef GAME_STREAM_CONTROL_H
#define GAME_STREAM_CONTROL_H

#include "ps2/prelude.h"

/* Partial native views. Original class identities and field roles are UNVERIFIED. */
typedef struct {
    void* buffer;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Recovered_StreamRecord;

typedef struct {
    u8 unk_00[0x10];
    s16 releaseAdjustment;
    u16 unk_12;
    void (*release)(void*);
    s16 beginAdjustment;
    u16 unk_1A;
    s32 (*begin)(void*, u32, s32);
    u8 unk_20[8];
    s16 resetAdjustment;
    u16 unk_2A;
    s32 (*reset)(void*, s32, s32);
    u8 unk_30[0x10];
    s16 readyAdjustment;
    u16 unk_42;
    s32 (*ready)(void*);
} Recovered_StreamDeviceVtable;

#ifdef __cplusplus
class Recovered_StreamDevice {
    u8 unk_00[0x28];

  public:
    /* Unused slots' signatures are UNVERIFIED; their positions preserve the native table. */
    virtual s32 slot08();
    virtual void release();
    virtual s32 begin(u32, s32);
    virtual s32 slot20();
    virtual s32 reset(s32, s32);
    virtual s32 slot30();
    virtual s32 slot38();
    virtual s32 ready();
};
typedef char StreamDeviceSize[sizeof(Recovered_StreamDevice) == 0x2C ? 1 : -1];
#else
typedef struct {
    u8 unk_00[0x28];
    Recovered_StreamDeviceVtable* vtable;
} Recovered_StreamDevice;
#endif

typedef struct {
    Recovered_StreamRecord records[2];
    s32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
    u8 unk_43;
    u8 active;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    void* unk_58;
    void* unk_5C;
    void* unk_60;
    Recovered_StreamDevice* device;
    s32 pending;
    u8 unk_6C[4];
    u8 unk_70[0x48];
    u8 stream[0x60];
    s32 unk_118;
    s8 unk_11C;
    s8 selected;
    u8 unk_11E[2];
    s32 state;
} Recovered_StreamControl;

typedef char StreamRecordSize[sizeof(Recovered_StreamRecord) == 0x18 ? 1 : -1];
typedef char StreamDeviceOffset[(u32)&((Recovered_StreamControl*)0)->device == 0x64 ? 1 : -1];
typedef char StreamSelectedOffset[(u32)&((Recovered_StreamControl*)0)->selected == 0x11D ? 1 : -1];
typedef char StreamStateOffset[(u32)&((Recovered_StreamControl*)0)->state == 0x120 ? 1 : -1];

#endif
