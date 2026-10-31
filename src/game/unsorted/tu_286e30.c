#include "include_asm.h"
#include "ps2/prelude.h"

#ifdef NON_MATCHING
// Unmatched: two inner-loop cursor/index initialization instructions are ordered differently.
// Partial native views; original class identities remain UNVERIFIED.
typedef struct SceneBranchView {
    u8 unknown0[8];
    u32 field8, fieldC, field10, field14, field18, field1C, field20, field24, field28, field2C;
    u16 count30, count32, unknown34, count36, count38;
} SceneBranchView;
extern void func_00272AA8(void*);
extern void func_00287100(void*);
extern void func_002870F8(void*);
extern void func_0028C028(void*);
extern void* func_003822E0(void*, s32);
extern void func_0028EED8(void*);
extern void* func_00388E58(void*, s32);

void func_00286E30(SceneBranchView* self) {
    s32 i;
    void *list, *row;
    u32* cursor;
    s16 j;
    if (self->field8) self->field8 += (u32)self;
    if (self->fieldC) self->fieldC += (u32)self;
    if (self->field10) self->field10 += (u32)self;
    if (self->field18) self->field18 += (u32)self;
    if (self->field24) self->field24 += (u32)self;
    if (self->field1C) self->field1C += (u32)self;
    if (self->field14) self->field14 += (u32)self;
    if (self->field28) self->field28 += (u32)self;
    if (self->field2C) self->field2C += (u32)self;
    if (self->field20) self->field20 += (u32)self;
    i = 0;
    func_00272AA8((void*)self->field8);
    for (; (u32)i < self->count30; i = (u16)(i + 1)) func_00287100((void*)(self->field10 + i * 0x34));
    for (i = 0; (u32)i < self->count32; i = (u16)(i + 1)) {
        u32* first = (u32*)(i * 4 + self->field18);
        u32* second;
        if (*first) *first += (u32)self;
        second = (u32*)(i * 4 + self->field24);
        if (*second) *second += (u32)self;
    }
    for (i = 0; (u32)i < self->count36; i = (u16)(i + 1)) func_0028C028((void*)(self->field28 + i * 0xF0));
    for (i = 0; (u32)i < self->count38; i = (u16)(i + 1)) func_002870F8((void*)(self->field2C + i * 0xC0));
    list = (void*)self->field14;
    i = 0;
    func_00272AA8(list);
    for (; i < M2C_FIELD(list, s32*, 8); ++i) func_0028EED8(func_003822E0(list, i));
    if (self->fieldC) {
        i = 0;
        func_00272AA8((void*)self->fieldC);
        if (M2C_FIELD(self->fieldC, s32*, 8) > 0) do {
                s32 next;
                row = func_00388E58((void*)self->fieldC, i);
                next = i + 1;
                if (M2C_FIELD(row, s16*, 0) > 0) {
                    j = 0;
                    cursor = (u32*)((u8*)row + 4);
                    do {
                        *cursor += self->field8;
                        ++cursor;
                        ++j;
                    } while (j < M2C_FIELD(row, s16*, 0));
                }
                i = (u16)next;
            } while (i < M2C_FIELD(self->fieldC, s32*, 8));
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_286e30", func_00286E30);
#endif

void func_002870F8(void *element) {

}

void func_00287100(void *element) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_286e30", func_00287108);
