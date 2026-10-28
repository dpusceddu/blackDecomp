#include "include_asm.h"
#include "ps2/prelude.h"

extern u64 func_00290AC0(u64, u64);
extern u64 func_002904F0(u64, u64);
#ifdef NON_MATCHING
// Unmatched: digit decoding branches and register allocation differ.
void func_00272488(u64 name, char* output) {
    s32 i = 11;
    do {
        s8 digit = (s8)func_00290AC0(name, 40);
        s8 character;
        if (digit == 39) character = '_';
        else if (digit >= 13) character = digit + 0x34;
        else if (digit >= 3) character = digit + 0x2D;
        else if (digit == 2) character = '/';
        else if (digit == 1) character = '-';
        else character = digit == 0 ? ' ' : 0;
        output[i] = character;
        i--;
        name = func_002904F0(name, 40);
    } while (i >= 0);
    output[12] = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_00272488);
#endif
extern u64 D_00400510[];
u64 func_00272580(u64 name, s32 first, s32 last) {
    if (first > 0) name = func_00290AC0(name, D_00400510[12 - first]);
    if (last < 11) name -= func_00290AC0(name, D_00400510[11 - last]);
    return name;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_00272608);
u64 func_00272610(u64 first, u64 second) {
    s32 i = 0;
    while (i < 12 && func_00290AC0(first, D_00400510[i + 1]) == 0) i++;
    if (i == 0) return first;
    if (i == 12) return second;
    return first + func_002904F0(second, D_00400510[12 - i]);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_002726C8);
// UNVERIFIED: original header identity and fields before the count.
typedef struct { u8 unknown[8]; s32 count; u32* entries; } Recovered_OffsetList;
void func_00272730(Recovered_OffsetList* self) {
    s32 i = 0;
    self->entries = (u32*)((u32)self->entries + (u32)self);
    if (self->count > 0) {
        do {
            u32* entry = (u32*)(i * 4 + (u32)self->entries);
            if (*entry) *entry += (u32)self;
            i++;
        } while (i < self->count);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_00272788);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_002728C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_002728D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_00272960);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_00272A58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272488", func_00272A60);
// UNVERIFIED: entry identity and untouched fields.
typedef struct { u8 unknown[8]; u32 offset; u32 unknown0C; } Recovered_OffsetRecord;
typedef struct { u8 unknown[8]; s32 count; Recovered_OffsetRecord* entries; } Recovered_OffsetRecords;
void func_00272AA8(Recovered_OffsetRecords* self) {
    s32 i = 0;
    self->entries = (Recovered_OffsetRecord*)((u32)self->entries + (u32)self);
    if (self->count > 0) {
        do {
            Recovered_OffsetRecord* entry = (Recovered_OffsetRecord*)(i * 16 + (u32)self->entries);
            i++;
            entry->offset += (u32)self;
        } while (i < self->count);
    }
}

#include "ps2/recovered_types.h"
extern s32 func_00272B78(void *);

s32 func_00272AF8(void *arg0, s32 arg1, s32 arg2, u32 arg3, f32 fparg0) {
    M2C_FIELD(arg0, s32 *, 0x34) = arg1;
    M2C_FIELD(arg0, s32 *, 0x38) = arg2;
    M2C_FIELD(arg0, u32 *, 0x40) = arg3;
    M2C_FIELD(arg0, f32 *, 0x20) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x24) = 300.0f;
    M2C_FIELD(arg0, f32 *, 0x28) = 150.0f;
    M2C_FIELD(arg0, f32 *, 0x2C) = 75.0f;
    M2C_FIELD(arg0, f32 *, 0x30) = 10.0f;
    return func_00272B78(arg0);
}
