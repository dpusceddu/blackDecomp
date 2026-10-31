#include "ps2/prelude.h"
// Partial section access views; original class identities remain UNVERIFIED.
typedef struct SectionView {
    u32 field0, records;
    s32 count;
    u32 header, nodes, models, textures;
} SectionView;
typedef struct SectionRowView {
    u8 unknown[0x18];
    u32 first, second;
    s32 firstCount, secondCount;
} SectionRowView;
extern void* D_0040F4C4;
extern void func_00272AA8(void*);
extern void* func_003822E0(void*, s32);
extern void* func_003822F8(void*, s32);
extern void* func_00383738(void*, s32);
extern void func_0028EED8(void*);
extern void func_001AF930(void*);
extern void func_00108540(void*, s32, void*, s32);
extern void func_00388E70(void*);
extern void func_00288A38(void*);
extern s32 func_00110A88(void*);
void func_00288488(SectionView* self) {
    s32 i, j, next;
    void* list;
    SectionRowView* row;
    self->header += (u32)self;
    self->records += (u32)self;
    self->nodes += (u32)self;
    if (self->textures) {
        list = (void*)(self->textures + (u32)self);
        i = 0;
        self->textures = (u32)list;
        func_00272AA8(list);
        for (; i < M2C_FIELD(list, s32*, 8); ++i) func_0028EED8(func_003822E0(list, i));
        func_00108540(D_0040F4C4, 0, (void*)self->textures, 0);
    }
    if (self->models) {
        list = (void*)(self->models + (u32)self);
        i = 0;
        self->models = (u32)list;
        func_00272AA8(list);
        for (; i < M2C_FIELD(list, s32*, 8); ++i) func_001AF930(func_003822F8(list, i));
        func_00108540(D_0040F4C4, 1, (void*)self->models, 0);
    }
    for (i = 0; i < self->count; i = next) {
        next = i + 1;
        row = (SectionRowView*)(i * 0x28 + self->records);
        row->first += (u32)row;
        row->second += (u32)row;
        for (j = 0; j < row->firstCount; ++j) func_00388E70((void*)(row->first + j * 0xB0));
        for (j = 0; j < row->secondCount; ++j) func_00388E70((void*)(row->second + j * 0xB0));
    }
    i = 0;
    func_00288A38((void*)self->header);
    func_00272AA8((void*)self->nodes);
    if (M2C_FIELD(self->nodes, s32*, 8) > 0) do {
            s32 index = i;
            ++i;
            func_00110A88(func_00383738((void*)self->nodes, index));
        } while (i < M2C_FIELD(self->nodes, s32*, 8));
}
