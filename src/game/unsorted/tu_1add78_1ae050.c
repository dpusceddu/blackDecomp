#include "include_asm.h"
#include "ps2/prelude.h"

/* Accessed slot layout; original field meanings remain UNVERIFIED. */
typedef struct {
    u16 field0, field2, field4, field6;
    void* object;
    u8 fieldC, fieldD, unknownE[2];
} BkEffectSlotPS2;
typedef char EffectSlotSize[(sizeof(BkEffectSlotPS2) == 0x10) ? 1 : -1];
typedef char EffectSlotObjectOffset[((unsigned)&((BkEffectSlotPS2*)0)->object == 8) ? 1 : -1];

extern void func_001B3CD8(BkEffectSlotPS2*);
extern s32 func_001B3D18(BkEffectSlotPS2*);
extern void func_001D3040(void);
extern void func_001D3078(void);
extern void func_001D3090(void*);
extern void func_001D3368(void);
extern void func_001D3408(void*, u16);
extern void func_001D37C8(void*, u16, void*);
extern void* func_00148508(void*, u8);
extern void* D_0040F4C0;
void func_001B2BC0(BkEffectSlotPS2*);
void func_001B2C40(BkEffectSlotPS2*);
void func_001B2CD0(BkEffectSlotPS2*);

extern s32 func_001ADEA8(s32);
extern s32 func_001ADF18();
extern s32 func_001ADF30();

void func_001AE050(void) {

}

void func_001AE058(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
}

void func_001AE068(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) - 1);
}

void func_001AE078(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x24) = arg1;
    M2C_FIELD(arg0, s32 *, 0x28) = arg2;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

void func_001AE088(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
}

void func_001AE090(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001AE098);

void func_001AE0A8(void *arg0) {
    func_001ADEA8(arg0 + 0xC);
}

void func_001AE0C8(s32 arg0) {
    func_001ADF18(arg0 + 0xC);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001AE0E8);

s32 func_001AE0F0(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = arg0 + 0xC;
    func_001ADF18(temp_16, arg1);
    return func_001ADF30(temp_16, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0A20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0D88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0E00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0F70);
void func_001B2A78(BkEffectSlotPS2* slots) {
    u16 i;
    for (i = 0; i < 28; i++) { func_001B3CD8(slots + i); }
}
s32 func_001B2AC8(BkEffectSlotPS2* slots) {
    u16 i;
    s8* objects = (s8*)slots + 8;
    for (i = 0; i < 28; i++) {
        void** objectAddress = (void**)(objects + i * 16);
        void* object = *objectAddress;
        if (object) {
            void* table = M2C_FIELD(object, void**, 0x10);
            BkEffectSlotPS2* slot = slots + i;
            ((void (*)(void*, u8))M2C_FIELD(table, void**, 0x7C))((s8*)object + M2C_FIELD(table, s16*, 0x78),
                                                                  slot->fieldC);
            func_001B3D18(slot);
        }
    }
    func_001D3040();
    return 1;
}
void func_001B2B68(BkEffectSlotPS2* slots) {
    func_001D3090(M2C_FIELD(D_0040F4C0, void**, 0xD540));
    func_001B2BC0(slots);
    func_001B2C40(slots);
    func_001B2CD0(slots);
    func_001D3368();
}
void func_001B2BC0(BkEffectSlotPS2* slots) {
    u16 i;
    for (i = 0; i < 8; i++) {
        BkEffectSlotPS2* slot = slots + i;
        if (slot->fieldD && slot->field0) { func_001D3408((s8*)slots + 0x1C0 + slot->field4 * 32, slot->field0); }
    }
}
void func_001B2C40(BkEffectSlotPS2* slots) {
    u16 i;
    s8* objects = (s8*)slots + 8;
    for (i = 8; i < 20; i++) {
        BkEffectSlotPS2* slot = slots + i;
        if (slot->fieldD && slot->field0) {
            void** objectAddress = (void**)(objects + i * 16);
            func_001D37C8((s8*)slots + 0x1C0 + slot->field4 * 32, slot->field0, (s8*)*objectAddress + 0x70);
        }
    }
}
void func_001B2CD0(BkEffectSlotPS2* slots) {
    u16 i;
    s8* objects = (s8*)slots + 8;
    for (i = 20; i < 28; i++) {
        BkEffectSlotPS2* slot = slots + i;
        if (slot->fieldD && slot->field0) {
            void** objectAddress = (void**)(objects + i * 16);
            void* transform = func_00148508(*objectAddress, slot->fieldC);
            func_001D37C8((s8*)slots + 0x1C0 + slot->field4 * 32, slot->field0, transform);
        }
    }
}
s32 func_001B2D70(BkEffectSlotPS2* slots) {
    u16 i;
    s8* objects = (s8*)slots + 8;
    func_001D3078();
    for (i = 0; i < 28; i++) {
        void** objectAddress = (void**)(objects + i * 16);
        void* object = *objectAddress;
        if (object) {
            void* table = M2C_FIELD(object, void**, 0x10);
            BkEffectSlotPS2* slot = slots + i;
            ((void (*)(void*, u8))M2C_FIELD(table, void**, 0x7C))((s8*)object + M2C_FIELD(table, s16*, 0x78),
                                                                  slot->fieldC);
            func_001B3D18(slot);
        }
    }
    return 1;
}
void func_001B6188(void* base) {
    u8 i;
    for (i = 0; i < 4; i++) { M2C_FIELD(base, u8*, 0x734 + i * 0xC20) = 0; }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B61C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B6250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B6328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001BEBA0);
void func_001C1A68(void* out, void* input, void* data) {
    M2C_FIELD(out, void**, 8) = data;
    M2C_FIELD(out, void**, 4) = input;
    M2C_FIELD(out, f32*, 0) = __ee_max_s(__ee_max_s(M2C_FIELD(input, f32*, 0x80), M2C_FIELD(input, f32*, 0x84)),
                                         M2C_FIELD(input, f32*, 0x88));
    M2C_FIELD(out, f32*, 0) = __ee_max_s(M2C_FIELD(out, f32*, 0), M2C_FIELD(input, f32*, 0x8C));
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C1C48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C1CD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C2210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C2250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C79D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C7D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C7DB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C8108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C81F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C8478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C8560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CAB20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CADD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CB3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CC3A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CCAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CCF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CD360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CD650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CD8D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CDA28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CDAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CDB98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CDD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CE1B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CE3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CE780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CE9E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CEB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CEDA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CEF38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF1D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF6C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF8C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CFA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CFB00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CFB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CFE50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001DD7B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001DD7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001E45A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001E8B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001E9250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001E9C68);
void func_001ED2C8(void* state, u64 value, s32 data) {
    M2C_FIELD(state, s32*, 0x14) = 1;
    M2C_FIELD(state, u64*, 0) = value;
    M2C_FIELD(state, s32*, 8) = data;
    M2C_FIELD(state, s32*, 0x1C)++;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED4A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED4F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED6B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED718);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED830);
