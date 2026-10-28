#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00209E78(void) { return 1; }

// Partial resource table views; original type and field meanings are UNVERIFIED.
typedef struct {
    s32 type, value, key, references, unknown10;
} ResourceTableEntry;
typedef struct {
    s32 unknown00;
    ResourceTableEntry entries[112];
} ResourceTable;
extern void func_00209D10(ResourceTableEntry*);
extern void func_00209CC0(void*);
#ifdef NON_MATCHING
// Unmatched: key cursor and branch scheduling differ.
ResourceTableEntry* func_00209E80(ResourceTable* self, s32 key) {
    s32 i;
    for (i = 0; i < 112; i++) {
        ResourceTableEntry* entry = &self->entries[i];
        if (entry->key == key) {
            entry->references++;
            return entry;
        }
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209e78", func_00209E80);
#endif
#ifdef NON_MATCHING
// Unmatched: key cursor and setup scheduling differ.
extern void func_00209BD8(void*, s32, s32);
s32 func_00209EC8(ResourceTable* self, s32 key, s32 value) {
    s32 i;
    for (i = 0; i < 112; i++) {
        ResourceTableEntry* entry = &self->entries[i];
        if (entry->key == key || entry->key == -1) {
            func_00209BD8(entry, key, value);
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209e78", func_00209EC8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209e78", func_00209F28);
#ifdef NON_MATCHING
// Unmatched: key cursor and setup scheduling differ.
extern void func_00209C08(void*, s32, s32);
s32 func_00209F38(ResourceTable* self, s32 key, s32 value) {
    s32 i;
    for (i = 0; i < 112; i++) {
        ResourceTableEntry* entry = &self->entries[i];
        if (entry->key == key || entry->key == -1) {
            func_00209C08(entry, key, value);
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209e78", func_00209F38);
#endif
#ifdef NON_MATCHING
// Unmatched: key cursor and setup scheduling differ.
extern void func_00209C38(void*, s32, s32);
s32 func_00209F98(ResourceTable* self, s32 key, s32 value) {
    s32 i;
    for (i = 0; i < 112; i++) {
        ResourceTableEntry* entry = &self->entries[i];
        if (entry->key == key || entry->key == -1) {
            func_00209C38(entry, key, value);
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209e78", func_00209F98);
#endif
s32 func_00209FF8(ResourceTable* self, s32 key) {
    s32 i;
    for (i = 0; i < 112; i++) {
        ResourceTableEntry* entry = &self->entries[i];
        if (entry->key == key) {
            func_00209D10(entry);
            func_00209CC0(entry);
            return 1;
        }
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209e78", func_0020A058);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209e78", func_0020A220);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209e78", func_0020A338);
