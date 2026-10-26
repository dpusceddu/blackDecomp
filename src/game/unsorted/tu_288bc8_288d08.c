#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"
#include "ps2/prototypes.h"

extern char D_00400A08[];
const char rodata_00400A08[104] __asm__("D_00400A08") __attribute__((aligned(8))) = "%d" "\000\000\000\000\000\000" "RawData" "\000" "Graph" "\000\000\000" "AdditionalData" "\000\000" "CFindNearestData" "\000\000\000\000\000\000\000\000" "CAstarData" "\000\000\000\000\000\000" "UpdateWithPathObjects" "\000\000\000";
extern s32 func_0035D728();

extern void *func_002E3408(PS2KaimChildBuffer *);
extern void *D_003E2990[];

typedef struct {
    u8 unk_00[0x30];
    s16 adjustment;
    u16 unk_32;
    u32 (*allocate)(void *, u32, void **);
} Recovered_ChildAllocatorVtable;
typedef struct {
    Recovered_ChildAllocatorVtable *vtable;
} Recovered_ChildAllocator;
extern Recovered_ChildAllocator *D_003C87E8;
extern void (*D_003C87EC)(void *, u32, u32);
extern PS2KaimChildBuffer **func_00288EF8(PS2KaimChildBuffer **, PS2KaimChildBuffer **, char *, char *);

s32 func_00288D08(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 4);
}

#ifdef NON_MATCHING
// Unmatched: allocator output initialization scheduling differs.
PS2KaimChildBuffer *func_00288D10(PS2KaimChildBuffer *self, char *first, char *value, char *name, u32 capacity) {
    func_002E3408(self);
    self->vtable = D_003E2990;
    if (first != 0) func_002E3578(self, first);
    if (name != 0) func_002E3630(self, name);
    if (value != 0) func_002E36E8(self, value);
    if (capacity != 0) {
        PS2KaimChildBuffer **block;
        u32 bytes;
        Recovered_ChildAllocatorVtable *vtable;
        u32 tag;
        self->count = 0;
        block = 0;
        bytes = capacity * 4;
        vtable = D_003C87E8->vtable;
        tag = vtable->allocate((u8 *)D_003C87E8 + vtable->adjustment, bytes, (void **)&block);
        if (D_003C87EC != 0) D_003C87EC(block, bytes, tag);
        self->capacity = capacity;
        self->children = block;
    }
    return self;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288D10);

s32 func_00288E00(s32 arg0, s32 arg1) {
    s32 *temp_2;
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x20);
    temp_2 = (temp_3 * 4) + M2C_FIELD(arg0, s32 *, 0x18);
    *temp_2 = arg1;
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (temp_3 + 1);
    return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288E20);
#ifdef NON_MATCHING
// Unmatched: allocator-call scheduling and parameter registers differ.
PS2KaimChildBuffer **func_00288E28(PS2KaimChildBuffer **out, PS2KaimChildBuffer **parent, char *first,
                                    char *value, char *name, u32 capacity) {
    void *block = 0;
    Recovered_ChildAllocatorVtable *vtable = D_003C87E8->vtable;
    u32 tag = vtable->allocate((u8 *)D_003C87E8 + vtable->adjustment, 0x24, &block);
    PS2KaimChildBuffer *child;
    if (D_003C87EC != 0) D_003C87EC(block, 0x24, tag);
    child = func_00288D10((PS2KaimChildBuffer *)block, first, value, name, capacity);
    func_00288E00((s32)*parent, (s32)child);
    *out = child;
    return out;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288E28);

#ifdef NON_MATCHING
// Unmatched: allocator-call scheduling and parameter registers differ.
PS2KaimChildBuffer **func_00288EF8(PS2KaimChildBuffer **out, PS2KaimChildBuffer **parent, char *name, char *value) {
    void *block = 0;
    Recovered_ChildAllocatorVtable *vtable = D_003C87E8->vtable;
    u32 tag = vtable->allocate((u8 *)D_003C87E8 + vtable->adjustment, 0x24, &block);
    PS2KaimChildBuffer *child;
    if (D_003C87EC != 0) D_003C87EC(block, 0x24, tag);
    child = func_00288D10((PS2KaimChildBuffer *)block, 0, value, name, 0);
    func_00288E00((s32)*parent, (s32)child);
    *out = child;
    return out;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288EF8);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00288FB0);

M2C_UNK *** func_00289028(M2C_UNK ***arg0, M2C_UNK ***arg1, M2C_UNK *arg2, M2C_UNK *arg3) {
    u8 sp[8];
    func_0035D728(sp, D_00400A08, arg3);
    func_00288EF8((PS2KaimChildBuffer **)arg0, (PS2KaimChildBuffer **)arg1, (char *)arg2, (char *)sp);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288bc8_288d08", func_00289090);
