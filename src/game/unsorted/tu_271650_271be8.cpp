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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650_271be8", func_00271F10);
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
