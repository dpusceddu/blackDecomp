#include "include_asm.h"
#include "ps2/prelude.h"
typedef struct Recovered_LookupEntry {
    u8 unk_0[4];
    s16 unk_4;
    s16 unk_6;
    s16 unk_8, unk_A, unk_C, unk_E, unk_10;
    u8 unk_12[2];
} Recovered_LookupEntry;
extern Recovered_LookupEntry D_003BCB28[][4];
extern s32 func_0012F8C0(void*, s32, s16, s32*);
typedef char LookupEntrySize[sizeof(Recovered_LookupEntry) == 0x14 ? 1 : -1];
typedef char LookupRowSize[sizeof(D_003BCB28[0]) == 0x50 ? 1 : -1];
typedef char LookupPointerWidth[sizeof(void*) == 4 ? 1 : -1];

s32 func_0012F740(void* self, s32 group, s32 entry, s32* result) {
    entry *= sizeof(Recovered_LookupEntry);
    entry += group * sizeof(D_003BCB28[0]);
    entry += (u32)D_003BCB28;
    return func_0012F8C0(self, group, ((Recovered_LookupEntry*)entry)->unk_8, result);
}

s32 func_0012F780(void* self, s32 group, s32 entry, s32* result) {
    entry *= sizeof(Recovered_LookupEntry);
    entry += group * sizeof(D_003BCB28[0]);
    entry += (u32)D_003BCB28;
    return func_0012F8C0(self, group, ((Recovered_LookupEntry*)entry)->unk_A, result);
}

s32 func_0012F7C0(void* self, s32 group, s32 entry, s32* result) {
    entry *= sizeof(Recovered_LookupEntry);
    entry += group * sizeof(D_003BCB28[0]);
    entry += (u32)D_003BCB28;
    return func_0012F8C0(self, group, ((Recovered_LookupEntry*)entry)->unk_E, result);
}

s32 func_0012F800(void* self, s32 group, s32 entry, s32* result) {
    entry *= sizeof(Recovered_LookupEntry);
    entry += group * sizeof(D_003BCB28[0]);
    entry += (u32)D_003BCB28;
    return func_0012F8C0(self, group, ((Recovered_LookupEntry*)entry)->unk_C, result);
}

s32 func_0012F840(void* self, s32 group, s32 entry, s32* result) {
    entry *= sizeof(Recovered_LookupEntry);
    entry += group * sizeof(D_003BCB28[0]);
    entry += (u32)D_003BCB28;
    return func_0012F8C0(self, group, ((Recovered_LookupEntry*)entry)->unk_10, result);
}

s32 func_0012F880(void* self, s32 group, s32 entry, s32* result) {
    entry *= sizeof(Recovered_LookupEntry);
    entry += group * sizeof(D_003BCB28[0]);
    entry += (u32)D_003BCB28;
    return func_0012F8C0(self, group, ((Recovered_LookupEntry*)entry)->unk_4, result);
}

s32 func_0012F8C0(void* self, s32 group, s16 value, s32* result) {
    if ((u32)group > 8) {
        *result = 0;
        return 1;
    }
    if (value == 0) {
        *result = 0;
        return 1;
    }
    if (value == -1) {
        *result = 0;
        return 0;
    }
    *result = value;
    return 2;
}

#ifdef NON_MATCHING
typedef struct Recovered_ObjectiveCounts {
    u8 unk_0[8];
    s16 unk_8;
    u8 unk_A[2];
    s16 unk_C;
    u8 unk_E[2];
    s16 unk_10;
    u8 unk_12[2];
    s16 unk_14;
    u8 unk_16[2];
    s16 unk_18;
} Recovered_ObjectiveCounts;
extern u8* D_0040F4D0;
extern void* D_0040F4E8;
extern s32 func_00122A00(void*, s8);
extern s32 func_00160AA8(Recovered_ObjectiveCounts*, s8);
extern void func_0012FC10(void*, const char*, s16*, s16, s32);
static inline s16* TableColumn(s32 offset) { return (s16*)(offset + (u32)D_003BCB28); }
// Unmatched: column-address lifetimes, saved-register allocation and warning-call scheduling differ.
void func_0012F908(void* self, s32 group) {
    if ((u32)group < 9) {
        s32 difficulty;
        s32 offset = group * 0x50;
        s16* secondaryTarget = TableColumn(offset + 4);
        s16* bodycountTarget = TableColumn(offset + 6);
        s16* armamentTarget = TableColumn(offset + 0xE);
        s16* reconTarget = TableColumn(offset + 0x10);
        s16* intelTarget = TableColumn(offset + 0xC);
        s16* blackmailTarget = TableColumn(offset + 0xA);
        s16* destructionTarget = TableColumn(offset + 8);
        for (difficulty = 0; difficulty < 4; difficulty++) {
            Recovered_ObjectiveCounts* counts = (Recovered_ObjectiveCounts*)(D_0040F4D0 + 0x8F0);
            s16 armament = counts->unk_18;
            s16 destruction = counts->unk_8;
            s16 blackmail = counts->unk_C;
            s16 intel = counts->unk_10;
            s16 recon = counts->unk_14;
            s16 bodycount = func_00122A00(D_0040F4E8, (s8)group);
            func_0012FC10(self, "Secondary", secondaryTarget,
                          func_00160AA8((Recovered_ObjectiveCounts*)(D_0040F4D0 + 0x8F0), difficulty), difficulty);
            secondaryTarget += 10;
            func_0012FC10(self, "Destruction", destructionTarget, destruction, difficulty);
            destructionTarget += 10;
            func_0012FC10(self, "Blackmail", blackmailTarget, blackmail, difficulty);
            blackmailTarget += 10;
            func_0012FC10(self, "Intel", intelTarget, intel, difficulty);
            intelTarget += 10;
            func_0012FC10(self, "Recon", reconTarget, recon, difficulty);
            reconTarget += 10;
            func_0012FC10(self, "Armament", armamentTarget, armament, difficulty);
            armamentTarget += 10;
            func_0012FC10(self, "Bodycount", bodycountTarget, bodycount, difficulty);
            bodycountTarget += 10;
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/table_queries", func_0012F908);
#endif

s32 func_0012FB48(void* self, s32 group, s32 mode) {
    if ((u32)group >= 9) return 0;
    switch (mode) {
        case 0: return 0;
        case 1:
        case 2: {
            Recovered_LookupEntry* row = (Recovered_LookupEntry*)(group * (s32)sizeof(D_003BCB28[0]) + (u32)D_003BCB28);
            return row[3].unk_6 + row[3].unk_A + row[3].unk_C + row[3].unk_10 + row[3].unk_E;
        }
        case 3: {
            Recovered_LookupEntry* row = (Recovered_LookupEntry*)(group * (s32)sizeof(D_003BCB28[0]) + (u32)D_003BCB28);
            return row[3].unk_6 + row[3].unk_A + row[3].unk_C + row[3].unk_10 + row[3].unk_E + row[3].unk_8;
        }
        default: return 0;
    }
}

extern const char* D_003BCB18[];
extern void func_0016D798(const char*, const char*, s32, s32, const char*, const char*);
void func_0012FC10(void* self, const char* name, s16* target, s16 available, s32 difficulty) {
    if (available < *target) {
        func_0016D798("Message to level designer: \n%s objective target is unreachable.\nTarget is %d but there are "
                      "only %d \n%s objectives at difficulty level %s",
                      name, *target, available, name, D_003BCB18[difficulty]);
        *target = available;
    }
}
