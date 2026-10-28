#include "game/stream_control.h"
extern "C" s32 func_0028F2C0(void*, u32*, s32*, u32*, u32*);
extern "C" void func_002719D0(Recovered_StreamControl* self, s32 amount) {
    u32 start;
    s32 length;
    u32 next;
    u32 unused;
    s32 ready;
    if (self->pending != 0) return;

    ready = self->device->ready();
    if (ready != 1 || self->active == 1) return;

    func_0028F2C0(self->stream, &start, &length, &next, &unused);
    start = (start & 0x0FFFFFFF) | 0x20000000;
    next = (next & 0x0FFFFFFF) | 0x20000000;
    if (length >= (amount << 16)) {
        if (self->device->begin(start, amount << 16) <= 0) {
            self->active = ready;
            if (self->unk_43 != 0) {
                self->device->reset(0, 0);
            }
        }
        self->pending = amount << 16;
    }
}
