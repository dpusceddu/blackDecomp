#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/vu0_lowering.h"

typedef struct {
    f32 x, y, z, w;
} VectorFields __attribute__((aligned(16)));

static inline f32 DotXYZ(BkVuVector a, BkVuVector b, BkVuVector one) {
    return __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(a, b), one));
}

static inline BkVuVector AddW(BkVuVector a, BkVuVector b) {
    BkVuVector result;
    __asm__("vaddw.w outv, av, bvw" : "=j outv"(result) : "j av"(a), "j bv"(b));
    return result;
}

static inline BkVuVector SubW(BkVuVector a, BkVuVector b) {
    BkVuVector result;
    __asm__("vsubw.w outv, av, bvw" : "=j outv"(result) : "j av"(a), "j bv"(b));
    return result;
}

static inline f32 ReadW(BkVuVector value) {
    VectorFields spill;
    *(BkVuVector*)&spill = value;
    return spill.w;
}

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
s32 func_0027EFE8(BkVuVector a, BkVuVector b) {
    f32 radii = ReadW(AddW(a, b));
    f32 distance = DotXYZ(BkVuSubXYZ(a, b), BkVuSubXYZ(a, b), BkVuOneX());
    f32 difference;
    if (radii * radii < distance) return 0;
    difference = ReadW(SubW(b, a));
    if (difference < 0.0f) return 1;
    if (distance < difference * difference) return 2;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F1C0);
s32 func_0027F218(BkVuVector point, BkVuVector normal, BkVuVector a, BkVuVector b, BkVuVector c, BkVuVector d) {
    BkVuVector one = BkVuOneX();
    if (DotXYZ(BkVuCrossXYZ(normal, BkVuSubXYZ(b, a)), BkVuSubXYZ(point, a), one) < 0.0f) return 0;
    if (DotXYZ(BkVuCrossXYZ(normal, BkVuSubXYZ(c, b)), BkVuSubXYZ(point, b), one) < 0.0f) return 0;
    if (DotXYZ(BkVuCrossXYZ(normal, BkVuSubXYZ(d, c)), BkVuSubXYZ(point, c), one) < 0.0f) return 0;
    if (DotXYZ(BkVuCrossXYZ(normal, BkVuSubXYZ(a, d)), BkVuSubXYZ(point, d), one) < 0.0f) return 0;
    return 1;
}
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
u32 func_0027F640(CalendarFields* date) {
    return date->second + date->minute * 60 + date->hour * 3600 + (date->day - 1) * 86400 +
           (date->month - 1) * 2678400 + (date->year % 100) * 32140800;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27d1d8", func_0027F6B8);

void func_0027F778(void) {
    D_003C0E04 += 1;
}
