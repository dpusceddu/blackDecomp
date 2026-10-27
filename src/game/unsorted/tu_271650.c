#include "include_asm.h"
#include "game/aligned_buffer.h"
#include "game/stream_control.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0028F618(s32);
extern s32 func_0028F718(s32);
extern s32 func_0028FA60(s32);
extern void func_0028F3B0(void *, s32);
extern void func_0028F408(void *);

extern void func_002719D0(Recovered_StreamControl *, s32);

#ifdef NON_MATCHING
#include "ps2/ee_types.h"
extern EeU128* D_0040E5F0;
extern void func_002B3D88(s32, s32);

/* Native 64-bit pair transport, as used by the other packet builders. */
static inline EeU128 PackStreamPacket(u64 high, u64 low) {
    EeU128 packet;
    __asm__("pcpyld pv, hv, lv" : "=r pv"(packet) : "r hv"(high), "r lv"(low));
    return packet;
}
#endif

void func_00271650(Recovered_StreamRecord* self) {
    self->buffer = 0;
    self->unk_04 = -1;
    self->unk_08 = -1;
}

s32 func_00271668(Recovered_StreamRecord* self, Recovered_AlignedBuffer* allocator, s32 width, s32 height, s32 value) {
    s32 columns = width / 4;
    s32 rows = height / 4;
    self->unk_14 = value;
    self->unk_0C = width;
    self->unk_10 = height;
    self->unk_04 = columns;
    self->unk_08 = rows;
    if (width != columns * 4) self->unk_04 = columns + 1;
    if (height != rows * 4) self->unk_08 += 1;
    self->buffer = AlignedBuffer_Allocate(allocator, (u32)(self->unk_0C * self->unk_10) << 10);
    return 1;
}

void func_00271710(Recovered_StreamRecord* self) {
    self->buffer = 0;
    self->unk_04 = -1;
    self->unk_08 = -1;
}

#ifdef NON_MATCHING
// Unmatched: quadword commoning and packet-cursor register lifetimes differ.
void func_00271728(Recovered_StreamRecord* self, s32 row, s32 column) {
    u8* source = (u8*)self->buffer + (((row << 2) * self->unk_10) << 10) + (column << 12);
    EeU128* packet;
    s32 i;
    func_002B3D88(0, 0x20);
    packet = D_0040E5F0;
    *packet++ = PackStreamPacket((((u64)0xA000 << 28) | 0x8000) << 19, 0x10000004);
    *packet++ = PackStreamPacket(14, ((u64)0x8000 << 45) | 0x8003);
    *packet++ = PackStreamPacket(0x50, ((u64)self->unk_14 << 32) | ((u64)0x8000 << 33));
    *packet++ = PackStreamPacket(0x52, ((u64)0x8000 << 23) | 0x10);
    *packet++ = PackStreamPacket(6, (u64)self->unk_14 | 0x18004000 | ((u64)0xC000 << 17));
    for (i = 0; i < 4; ++i) {
        *packet++ = PackStreamPacket((((u64)0xA000 << 28) | 0x8000) << 19, 0x10000004);
        *packet++ = PackStreamPacket(14, ((u64)0x8000 << 45) | 0x8002);
        *packet++ = PackStreamPacket(0x51, (u64)(i << 4) << 32);
        *packet++ = PackStreamPacket(0x53, 0);
        *packet++ = PackStreamPacket(0, ((u64)0x8000 << 44) | 0x100 | (i == 3 ? 0x8000 : 0));
        *packet++ = PackStreamPacket((((u64)0xA000 << 22) | 0x8000) << 25,
                                   ((u64)(u32)source << 32) | 0x30000100);
        source += self->unk_10 << 10;
    }
    *packet++ = PackStreamPacket((((u64)0xA000 << 29) | 0x8000) << 18, 0x10000002);
    *packet++ = PackStreamPacket(14, ((u64)0x8000 << 45) | 0x8001);
    *packet++ = PackStreamPacket(0x3F, 0);
    D_0040E5F0 = packet;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650", func_00271728);
#endif

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
