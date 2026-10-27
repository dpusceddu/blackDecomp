#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/stream_control.h"

#include "ps2/recovered_types.h"
extern "C" s32 func_00271650(void *);
extern "C" s32 func_00294A08();

extern "C" s32 func_00271BE8(s32 *arg0) {
    s32 *var_16;

    var_16 = arg0;
    do {
        func_00271650(var_16);
        var_16 = (s32 *) (((s8 *) var_16) + 0x18);
    } while ((s32) var_16 < (s32) ((s32 *) (((s8 *) arg0) + 0x30)));
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x118) = 0;
    M2C_FIELD(arg0, s32 *, 0x120) = 1;
    return func_00294A08();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650_271be8", func_00271C50);
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

extern "C" void func_00271710(void*);
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
