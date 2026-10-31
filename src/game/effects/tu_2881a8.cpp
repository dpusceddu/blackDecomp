#include "ps2/prelude.h"

// Partial relocation views; original class identities and untouched fields are UNVERIFIED.
struct SceneRelocationView {
    u8 unknown00[0x20];
    u32 field20, unknown24, field28, unknown2C, field30, unknown34, field38, unknown3C;
    u32 field40, unknown44, field48, unknown4C, field50, unknown54, field58, unknown5C;
    u32 field60, unknown64, field68, unknown6C, field70, unknown74, field78, unknown7C;
    u32 field80;
    u8 unknown84[0x2B8];
    u32 field33C;
    void* field340;
    u8 unknown344[0xC];
    u32 field350;
    u8 unknown354[0x3C];
    void *field390, *field394, *field398;
    u32 field39C;
};
extern "C" void func_00288470(u32*);
extern "C" void func_0028B848(void*);
extern "C" void func_00272AA8(void*);
extern "C" void* func_003822E0(void*, s32);
extern "C" void func_0028EED8(void*);
extern "C" void func_00286E30(void*);

static inline void RelocateField(u32* offset) {
    if (*offset) *offset += (u32)offset;
}

extern "C" void func_002881A8(SceneRelocationView* self) {
    s32 i;
    void *list, *secondList, *thirdList, *table;
    s16 count;
    func_00288470((u32*)((u8*)self + 4));
    RelocateField(&self->field20);
    RelocateField(&self->field28);
    RelocateField(&self->field30);
    RelocateField(&self->field38);
    RelocateField(&self->field40);
    RelocateField(&self->field48);
    RelocateField(&self->field50);
    RelocateField(&self->field60);
    RelocateField(&self->field58);
    RelocateField(&self->field68);
    RelocateField(&self->field70);
    RelocateField(&self->field78);
    RelocateField(&self->field80);
    if (self->field33C) self->field33C += (u32)self;
    if (self->field340) self->field340 = (void*)((u32)self->field340 + (u32)self);
    if (self->field390) self->field390 = (void*)((u32)self->field390 + (u32)self);
    if (self->field394) self->field394 = (void*)((u32)self->field394 + (u32)self);
    if (self->field350) self->field350 += (u32)self;
    if (self->field398) self->field398 = (void*)((u32)self->field398 + (u32)self);
    if (self->field39C) self->field39C += (u32)self;
    table = self->field340;
    count = M2C_FIELD(table, s16*, 0x16);
    M2C_FIELD(table, void**, 0x18) = (void*)((u32)M2C_FIELD(table, void**, 0x18) + (u32)table);
    // The native code retains this empty signed-short initialization walk.
    for (s16 element = 0; element < count; ++element) {}
    i = 0;
    func_0028B848((void*)self->field33C);
    list = self->field390;
    func_00272AA8(list);
    for (; i < M2C_FIELD(list, s32*, 8); ++i) func_0028EED8(func_003822E0(list, i));
    secondList = self->field398;
    i = 0;
    func_00272AA8(secondList);
    for (; i < M2C_FIELD(secondList, s32*, 8); ++i) func_0028EED8(func_003822E0(secondList, i));
    thirdList = self->field394;
    i = 0;
    func_00272AA8(thirdList);
    for (; i < M2C_FIELD(thirdList, s32*, 8); ++i) func_0028EED8(func_003822E0(thirdList, i));
    func_00286E30((void*)self->field350);
}
