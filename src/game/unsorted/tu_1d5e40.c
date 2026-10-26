#include "include_asm.h"
#include "ps2/prelude.h"

extern void ResourcePool_Initialize(void*);
extern s32 func_001D6230(void *, M2C_UNK, M2C_UNK);
extern s32 func_001D76E8();
extern s32 func_001D7BB8();
extern s32 func_00281BB8();
extern void ResourcePool_Rebind(void*, void**, s32);
extern s32 func_00280A80();
extern void func_001D7128();
extern s32 func_001F0620();
extern s32 func_001F0770(s32, f32);
extern f32 D_003BD2A8;
extern s32 func_001F0C98();
extern s32 func_001F08E8(s32);
extern s32 func_001F0958(s32);
extern void * func_001092F8();

/* Partial resource owner; object and timestamp meanings are UNVERIFIED. */
typedef struct Recovered_ResourceEntry {
    void* resource;
    u32 unk_04;
    u32 stamp;
} Recovered_ResourceEntry;
typedef struct Recovered_ResourceOwner {
    u8 unk_00[0x5C];
    Recovered_ResourceEntry* entries;
    u32 count;
    u8 unk_64[0x1C];
    u32 stamp;
    u32 state;
    u8 unk_88[0x12C];
    void* playback;
} Recovered_ResourceOwner;
extern void* func_002842E8(void*);
extern void func_00284298(void*);
extern s32 func_001D7A60(void*);
extern void func_00281C98(void*);

s32 func_001D5E40(void) {
    return 0;
}

s32 func_001D5E48(void) {
    return 0;
}

void func_001D5E50(void) {

}

void func_001D5E58(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x1B4) = 0;
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    ResourcePool_Initialize(arg0 + 0x94);
    func_001D6230(arg0, 0, 0);
}

s32 func_001D5EA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x84);
    switch (temp_3) {                               /* irregular */
    case 1:
        M2C_FIELD(arg0, s64 *, 0x1A8) = (s64) arg2;
        M2C_FIELD(arg0, s32 *, 0x1B4) = arg4;
        M2C_FIELD(arg0, s32 *, 0x1B0) = arg3;
        if (func_001D76E8(arg4, arg3, 1, arg2) == 0) {
            return 0;
        }
        M2C_FIELD(arg0, s32 *, 0x78) = func_001D7BB8(M2C_FIELD(arg0, s32 *, 0x1B4), arg1);
        M2C_FIELD(arg0, s32 *, 0x84) = 2;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    case 2:
        func_00281BB8(arg0 + 0x94, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x80) = 0;
        return 1;
    default:
        return 0;
    }
}

#ifdef NON_MATCHING
// Unmatched: the resource loop uses different saved registers.
s32 func_001D5F58(Recovered_ResourceOwner* owner) {
    u32 index;
    switch (owner->state) {
        case 1:
            owner->state = 2;
            /* fallthrough */
        case 2:
        case 3:
        case 4:
            index = 0;
            if (owner->count != 0) {
                u32 offset = 0;
                do {
                    Recovered_ResourceEntry* entry = (Recovered_ResourceEntry*)((u8*)owner->entries + offset);
                    index++;
                    offset += sizeof(Recovered_ResourceEntry);
                    func_00284298(entry->resource);
                } while (index < owner->count);
            }
            if (func_001D7A60(owner->playback) != 0) {
                M2C_FIELD(owner, void**, 0x78) = 0;
                owner->state = 5;
                owner->playback = 0;
                case 5:
                    func_00281C98((u8*)owner + 0x94);
                    owner->entries = 0;
                    owner->state = 7;
                    owner->count = 0;
                case 7: return 1;
            }
        default: return 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D5F58);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D60B8);
#ifdef NON_MATCHING
// Unmatched: the loop index and byte offset use swapped saved registers.
Recovered_ResourceEntry* func_001D6178(Recovered_ResourceOwner* owner) {
    u32 offset;
    u32 index;
    Recovered_ResourceEntry* oldest = owner->entries;
    index = 0;
    if (owner->count != 0) {
        offset = 0;
        do {
            Recovered_ResourceEntry* entry = (Recovered_ResourceEntry*)((u8*)owner->entries + offset);
            if (func_002842E8(entry->resource) == 0) {
                entry->stamp = owner->stamp;
                return entry;
            }
            index++;
            offset += sizeof(Recovered_ResourceEntry);
            oldest = entry->stamp < oldest->stamp ? entry : oldest;
        } while (index < owner->count);
    }
    func_00284298(oldest->resource);
    oldest->stamp = owner->stamp;
    return oldest;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6178);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D62F8);

void func_001D6388(s32 arg0, void** resources, s32 count) {
    ResourcePool_Rebind((void*)(arg0 + 0x94), resources, count);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D63A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D65F8);

void func_001D6C48(void *arg0)
{
  int temp_4;
  M2C_FIELD(arg0, s32 *, 0x1C24) = (s32) (((M2C_FIELD(arg0, s32 *, 0x1C24)) + 1) ^ 0);
  M2C_FIELD(arg0, s32 *, 0x1C40) = (s32) ((M2C_FIELD(arg0, s32 *, 0x1C40)) - 1);
  func_00280A80(arg0 + 0x40);
  if (((!D_003BD2A8) && (!D_003BD2A8)) && (!D_003BD2A8))
  {
    if (arg0)
    {
    }
  }
  func_001D7128(arg0);
  temp_4 = M2C_FIELD(arg0, s32 *, 0x1BE0);
  if (temp_4 != 0)
  {
    func_001F0620(temp_4, M2C_FIELD(arg0, s32 *, 0x1C24));
    func_001F0770(M2C_FIELD(arg0, s32 *, 0x1BE0), D_003BD2A8);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6CB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6E70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6E78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6F90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7020);

void func_001D7100(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_11;

    temp_11 = M2C_FIELD(arg7, s32 *, 0x1BE0);
    if (temp_11 != 0) {
        func_001F0C98(arg0, arg1, arg2, arg3, arg4, arg5, arg6, temp_11 + 0x1D0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7128);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7198);

void func_001D7238(void *arg0) {
    func_001F08E8(M2C_FIELD(arg0, s32 *, 0x1BE0));
}

void func_001D7258(void *arg0) {
    func_001F0958(M2C_FIELD(arg0, s32 *, 0x1BE0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7278);

void func_001D72B8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x90) = 0;
}

void func_001D72C0(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1BEC) = func_001092F8();
}

void func_001D72E8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1C04) = func_001092F8();
}

void func_001D7310(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1BF4) = func_001092F8();
}

void func_001D7338(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1C08) = func_001092F8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D73D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7460);

void func_001D7498(s32 arg0, s32 arg1) {
    s32 var_3;
    void *var_4;

    var_4 = arg0 + 0x2F;
    var_3 = 0;
loop_1:
    var_3 += 1;
    if (M2C_FIELD(var_4, s32 *, -0xF) == arg1) {
        M2C_FIELD(var_4, s8 *, 0) = 0;
        return;
    }
    var_4 += 0x10;
    if (var_3 >= 2) {
        return;
    }
    goto loop_1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D74C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D75E0);
