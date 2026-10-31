#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 D_0040EAF8;
extern M2C_UNK D_0048F6D0;

s32 func_00158A98(void *arg0) {
    s32 *temp_3;
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_5 == 0) {
        return 1;
    }
    if (D_0040EAF8 < 8) {
        temp_3 = (D_0040EAF8 * 4) + ((s32) &D_0048F6D0);
        D_0040EAF8 += 1;
        *temp_3 = temp_5;
    }
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: the catalog search count and index use different registers.
#include "game/audio/resource_owner.h"
#include "game/weapons/catalog.h"

extern void func_00135ED0(void*, f32, f32);
extern s32 func_00158668(void*, s32);
extern s32 func_001551A8(void*);
extern s32 func_001580F0(void*);
extern void func_001D73D8(Recovered_PlaybackSlots*);
extern void* D_0040F510;
extern s32 func_001583D8(void*);
extern void** D_0040F4E0;
extern void* D_0040F4D0;
extern void func_00136848(s32*, u64);
extern s32 func_00156450(void*);
extern s32 func_00156278(void*, s32, s8, u8*);
extern void func_00156F18(void*, s32);
extern s32 func_001B5578(void*, void*, void*, s32);
extern void* D_0040F4D8;
extern s32 func_0015A8D0(void*);
extern void func_00156D60(void*);

static inline s8 FindWeaponEventRow(void* manager, u64 key) {
    BkWeaponCatalogPS2* catalog = ((BkWeaponCatalogOwnerPS2*)manager)->catalog;
    s8 index = 0;
    u8 count = catalog->count;
    if (count) {
        BkWeaponCatalogRowPS2* row = catalog->rows;
        do {
            if (row->identity == key) return index;
            row++;
            index++;
        } while (index < count);
    }
    return -1;
}

void func_00158AE0(u64 key, void** argument) {
    void* actor = *argument;
    void* component = (u8*)actor + 0x280;
    void* weapon;
    void* payload;
    u64 selectedKey;
    s8 selected;
    switch (key) {
        case 0x73063D2F95228000UL:
            func_001551A8(component);
            if (M2C_FIELD(*argument, s32*, 0xC4) == 2) {
                func_001580F0(M2C_FIELD(component, void**, 0x24));
                func_001D73D8(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), Recovered_PlaybackSlots**, 0xC));
            } else {
                func_001583D8(M2C_FIELD(component, void**, 0x24));
            }
            M2C_FIELD(M2C_FIELD(component, void**, 0x24), s32*, 0xD8) = 14;
            break;
        case 0x9414F5B470A00000UL:
            func_00158668(M2C_FIELD(component, void**, 0x24), (s32)actor);
            M2C_FIELD(M2C_FIELD(component, void**, 0x24), s32*, 0xD8) = 29;
            break;
        case 0xB76B1021B22EDCC0UL:
            payload = M2C_FIELD(M2C_FIELD(M2C_FIELD(component, void**, 0x24), void**, 0xE8), void**, 0x10);
            if (M2C_FIELD(payload, u8*, 0x6C)) func_001B5578((u8*)D_0040F4D8 + 0x512E0, actor, payload, 0);
            break;
        case 0xB76B1021A5ABBB58UL:
            payload = M2C_FIELD(M2C_FIELD(M2C_FIELD(component, void**, 0x24), void**, 0xE8), void**, 0x10);
            if (M2C_FIELD(payload, u8*, 0x6C)) func_001B5578((u8*)D_0040F4D8 + 0x512E0, actor, payload, 1);
            break;
        case 0x61993E3F1EC654D0UL: func_00135ED0(actor, 0.0f, 4.0f); break;
        case 0x712F541CEEFD4080UL:
            selectedKey = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), u64*, 0x2E8);
            selected = FindWeaponEventRow(D_0040F4E0, selectedKey);
            func_00136848(*argument, selectedKey);
            func_00156450(M2C_FIELD(*argument, void**, 0x2A4));
            actor = *argument;
            func_00156278(M2C_FIELD(actor, void**, 0x2A4), (s32)actor, (s8)selected, 0);
            break;
        case 0xB12FC567E6600000UL:
            weapon = M2C_FIELD(component, void**, 0x24);
            if (!M2C_FIELD(M2C_FIELD(weapon, void**, 0xEC), u8*, 0xC7)) {
                M2C_FIELD(weapon, s32*, 0xD8) = 8;
                func_00156D60(weapon);
            } else {
                M2C_FIELD(weapon, u8*, 0x101)--;
                func_0015A8D0(M2C_FIELD(weapon, void**, 0xF4));
            }
            break;
        case 0xB796AC6F7DB30CD0UL:
            func_00156F18(M2C_FIELD(component, void**, 0x24), 1);
            M2C_FIELD(M2C_FIELD(component, void**, 0x24), u8*, 0x108) = 1;
            break;
        case 0xB796AC6F7DB30BA2UL:
            func_00156F18(M2C_FIELD(component, void**, 0x24), 0);
            M2C_FIELD(M2C_FIELD(component, void**, 0x24), u8*, 0x108) = 0;
            break;
    }
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_158a98", func_00158AE0);
#endif
