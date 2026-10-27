#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/stream_control.h"
#include "game/aligned_buffer.h"

extern "C" void func_00271650(Recovered_StreamRecord*);
extern "C" s32 func_00294A08();

extern "C" s32 func_00271BE8(Recovered_StreamControl* self) {
    Recovered_StreamRecord* record = self->records;
    do {
        func_00271650(record);
        ++record;
    } while ((s32)record < (s32)(self->records + 2));
    self->unk_58 = 0;
    self->unk_5C = 0;
    self->unk_60 = 0;
    self->unk_118 = 0;
    self->state = 1;
    return func_00294A08();
}

#ifdef NON_MATCHING
extern "C" {
void* func_0027C778(const char*);
Recovered_StreamDevice* func_0027CAB8(void*, const char*, s32);
s32 func_00271668(Recovered_StreamRecord*, Recovered_AlignedBuffer*, s32, s32, s32);
s32 func_00293F60(void*, void*, s32);
s32 func_00294BB0(void*, s32, s32 (*)(s32, s32, Recovered_StreamControl*), Recovered_StreamControl*);
s32 func_00271B50(s32, s32, Recovered_StreamControl*);
s32 func_00271968(s32, s32, Recovered_StreamControl*);
s32 func_00271988(s32, s32, Recovered_StreamControl*);
s32 func_0028F0E8(void*, void*, void*, s32, s32, s32);
s32 func_0028F160(void*);
s32 func_00294B18(void*);
void func_002719D0(Recovered_StreamControl*, s32);
void func_00271AF0(Recovered_StreamControl*);
s32 func_0028FA60(void*);
}

// Unmatched: flags and loop-bit saved registers are exchanged.
extern "C" s32 func_00271C50(Recovered_StreamControl* self, Recovered_AlignedBuffer* allocator, s32 width, s32 height,
                            const char* name, s32 flags, f32 rate) {
    switch (self->state) {
        case 1:
        case 0x38: {
            self->device = func_0027CAB8(func_0027C778(name), name, 0x11);
            if (self->device != 0) {
                void* decoder = self->unk_70;
                s32 alignment = allocator->alignment;
                AlignedBuffer_SetAlignment(allocator, 0x80);
                u8 loop = flags & 1;
                s32 bytes = width * height * 9 / 2 + 0x2800;
                self->unk_38 = rate;
                self->unk_3C = rate;
                self->unk_48 = width / 16;
                self->unk_4C = height / 16;
                self->unk_50 = self->unk_48 * self->unk_4C;
                self->unk_5C = AlignedBuffer_Allocate(allocator, bytes);
                self->unk_58 = AlignedBuffer_Allocate(allocator, 0x100000);
                self->unk_60 = AlignedBuffer_Allocate(allocator, 0x110);
                Recovered_StreamRecord* record = self->records;
                do {
                    func_00271668(record, allocator, self->unk_48, self->unk_4C, self->unk_118);
                    ++record;
                } while ((s32)record < (s32)(self->records + 2));
                AlignedBuffer_SetAlignment(allocator, alignment);
                func_00293F60(decoder, self->unk_5C, bytes);
                func_00294BB0(decoder, 1, func_00271B50, self);
                func_00294BB0(decoder, 2, func_00271968, self);
                func_00294BB0(decoder, 3, func_00271988, self);
                func_0028F0E8(self->stream, self->unk_58, self->unk_60, 0x10, 0, 0);
                self->unk_54 = flags;
                self->unk_43 = loop;
                self->unk_11C = 0;
                self->unk_41 = 0;
                self->unk_42 = 0;
                self->active = 0;
                self->unk_45 = 0;
                self->unk_46 = 0;
                self->pending = 0;
                self->unk_34 = 0;
                self->selected = -1;
                self->unk_40 = 1;
                self->unk_30 = -1;
                func_0028F160(self->stream);
                func_00294B18(decoder);
                func_002719D0(self, 8);
                self->state = 2;
            } else {
                return 0;
            }
        }
        case 2:
            func_00271AF0(self);
            if (func_0028FA60(self->stream) <= 0x10000) return 0;
            self->state = 0x1C;
            break;
        default:
            break;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650_271be8", func_00271C50);
#endif

extern "C" {
f32 func_0029D950(f32);
void func_00271AF0(Recovered_StreamControl*);
void func_002719D0(Recovered_StreamControl*, s32);
s32 func_0028FA60(void*);
s32 func_00294AC8(void*, void*, s32);
s32 func_00294B98(void*);
s32 func_0028F160(void*);
s32 func_00294B18(void*);
}

extern "C" void func_00271F10(Recovered_StreamControl* self) {
    if (!self->unk_40) return;
    if (self->unk_46 && !self->unk_42) return;
    if (self->unk_42) {
        s32 ready = self->device->ready();
        switch (ready) {
            case 1:
                self->device->release();
                break;
            case 0:
                self->unk_42 = 0;
                self->device = 0;
                self->unk_40 = 0;
                self->unk_43 = 0;
                self->unk_41 = 1;
                break;
        }
        return;
    }
    s32 frame = (s32)func_0029D950(self->unk_34 / self->unk_38);
    func_00271AF0(self);
    func_002719D0(self, 1);
    if (self->unk_30 < frame && (func_0028FA60(self->stream) > 0x10000 || self->active == 1)) {
        s32 remaining = frame - self->unk_30;
        if (remaining >= 3) remaining = 2;
        do {
            if (remaining == 0) break;
            --remaining;
            func_00294AC8(self->unk_70, self->records[self->unk_11C].buffer, self->unk_50);
            ++self->unk_30;
        } while (!func_00294B98(self->unk_70));
        self->unk_11C = (s8)(self->unk_11C + 1) % 2;
        self->selected = (s8)(self->selected + 1) % 2;
        if (func_00294B98(self->unk_70) || self->unk_45) {
            func_0028F160(self->stream);
            func_00294B18(self->unk_70);
            if (!self->unk_43) {
                self->unk_42 = 1;
            } else {
                self->unk_30 = -1;
                self->unk_45 = 0;
                self->unk_34 = 0;
                if (self->active) {
                    self->active = 0;
                } else {
                    while (self->device->ready() != 1) {}
                    self->device->reset(0, 0);
                }
                func_002719D0(self, 8);
            }
        }
    }
    if (!(self->unk_54 & 2)) self->unk_34 += self->unk_3C;
}

extern "C" void func_00271710(Recovered_StreamRecord*);
extern "C" void func_0028FA08(void*);
extern "C" s32 func_00294AB8(void*);

extern "C" void func_002721D8(Recovered_StreamControl* self) {
    Recovered_StreamRecord* record = self->records;
    do {
        func_00271710(record);
        ++record;
    } while ((s32)record < (s32)(self->records + 2));
    func_0028FA08(self->stream);
    func_00294AB8(self->unk_70);
    self->unk_58 = 0;
    self->unk_5C = 0;
    self->unk_60 = 0;
    if (self->device != 0) {
        while (self->device->ready() == 2) {}
        if (self->device->ready() == 1) {
            self->device->release();
        }
        self->device = 0;
    }
    self->state = 0x38;
}
