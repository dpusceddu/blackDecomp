#include "ps2/prelude.h"
// UNVERIFIED class identity; native offsets and record strides.
typedef struct SceneMaterialsView {
    u8 unknown0[0x24];
    u32 firstCount, secondCount, unknown2C, field30, field34, field38, field3C, field40;
} SceneMaterialsView;
extern void func_0028B940(void*);
extern void func_0028BB98(void*);
void func_0028B848(SceneMaterialsView* self) {
    u32 i, offset;
    if (self->field34) self->field34 += (u32)self;
    if (self->field38) self->field38 += (u32)self;
    if (self->field30) self->field30 += (u32)self;
    if (self->field3C) self->field3C += (u32)self;
    if (self->field40) self->field40 += (u32)self;
    for (i = 0; i < self->firstCount; ++i) func_0028B940((void*)(self->field34 + i * 16));
    i = 0;
    if (self->secondCount) {
        offset = 0;
        do {
            func_0028BB98((void*)(self->field38 + offset));
            ++i;
            offset += 0x30;
        } while (i < self->secondCount);
    }
}
