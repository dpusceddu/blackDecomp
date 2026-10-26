#include "include_asm.h"
#include "game/aligned_buffer.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0028F618(s32);
extern s32 func_0028F718(s32);
extern s32 func_0028FA60(s32);
extern void func_0028F3B0(void *, s32);
extern void func_0028F408(void *);
extern void func_0028F2C0(void *, u32 *, s32 *, u32 *, u32 *);

typedef struct {
    u8 unk_00[0x18];
    s16 beginAdjustment;
    u16 unk_1A;
    s32 (*begin)(void *, u32, s32);
    u8 unk_20[8];
    s16 resetAdjustment;
    u16 unk_2A;
    s32 (*reset)(void *, s32, s32);
    u8 unk_30[0x10];
    s16 readyAdjustment;
    u16 unk_42;
    s32 (*ready)(void *);
} Recovered_StreamDeviceVtable;

typedef struct {
    u8 unk_00[0x28];
    Recovered_StreamDeviceVtable *vtable;
} Recovered_StreamDevice;

typedef struct {
    u8 unk_00[0x43];
    u8 unk_43;
    u8 active;
    u8 unk_45;
    u8 unk_46[0x1E];
    Recovered_StreamDevice *device;
    s32 pending;
    u8 unk_6C[0x4C];
    u8 stream[1];
} Recovered_StreamControl; /* Field roles UNVERIFIED. */

extern void func_002719D0(Recovered_StreamControl *, s32);

void func_00271650(void *arg0)
{
  void *new_var;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  new_var = arg0;
  if (new_var && new_var)
  {
  }
  M2C_FIELD(new_var, s32 *, 4) = -1;
  M2C_FIELD(new_var, s32 *, 8) = -1;
}

void * func_00271668(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    s32 temp_3;
    s32 temp_7;

    temp_7 = (s32) (((s32) arg2 > -1) ? arg2 : (arg2 + 3)) >> 2;
    temp_3 = (s32) (((s32) arg3 > -1) ? arg3 : (arg3 + 3)) >> 2;
    M2C_FIELD(arg0, void **, 0x14) = arg4;
    M2C_FIELD(arg0, void **, 0xC) = arg2;
    M2C_FIELD(arg0, void **, 0x10) = arg3;
    M2C_FIELD(arg0, s32 *, 4) = temp_7;
    M2C_FIELD(arg0, s32 *, 8) = temp_3;
    if (arg2 != (temp_7 * 4)) {
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_7 + 1);
    }
    if (arg3 != (temp_3 * 4)) {
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 1);
    }
    M2C_FIELD(arg0, void **, 0) = AlignedBuffer_Allocate(arg1, (u32) (((s32) M2C_FIELD(arg0, void **, 0xC) * (s32) M2C_FIELD(arg0, void **, 0x10)) << 0xA));
    return (void *)1;
}

void func_00271710(void *arg0)
{
  void *new_var;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  new_var = arg0;
  if (new_var && new_var)
  {
  }
  M2C_FIELD(new_var, s32 *, 4) = -1;
  M2C_FIELD(new_var, s32 *, 8) = -1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650", func_00271728);

s32 func_00271968(s32 arg0, s32 arg1, s32 arg2) {
    func_0028F618(arg2 + 0xB8);
    return 1;
}

s32 func_00271988(s32 arg0, s32 arg1, s32 arg2) {
    func_0028F718(arg2 + 0xB8);
    return 1;
}

s32 func_002719A8(s32 arg0) {
    return func_0028FA60(arg0 + 0xB8) <= 0xFFFF;
}

#ifdef NON_MATCHING
// Unmatched: device-call register selection and buffer scheduling differ.
void func_002719D0(Recovered_StreamControl *self, s32 amount) {
    u32 start, next, unused;
    Recovered_StreamDevice *device;
    Recovered_StreamDeviceVtable *vtable;
    s32 ready;
    s32 length;
    if (self->pending != 0) return;
    device = self->device;
    vtable = device->vtable;
    ready = vtable->ready((u8 *)device + vtable->readyAdjustment);
    if (ready != 1 || self->active == 1) return;
    func_0028F2C0(self->stream, &start, &length, &next, &unused);
    start = (start & 0x0FFFFFFF) | 0x20000000;
    next = (next & 0x0FFFFFFF) | 0x20000000;
    amount <<= 16;
    if (length >= amount) {
        device = self->device;
        vtable = device->vtable;
        if (vtable->begin((u8 *)device + vtable->beginAdjustment, start, amount) <= 0) {
            self->active = ready;
            if (self->unk_43 != 0) {
                device = self->device;
                vtable = device->vtable;
                vtable->reset((u8 *)device + vtable->resetAdjustment, 0, 0);
            }
        }
        self->pending = amount;
    }
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650", func_002719D0);

void func_00271AF0(Recovered_StreamControl *self) {
    if (self->pending > 0) {
        Recovered_StreamDevice *device = self->device;
        Recovered_StreamDeviceVtable *vtable = device->vtable;
        if (vtable->ready((u8 *)device + vtable->readyAdjustment) == 1) {
            func_0028F3B0(self->stream, self->pending);
            self->pending = 0;
        }
    }
}
s32 func_00271B50(s32 unused1, s32 unused2, Recovered_StreamControl *self) {
    if (func_002719A8((s32)self) != 0) {
        if (self->active == 0) {
            func_00271AF0(self);
            func_0028F408(self->stream);
            func_002719D0(self, 1);
        } else {
            self->unk_45 = 1;
            func_0028F3B0(self->stream, 0x10000);
            func_0028F408(self->stream);
        }
    } else {
        func_0028F408(self->stream);
    }
    return 1;
}
