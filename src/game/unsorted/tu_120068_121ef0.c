#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00107D20(M2C_UNK);
extern s32 * D_0040F4DC;
const u32 rodata_003F4228[14] __asm__("D_003F4228") __attribute__((aligned(8))) = { 0x00000032, 0x00000078, 0x0000008C, 0x00000082, 0x0000007D, 0x0000006E, 0x00000064, 0x00000096, 0x3F800000, 0x3E99999A, 0x3F800000, 0x3F19999A, 0x3F800000, 0x00000000 };
extern volatile char D_003F4228;
extern s32 * D_0040F53C;
extern void func_00122DF0(M2C_UNK *);
extern M2C_UNK D_0048EFA8;
extern s32 func_00122E38(M2C_UNK *, s32);
extern s32 func_00123020(M2C_UNK *, s32);
extern s32 func_00123248(M2C_UNK *);
extern void func_00123960(M2C_UNK *);
extern s32 func_00123980(M2C_UNK *, M2C_UNK, s32, s32);
extern s32 func_001229F8();
extern s8 func_001228E0(s32, s8);
/* Partial keyed catalog and discovery counters; names and unused fields are UNVERIFIED. */
typedef struct Recovered_CatalogEntry {
    u64 key;
    u8 unk_08[0x18];
} Recovered_CatalogEntry;
typedef char RecoveredCatalogEntrySize[(sizeof(Recovered_CatalogEntry) == 0x20) ? 1 : -1];
typedef struct Recovered_Catalog {
    u8 unk_00;
    u8 count;
    u8 unk_02[2];
    Recovered_CatalogEntry* entries;
} Recovered_Catalog;
typedef struct Recovered_DiscoveryData {
    u8 unk_00[0x3A];
    u16 count;
    u8* flags;
} Recovered_DiscoveryData;
typedef struct Recovered_DiscoveryOwner {
    Recovered_DiscoveryData* data;
} Recovered_DiscoveryOwner;
extern Recovered_Catalog** D_0040F4E0;
typedef struct Recovered_DiscoverySlot {
    s8 catalogIndex;
} Recovered_DiscoverySlot;
typedef struct Recovered_DiscoveryState {
    u8 unk_00[0x2D0];
    Recovered_DiscoverySlot** slots;
    u8 unk_2D4[0x1E];
    s8 count;
} Recovered_DiscoveryState;
extern Recovered_DiscoveryState* D_0040F4D0;
extern s32 func_00122520(Recovered_DiscoveryOwner*, u64);
/* The counters' meanings are UNVERIFIED. */
typedef struct Recovered_Counters {
    u8 unk_00[0x16];
    s8 unk_16;
    s8 unk_17;
    s8 unk_18;
    s8 unk_19;
    s8 unk_1A;
} Recovered_Counters;
extern void* D_0040F0E0;
extern void func_00106698(void*);
extern f32 func_0013C980(void*);
extern s32 func_00122120(void*);
extern void func_001F2918(s32, s8, s32);
extern s32 D_0040F51C;

void func_00121EF0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) | arg1);
}

void func_00121F00(void* state) {
    f32 adjusted;
    f32 current;
    s32 enabled;
    s32 count;
    u8 level;
    void* stats;
    void* active;
    void* counters;
    void* player;

    active = M2C_FIELD(D_0040F0E0, void**, 0x21070);
    if (active == ((void*)(((s8*)D_0040F0E0) + 0x20FA0))) { func_00106698(active); }
    M2C_FIELD(state, s8*, 0xC) = 1;
    count = M2C_FIELD(state, u16*, 0xE) + 1;
    M2C_FIELD(state, u16*, 0xE) = count;
    if ((s16)count >= 4) {
        func_00121EF0(state, 0x1000);
        counters = M2C_FIELD(state, void**, 0);
        if (M2C_FIELD(counters, s16*, 0x12) < (s16)M2C_FIELD(state, u16*, 0xE)) {
            M2C_FIELD(counters, s16*, 0x12) = (s16)M2C_FIELD(state, u16*, 0xE);
        }
    } else if ((s16)count == 3) {
        func_00121EF0(state, 0x800);
    } else if ((s16)count == 2) {
        func_00121EF0(state, 0x400);
    }
    if (func_0013C980((void*)(((s8*)D_0040F4D0) + 0x30)) > 1.6f) { func_00121EF0(state, 0x100); }
    if (M2C_FIELD(state, s32*, 4) == 0) {
        stats = M2C_FIELD(state, void**, 0);
        M2C_FIELD(stats, u16*, 0x1C) = (u16)(M2C_FIELD(stats, u16*, 0x1C) + 1);
        player = (void*)(((s8*)D_0040F4D0) + 0x30);
        current = M2C_FIELD(player, f32*, 0x4E4);
        enabled = 1;
        if (!(current >= 1.0f)) { enabled = 0; }
        if (enabled & 0xFF) {
            /* Native inlined update: the delta is zero and both lower thresholds are 1.0f. */
            adjusted = current + 0.0f;
            M2C_FIELD(player, f32*, 0x4E4) = adjusted;
            if ((adjusted >= 1.0f) && (adjusted < 1.0f)) {
                M2C_FIELD(player, f32*, 0x4E4) = 1.3f;
            } else if (M2C_FIELD(player, f32*, 0x4E4) >= 2.0f) {
                M2C_FIELD(player, f32*, 0x4E4) = 2.0f;
                if (M2C_FIELD(player, u8*, 0x8B1) == 0) {
                    level = M2C_FIELD(player, u8*, 0x8A0);
                    if (level < 3U) {
                        M2C_FIELD(player, u8*, 0x8A0) = (u8)(level + 1);
                        M2C_FIELD(player, u8*, 0x8B1) = 1U;
                        M2C_FIELD(player, f32*, 0x4E4) = 1.3f;
                    }
                }
            }
        }
    } else {
        func_00122120(state);
    }
    func_001F2918(D_0040F51C, 0, M2C_FIELD(state, s32*, 4));
    M2C_FIELD(state, s32*, 4) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122120);

s16 func_00122368(void **arg0, s32 arg1) {
    if (arg1 & 1) {
        return M2C_FIELD(*arg0, s16 *, 0x1C);
    }
    if (arg1 & 2) {
        return M2C_FIELD(*arg0, s16 *, 0x22);
    }
    if (arg1 & 4) {
        return M2C_FIELD(*arg0, s16 *, 0x24);
    }
    if (arg1 & 8) {
        return M2C_FIELD(*arg0, s16 *, 0x26);
    }
    if (arg1 & 0x10) {
        return M2C_FIELD(*arg0, s16 *, 0x28);
    }
    if (arg1 & 0x20) {
        return M2C_FIELD(*arg0, s16 *, 0x2A);
    }
    if (arg1 & 0x40) {
        return M2C_FIELD(*arg0, s16 *, 0x2C);
    }
    if (arg1 & 0x80) {
        return M2C_FIELD(*arg0, s16 *, 0x2E);
    }
    if (arg1 & 0x100) {
        return M2C_FIELD(*arg0, s16 *, 0x30);
    }
    if (arg1 & 0x200) {
        return M2C_FIELD(*arg0, s16 *, 0x32);
    }
    if (arg1 & 0x400) {
        return M2C_FIELD(*arg0, s16 *, 0x34);
    }
    if (arg1 & 0x800) {
        return M2C_FIELD(*arg0, s16 *, 0x36);
    }
    if (arg1 & 0x1000) {
        return M2C_FIELD(*arg0, s16 *, 0x38);
    }
    return 0;
}

void func_00122478(Recovered_DiscoveryOwner* owner) {
    s32 index = 0;
    s8 count = D_0040F4D0->count;
    if (count > 0) {
        do {
            Recovered_DiscoverySlot* slot = D_0040F4D0->slots[index];
            if (slot != 0) { func_00122520(owner, (*D_0040F4E0)->entries[slot->catalogIndex].key); }
            index++;
        } while (index < count);
    }
}
#ifdef NON_MATCHING
// Unmatched: catalog-search register allocation and loop scheduling differ.
s32 func_00122520(Recovered_DiscoveryOwner* owner, u64 key) {
    Recovered_Catalog* catalog = *D_0040F4E0;
    u8 count = catalog->count;
    s32 index = 0;
    s32 selected;
    if (count != 0) {
        Recovered_CatalogEntry* entry = catalog->entries;
        do {
            if (entry->key == key) {
                selected = index;
                goto found;
            }
            entry++;
            index = (s8)(index + 1);
        } while (index < count);
    }
    selected = -1;
found:
    {
        /* A missing key selects index -1 in the native code. */
        u8* flag = owner->data->flags + (s8)selected;
        s32 result = 1;
        if (*flag == 0) {
            *flag = 1;
            result = owner->data->count + 1;
            owner->data->count = result;
        }
        return result;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122520);
#endif

void func_001225B8(void **arg0, s32 arg1) {
    void *temp_3;
    void *temp_3_2;
    void *temp_3_3;
    void *temp_3_4;
    void *temp_3_5;

    if (arg1 & 4) {
        temp_3 = *arg0;
        M2C_FIELD(temp_3, u8 *, 0x17) = (u8) (M2C_FIELD(temp_3, u8 *, 0x17) + 1);
        return;
    }
    if (arg1 & 8) {
        temp_3_2 = *arg0;
        M2C_FIELD(temp_3_2, u8 *, 0x18) = (u8) (M2C_FIELD(temp_3_2, u8 *, 0x18) + 1);
        return;
    }
    if (arg1 & 0x10) {
        temp_3_3 = *arg0;
        M2C_FIELD(temp_3_3, u8 *, 0x19) = (u8) (M2C_FIELD(temp_3_3, u8 *, 0x19) + 1);
        return;
    }
    if (arg1 & 2) {
        temp_3_4 = *arg0;
        M2C_FIELD(temp_3_4, u8 *, 0x16) = (u8) (M2C_FIELD(temp_3_4, u8 *, 0x16) + 1);
        return;
    }
    temp_3_5 = *arg0;
    if (arg1 & 0x20) {
        M2C_FIELD(temp_3_5, u8 *, 0x1A) = (u8) (M2C_FIELD(temp_3_5, u8 *, 0x1A) + 1);
        return;
    }
    M2C_FIELD(temp_3_5, u8 *, 0x15) = (u8) (M2C_FIELD(temp_3_5, u8 *, 0x15) + 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122658);
#ifdef NON_MATCHING
// Unmatched: mode branches and counter-load scheduling differ.
s32 func_00122660(s32 owner) {
    s32 mode = M2C_FIELD(D_0040F0E0, s32*, 0x2014C);
    Recovered_Counters* counters;
    switch (mode) {
        case 3:
            counters = (Recovered_Counters*)*D_0040F4DC;
            return counters->unk_17 + counters->unk_18 + counters->unk_19 + counters->unk_1A + counters->unk_16;
        case 1:
        case 2:
            counters = (Recovered_Counters*)*D_0040F4DC;
            return counters->unk_17 + counters->unk_18 + counters->unk_19 + counters->unk_1A;
        default: return 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122660);
#endif

void func_00122708(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = func_00107D20(0x280);
}

s32 func_00122738(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s8 *, 0x15) = 1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), f32 *, 4) = 300.0f;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0x1C) = 0x1E;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0x1E) = 0x1E;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), f32 *, 0xC) = 20.0f;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122780);

void func_001227A8(s32 *arg0) {
    *arg0 = *D_0040F4DC;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_001227C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_001228E0);
s32 func_00122900(s32 owner, s32 value) {
    s32 index = 0;
    while (index < func_001229F8(owner)) {
        s8 current = index;
        if (func_001228E0(owner, current) == value) { return current; }
        index++;
    }
    return -1;
}
s32 func_00122980(s32 owner, s32 value) {
    s32 index = 0;
    while (index < func_001229F8(owner)) {
        if (func_001228E0(owner, (s8)index) == value) { return 1; }
        index++;
    }
    return 0;
}

s32 func_001229F8(void) {
    return 8;
}

s32 func_00122A00(s32 arg0, s32 arg1)
{
  M2C_UNK *new_var;
  new_var = &(*((((s32) (arg1 << 0x18)) >> 0x16) + (&D_003F4228)));
  return *new_var;
}

void func_00122A20(void) {
    func_00122BB0(*D_0040F53C);
}

void func_00122A48(void) {
    func_00122BD0(*D_0040F53C);
}

void func_00122A70(void) {
    func_00122BF0(*D_0040F53C);
}

void func_00122A98(void) {
    func_00122C20(*D_0040F53C);
}

void func_00122AC0(void) {
    func_00122C50(*D_0040F53C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121ef0", func_00122AE8);

void func_00122AF0(void) {
    func_00122DF0(&D_0048EFA8);
}


void func_00122B60(s32 arg0) {
    func_00122E38(&D_0048EFA8, arg0);
}

void func_00122B88(s32 arg0) {
    func_00123020(&D_0048EFA8, arg0);
}

void func_00122BB0(void) {
    func_00123248(&D_0048EFA8);
}

void func_00122BD0(void) {
    func_00123960(&D_0048EFA8);
}

void func_00122BF0(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 1, arg1, arg2);
}

void func_00122C20(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 0, arg1, arg2);
}

void func_00122C50(s32 arg0, s32 arg1, s32 arg2) {
    func_00123980(&D_0048EFA8, 2, arg1, arg2);
}
