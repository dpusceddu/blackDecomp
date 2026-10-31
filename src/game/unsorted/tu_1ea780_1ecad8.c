#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001ED4F0(s32);

void func_001ECAD8(s32 arg0) {
    func_001ED4F0(arg0 + 0x7B0);
}

typedef struct Recovered_ModeOwner Recovered_ModeOwner;

extern void func_001EA580(Recovered_ModeOwner*, u64, s32);
extern void* D_0040F510;
extern f32 func_001DD748(void*);
extern s32 func_001EC5C8(void*);
extern f32 D_003BD980;
extern f32 D_003BD984;
extern void* D_0040F4D0;

void func_001ECAF8(void* self) {
    f32 interval;
    s32 category;
    s32 index;
    void* slot;
    void* clock;

    index = 0;
    func_001EA580(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), Recovered_ModeOwner**, 8), 0x684bbb0484a09400UL, 0);
    func_001EA580(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), Recovered_ModeOwner**, 8), 0x5fb8cab604a05e40UL, 0);
    for (; index < M2C_FIELD(self, s32*, 0x1E28); ++index) {
        slot = (u8*)self + index * 0x40;
        if (M2C_FIELD(slot, s32*, 0x28) == 1) {
            interval = func_001DD748(M2C_FIELD(slot, void**, 0x1C));
            category = func_001EC5C8(slot);
            switch (category) {
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                    if (interval < D_003BD980) {
                        func_001EA580(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), Recovered_ModeOwner**, 8),
                                      0x684bbb0484a09400UL, 1);
                    }
                    break;
                case 13:
                    if (interval < D_003BD984) {
                        func_001EA580(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), Recovered_ModeOwner**, 8),
                                      0x5fb8cab604a05e40UL, 1);
                    }
                    break;
                case 1:
                default: break;
            }
        }
    }
    if (M2C_FIELD(self, u8*, 0x1E55) == 1) {
        func_001EA580(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), Recovered_ModeOwner**, 8), 0x684bbb0484a09400UL,
                      1);
        clock = D_0040F4D0;
        if (M2C_FIELD(self, f32*, 0x1E50) < M2C_FIELD(clock, f32*, 0x20)) { M2C_FIELD(self, u8*, 0x1E55) = 0U; }
    }
}
#ifdef NON_MATCHING
// Unmatched: entry-search layout and saved register allocation differ (22 instructions).
extern void* func_001EBEB8(void*, s32);
extern s32 func_001EC600(void*, void*, s128);
extern void func_001EC330(void*, f32);
extern f32 func_001DD748(void*);
static inline u8 PlaybackEntryHasStateFour(void* slot) {
    void* associated = M2C_FIELD(slot, void**, 0x24);
    if (!associated) return 0;
    if (M2C_FIELD(associated, s32*, 0x14) == 4) return 1;
    return 0;
}
void func_001ECD50(void* self) {
    void* entry;
    s32 index;
    if (M2C_FIELD(self, u8*, 0x1E56)) {
        s32 activate;
        if (M2C_FIELD(self, u8*, 0x1E57) != 1 || M2C_FIELD(self, s32*, 0x1DE0) >= M2C_FIELD(self, s32*, 0x1DE4)) {
            s32 more;
            s32 count = M2C_FIELD(self, s32*, 0x1E30);
            index = M2C_FIELD(self, s32*, 0x1E38);
            activate = 1;
            entry = NULL;
            more = index < count;
            while (more) {
                void* candidate = (u8*)self + 0x80 + index * 0x28;
                if (M2C_FIELD(candidate, s32*, 0x14) == 3 &&
                    M2C_FIELD(candidate, s32*, 0x10) == M2C_FIELD(self, s32*, 0x1DE0)) {
                    entry = candidate;
                    break;
                }
                ++index;
                more = index < count;
            }
            if (entry) {
                void* slot = func_001EBEB8(self, M2C_FIELD(self, s32*, 0x1DE0));
                if (slot) {
                    activate = 0;
                    func_001EC600(slot, entry, M2C_FIELD(self, s128*, 0x1DD0));
                }
            } else {
                for (index = 0; index < M2C_FIELD(self, s32*, 0x1E28); ++index) {
                    entry = (u8*)self + index * 0x40;
                    if ((PlaybackEntryHasStateFour(entry) == 1) ||
                        (M2C_FIELD(entry, s32*, 0x28) == 1 && func_001DD748(M2C_FIELD(entry, void**, 0x1C)) <= 0.15f)) {
                        activate = 0;
                    }
                }
            }
        } else {
            activate = 1;
        }
        if (activate) func_001EC330(self, M2C_FIELD(self, f32*, 0x1E4C));
        M2C_FIELD(self, u8*, 0x1E56) = 0;
    }
    M2C_FIELD(self, u8*, 0x1E57) = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ecad8", func_001ECD50);
#endif


s32 func_001ECEF8(void* arg0, s32 arg1, s32 arg2) {
    s32 var_3;

    switch (arg1) {
        case 4:
        case 5: var_3 = 0xB; break;
        case 1:
        case 3: var_3 = (arg2 != 0) ? 4 : 7; break;
        case 2: var_3 = (arg2 != 0) ? 5 : 8; break;
        case 7: var_3 = 0xA; break;
        case 8: var_3 = 0xC; break;
        case 9: var_3 = 6; break;
        case 10: var_3 = 9; break;
        case 11: var_3 = 3; break;
        case 12: var_3 = 2; break;
        case 0:
        case 13:
        default: var_3 = 0xE; break;
    }
    return var_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ecad8", func_001ECF80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ecad8", func_001ED068);
