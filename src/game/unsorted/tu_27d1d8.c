#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003C0E04;

/* Partial serialized view; the prefix and discriminator meaning are UNVERIFIED. */
typedef struct {
    u8 unk_00[0x20];
    u32 dataOffset;
    u32 recordsOffset;
    u16 recordCount;
    u16 unk_2A;
    s32 unk_2C;
} Recovered_RelocatableRecords;

extern s32 func_0027F708(void* record);
extern s32 func_0027F6D8(void* record);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027D1D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027D7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027DD60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E308);
void func_0027E760(Recovered_RelocatableRecords* self) {
    u16 i;

    if (self->dataOffset) { self->dataOffset = (u32)self + self->dataOffset; }
    if (self->recordsOffset) { self->recordsOffset = (u32)self + self->recordsOffset; }
    if (self->unk_2C) {
        for (i = 0; i < self->recordCount; i++) { func_0027F708((void*)(self->recordsOffset + i * 16)); }
    } else {
        for (i = 0; i < self->recordCount; i++) { func_0027F6D8((void*)(self->recordsOffset + i * 16)); }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E820);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027E9B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027EFE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027EFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F1C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F338);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F518);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F5D0);

s32 func_0027F5E0(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F5E8);
/* This native encoding uses fixed 31-day months and 372-day years. */
typedef struct {
    u16 year, month, day, hour, minute, second;
} CalendarFields;
u32 func_0027F640(CalendarFields *date) {
    return date->second + date->minute * 60 + date->hour * 3600 + (date->day - 1) * 86400 + (date->month - 1) * 2678400 + (date->year % 100) * 32140800;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F6B8);

void func_0027F778(void) { D_003C0E04 += 1; }
