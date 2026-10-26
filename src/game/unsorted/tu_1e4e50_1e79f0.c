#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00280100(void *, s32);
extern void * D_0040F510;
extern void * D_0040F50C;
extern s32 func_001D7BB8();
extern void * func_0015BF38(s32);
extern s32 func_001D63A8(s32, s32, void *);
extern s32 func_001EFD30();
extern s32 func_00284298(void*);

/* Partial resource list and configuration; unaccessed fields are UNVERIFIED. */
typedef struct Recovered_ResourceList {
    u8 unk_00[0x80];
    void* unk_80[48];
    u8 unk_140[0x30];
    u32 unk_170[15];
    s32 unk_1AC;
} Recovered_ResourceList;
typedef char RecoveredResourcePointerIs32[(sizeof(void*) == 4) ? 1 : -1];

/* Partial keyed resources; original object and field meanings are UNVERIFIED. */
typedef struct Recovered_KeyResource {
    u64 unk_00;
    s32 unk_08;
    s32 unk_0C;
} Recovered_KeyResource;
typedef struct Recovered_KeyResourceOwner {
    s32 unk_00;
    u8 unk_04[0x30];
    void* unk_34;
    u8 unk_38[8];
    void* unk_40;
    void* unk_44;
    u8 unk_48[8];
    Recovered_KeyResource* unk_50;
    s32 unk_54;
    Recovered_KeyResource* unk_58;
    s32 unk_5C;
} Recovered_KeyResourceOwner;
typedef char RecoveredKeyResourceSize[(sizeof(Recovered_KeyResource) == 0x10) ? 1 : -1];
extern void func_00282100(void*);
extern s32 func_002821A8(void*, s32, s32);
extern void func_00282170(void*);

s32 func_001E79F0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 8) != 3) {
        func_00280100(D_0040F510, M2C_FIELD(arg0, s32 *, 4));
        M2C_FIELD(arg0, s32 *, 4) = 0;
        M2C_FIELD(D_0040F50C, s32 *, 0x948) = 0;
        M2C_FIELD(arg0, s32 *, 8) = 3;
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E7A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E7A58);
/* The meanings of the two 64-bit keys are UNVERIFIED. */
s32 func_001E7E08(u64 key) { return key == 0x6D936D37E6000000UL || key == 0x6D936E1CC7C00000UL; }
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E7E58);

void func_001E80C0(s64 arg0, s32 *arg1) {
    s32 temp_2;
    void *temp_6;

    temp_2 = func_001D7BB8(func_0015BF38(*arg1 + 0x280), arg0);
    if (temp_2 != 0) {
        temp_6 = M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), void **, 0xC);
        func_001D63A8(M2C_FIELD(temp_6, s32 *, 0x1BE0), temp_2, temp_6);
    }
}

void func_001E8120(Recovered_ResourceList* owner, const u32* values) {
    s32 remaining = 47;
    void** slot = &owner->unk_80[47];
    owner->unk_170[4] = values[4];
    owner->unk_170[5] = values[5];
    owner->unk_170[6] = values[6];
    owner->unk_170[0] = values[0];
    owner->unk_170[3] = values[3];
    owner->unk_170[9] = values[9];
    owner->unk_170[8] = values[8];
    owner->unk_170[1] = values[1];
    owner->unk_170[2] = values[2];
    owner->unk_170[7] = values[7];
    owner->unk_170[10] = values[10];
    owner->unk_170[11] = values[11];
    owner->unk_170[12] = values[12];
    owner->unk_170[13] = values[13];
    owner->unk_170[14] = values[14];
    do {
        *slot = 0;
        remaining--;
        slot = (void**)((u32)slot - 4U);
    } while (remaining >= 0);
    owner->unk_1AC = 0;
}

s32 func_001E81C0(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x1AC);
    if (temp_3 != 1) {
        if (temp_3 < 2) {
            if (temp_3 != 0) {
                return 0;
            }
            goto block_6;
        }
        if (temp_3 != 2) {
            if (temp_3 == 3) {
block_6:
                M2C_FIELD(arg0, s32 *, 0x1AC) = 1;
                goto block_7;
            }
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return 0;
        }
        goto block_9;
    }
block_7:
    if (func_001EFD30(D_0040F510) != 0) {
        M2C_FIELD(arg0, s32 *, 0x1AC) = 2;
block_9:
        return 1;
    }
    return 0;
}

s32 func_001E8248(void) {
    return 1;
}

void func_001E8250(Recovered_ResourceList* owner) {
    void** slot = owner->unk_80;
    s32 remaining = 47;
    do {
        void* resource = *slot;
        remaining--;
        slot++;
        if (resource != 0) { func_00284298(resource); }
    } while (remaining >= 0);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E82A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E8710);

void func_001E8798(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E87A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E8900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E8980);
Recovered_KeyResource* func_001E89B0(Recovered_KeyResourceOwner* owner, u64 key) {
    s32 index;
    if (owner->unk_50 != 0) {
        for (index = 0; index < owner->unk_54; index++) {
            if (owner->unk_50[index].unk_00 == key) { return &owner->unk_50[index]; }
        }
    }
    if (owner->unk_58 != 0) {
        for (index = 0; index < owner->unk_5C; index++) {
            if (owner->unk_58[index].unk_00 == key) { return &owner->unk_58[index]; }
        }
    }
    return 0;
}
#ifdef NON_MATCHING
// Unmatched: the kind comparison uses a different temporary register.
s32 func_001E8A30(Recovered_KeyResourceOwner* owner, Recovered_KeyResource* resources, s32 count, s32 kind) {
    Recovered_KeyResource* entry;
    func_00282100(M2C_FIELD(D_0040F510, void**, 0xCBF4));
    if (kind == 1) {
        owner->unk_58 = resources;
        owner->unk_5C = count;
    } else {
        owner->unk_50 = resources;
        owner->unk_54 = count;
    }
    entry = resources;
    if (count > 0) {
        do {
            if (entry->unk_0C != 0) {
                entry->unk_08 = func_002821A8(M2C_FIELD(D_0040F510, void**, 0xCBF4), entry->unk_0C, kind);
            }
            count--;
            entry++;
        } while (count != 0);
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e79f0", func_001E8A30);
#endif
s32 func_001E8AF0(Recovered_KeyResourceOwner* owner) {
    func_00282170(M2C_FIELD(D_0040F510, void**, 0xCBF4));
    owner->unk_58 = 0;
    owner->unk_5C = 0;
    return 1;
}
