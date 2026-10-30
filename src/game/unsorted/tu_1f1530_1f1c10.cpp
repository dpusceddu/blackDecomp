#include "include_asm.h"
#include "ps2/prelude.h"

extern "C" u8* D_0040F518;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F7C48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F8138);

// Partial overlay view; the original class and field meanings are UNVERIFIED.
struct OverlayModeView {
    char unknown00[0x78];
    float field78, field7c, field80, field84;
    char unknown88[0x98];
    int field120, field124, field128, field12c;
    char unknown130[0x10c];
    signed char mode;
};

extern "C" void func_001F2790(OverlayModeView* self, signed char mode) {
    self->mode = mode;
    if (mode != 2) {
        self->field78 = 30.0f;
        self->field7c = 22.0f;
        self->field80 = 610.0f;
        self->field84 = 458.0f;
        self->field120 = 0;
        self->field124 = 0;
        self->field128 = 0;
        self->field12c = 0;
    }
}
#ifdef NON_MATCHING
// Unmatched: indexed lookup register allocation differs.
// Partial target, vtable and clock views; field meanings are UNVERIFIED.
struct OverlayTargetDraft;
struct OverlaySlotDraft {
    char unknown00[0x3c];
    OverlayTargetDraft* target;
    char unknown40[0x68];
};
struct OverlayCallbackDraft {
    short adjustment, unknown02;
    void (*callback)(void*, float);
};
struct OverlayVtableDraft {
    char unknown00[0x10];
    OverlayCallbackDraft entry;
};
struct OverlayTargetDraft {
    char unknown00[0x14];
    OverlayVtableDraft* table;
    char unknown18[0x140];
    int previous;
    char unknown15c[4];
    int current;
};
struct OverlayClockDraft {
    char unknown00[0x1c];
    float time;
};
extern "C" OverlayClockDraft* D_0040F4D0;

extern "C" void func_001F2D08(void* self, signed char index, int value) {
    OverlayTargetDraft* target = ((OverlaySlotDraft*)D_0040F518)[(int)index].target;
    if (target->current != value) {
        target->current = value;
        target->previous = 0;
        target->table->entry.callback((char*)target + target->table->entry.adjustment, D_0040F4D0->time);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F2D08);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F2DF8);
// Partial native command views; original class identities and unused fields are UNVERIFIED.
extern "C" s32 func_001F1C10(void*, s32, s32, s32, s32, s32, s32);
struct OverlayLayerRecord {
    s32 flags;
    u8 opaque[12];
};
struct OverlayCommandList {
    u8 unknown00[0x2C];
    OverlayLayerRecord* layers;
    void SetFlags(s32 index, s32 flags) { layers[index].flags = flags; }
};
static inline OverlayCommandList* OverlayCommands(s8 index) {
    u32 address = index * 0xA8 + (u32)D_0040F518;
    return (OverlayCommandList*)(address + 0x40);
}
extern "C" s32 func_001F3948(void* self, s32 index, s32 a, s32 b) {
    s32 resource = M2C_FIELD(D_0040F518, s32*, 0x234);
    func_001F1C10(self, 2, 40, 0, (s8)index, a, b);
    OverlayCommands(M2C_FIELD(self, s8*, 0x12))->SetFlags(M2C_FIELD(self, s16*, 0x10) + 1, 2);
    s8 i;
    for (i = 0; i < 40; i++) M2C_FIELD(M2C_FIELD(self, u8**, 0x1C) + i * 0x10, s32*, 8) = resource;
    for (i = 0; i < 40; i++) M2C_FIELD(self, u8**, 0x24)[i] = 0;
    for (i = 0; i < 8; i++) {
        M2C_FIELD(self, u8**, 0x28)[i] = 0;
        for (s8 j = 0; j < 10; j++) M2C_FIELD(M2C_FIELD(self, u8**, 0x20) + i * 0x20, s32**, 0)[j] = 0;
    }
    M2C_FIELD(self, s32*, 0x2C) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F3AA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F3EE8);
#ifdef NON_MATCHING
// Unmatched: table and stride register allocation differs.
// Partial grid and slot views; original types and field meanings are UNVERIFIED.
struct OverlayGridListDraft {
    int* items;
    char unknown04[28];
};
struct OverlayGridDraft {
    char unknown00[0x10];
    short value;
    signed char index;
    char unknown13[13];
    OverlayGridListDraft* lists;
};
struct OverlayGridSlotDraft {
    char unknown00[0xa8];
};
extern "C" void func_00278F00(void*, int, int);

extern "C" int func_001F41C0(OverlayGridDraft* self) {
    signed char row, column;
    for (row = 0; row < 8; row++) {
        for (column = 0; column < 10; column++) {
            int item = self->lists[(int)row].items[(int)column];
            if (item)
                func_00278F00((char*)&((OverlayGridSlotDraft*)D_0040F518)[(int)self->index] + 0x40, self->value + 1,
                              item);
        }
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F41C0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F44F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F59E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F5F58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F75E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F76E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f1530_1f1c10", func_001F7A18);
extern "C" const int D_003F9F10[] = {12, 13, 23, 87, 24};

extern "C" int func_001F7B58(void* self, int value) {
    int i;
    for (i = 0; i < 5; i++) {
        if (value == D_003F9F10[i]) return 1;
    }
    return 0;
}
