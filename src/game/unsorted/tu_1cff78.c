#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/ee_types.h"

extern s32 D_0040EB00;
extern s32 D_0040EB04;
extern s32 D_0040EB18;
extern s32 func_00108328();
extern s32 D_0040F4C4;
extern void *D_0048F770[];
extern void *D_0048F990[];
extern EeS128 D_004165C0;
extern float D_0040EB08;

void func_001CFF78(void) {
    D_0040EB00 = -1;
    D_0040EB04 = -1;
}

void func_001CFF90(EeS128 value, float f) {
    D_004165C0 = value;
    D_0040EB00 = 0;
    D_0040EB04 = 0;
    D_0040EB08 = f;
}

void func_001CFFB8(void *item, int flag) {
    D_0048F770[D_0040EB00++] = item;
    if (flag) {
        D_0048F990[D_0040EB04++] = item;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D0010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D0A68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D0AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D0B20);
#ifdef NON_MATCHING
/* UNVERIFIED: partial layouts inferred from this function's accesses. */
typedef struct Unk1D0D10Data {
    char pad[0x9C];
    float value;
} Unk1D0D10Data;
typedef struct Unk1D0D10Item {
    float time;
    Unk1D0D10Data *data;
    char pad[0x5C];
    float limit;
} Unk1D0D10Item;
typedef struct Unk1D0D10Clock {
    char pad[0x20];
    float now;
} Unk1D0D10Clock;
extern Unk1D0D10Clock *D_0040F4D0;
extern s32 D_0040EB0C;
extern float D_0040EB14;
extern Unk1D0D10Item *D_0048FAA0[];

// Unmatched: list insertion register allocation and scheduling differ.
void func_001D0D10(Unk1D0D10Item *item) {
    if (D_0040F4D0->now - item->time < item->limit) {
        D_0048FAA0[D_0040EB0C++] = item;
        D_0040EB14 = __ee_max_s(D_0040EB14, item->data->value);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D0D10);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D0D80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D0EA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D0EF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D1188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D1218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D1268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D14E0);
/* UNVERIFIED: partial layouts inferred from the accesses below. */
typedef struct Unk1D1A30Entry {
    float value[4];
    char pad[0x80];
} Unk1D1A30Entry;
typedef struct Unk1D1A30Row {
    Unk1D1A30Entry *entries;
    int count;
    int field8;
    int fieldc;
    float field10;
} Unk1D1A30Row;
typedef struct Unk1D1A30Work {
    char pad[0xC];
    Unk1D1A30Row rows[4];
    int field5c;
    int field60;
    float field64;
} Unk1D1A30Work;

int func_001D1A30(Unk1D1A30Work *self) {
    int i, j;
    for (i = 0; i < 4; i++) {
        Unk1D1A30Entry *entry = self->rows[i].entries;
        for (j = 0; j < self->rows[i].count / 4; j++) {
            entry->value[0] = -9999.0f;
            entry->value[1] = -9999.0f;
            entry->value[2] = -9999.0f;
            entry->value[3] = -9999.0f;
            entry++;
        }
        self->rows[i].field8 = 0;
        self->rows[i].field10 = -9999.0f;
    }
    self->field5c = 0;
    self->field64 = -9999.0f;
    return 1;
}

s32 func_001D1B28(void) {
    return 1;
}

void func_001D1B30(void) {

}

void func_001D1B38(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D1B40);

void func_001D1D18(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D1D20);

#include "ps2/recovered_types.h"
extern s32 D_0042A1E0;
extern M2C_UNK D_004199E0;

s32 * func_001D1DC8(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7) {
    s32 *temp_2;
    void *temp_3;

    temp_3 = arg0 + 0xF;
    temp_2 = D_0042A1E0 + ((s32) &D_004199E0);
    D_0042A1E0 += ((s32) (((s32) temp_3 > -1) ? temp_3 : (arg0 + 0x1E)) >> 4) * 0x10;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D1E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D21F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D22C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D2438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D24F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D28D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D2CC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D2E30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cff78", func_001D2F18);

s32 func_001D3040(void) {
    D_0040EB18 = func_00108328(D_0040F4C4, "bulletholes");
    return 1;
}
