#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_003753E0();
extern s32 func_003778D8(void*, const char*);
extern s32 func_00377968(void*, s32);
extern s32 func_0031D268(void *, M2C_UNK, M2C_UNK);
extern s32 func_0037B1D0();
extern s32 func_0037B220(s32);

void func_00377840(void) {
    func_003753E0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377860);

void func_00377868(void *arg0, const char* name) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_003778D8(arg0, name) << 5));
}

void func_003778A0(void *arg0, s32 key) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_00377968(arg0, key) << 5));
}

extern s32 func_00316400(void*, const char*);
s32 func_003778D8(void* self, const char* name) {
    u32 i = 0;
    void* header = M2C_FIELD(self, void**, 0x124);
    if (M2C_FIELD(header, u32*, 0xC)) {
        u32 table = M2C_FIELD(header, u32*, 0x10);
        do {
            void* record = M2C_FIELD((i << 5) + table, void**, 0);
            if (record && func_00316400(record, name) == 0) return i;
            header = M2C_FIELD(self, void**, 0x124);
            i++;
            if (i >= M2C_FIELD(header, u32*, 0xC)) break;
            table = M2C_FIELD(header, u32*, 0x10);
        } while (1);
    }
    return 0;
}
// UNVERIFIED: original service table and callback identity.
typedef struct { u8 unknown[0xE8]; s32 (*compare)(s32, s32); } Recovered_CompareService;
extern Recovered_CompareService D_00449438;
s32 func_00377968(void* self, s32 key) {
    u32 i = 0;
    void* header = M2C_FIELD(self, void**, 0x124);
    if (M2C_FIELD(header, u32*, 0xC)) {
        Recovered_CompareService* service = &D_00449438;
        do {
            s32 record = M2C_FIELD((i << 5) + M2C_FIELD(header, u32*, 0x10), s32*, 4);
            if (record && service->compare(record, key) == 0) return i;
            i++;
            header = M2C_FIELD(self, void**, 0x124);
        } while (i < M2C_FIELD(header, u32*, 0xC));
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377A10);
extern void func_00318478(u32, u32, u32*, u32*);
s32 func_00377A20(void* self, void* arg1, s32 index) {
    u32 sp[2];
    void* entry = M2C_FIELD(M2C_FIELD(self, void**, 0x124), u8**, 0x18) + index * 0x28;
    u32 size = M2C_FIELD(entry, u32*, 0x20) / M2C_FIELD(entry, u16*, 0x1A) * M2C_FIELD(entry, s32*, 0xC);
    u32 result = M2C_FIELD(arg1, s32*, 4) * size;
    void* info;
    func_00318478(M2C_FIELD(arg1, u32*, 8), size, &sp[0], &sp[1]);
    info = M2C_FIELD(entry, void**, 0x14);
    result += sp[0];
    if (!(M2C_FIELD(info, u8*, 0x18) & 4)) result /= M2C_FIELD(info, u8*, 0xD);
    return result;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377BD8);
// UNVERIFIED: original buffer type and identity.
typedef struct { u8 data[0x2000]; s32 occupied; } Recovered_ScratchBuffer;
extern Recovered_ScratchBuffer D_0048AB88[2];
void* func_00377BE0(void) {
    s32 i = 0;
    u8* buffer = (u8*)D_0048AB88;
    s32* occupied = &D_0048AB88[0].occupied;
    do {
        i++;
        if (*occupied) {
            buffer += 0x2004;
            occupied = (s32*)((u8*)occupied + 0x2004);
        } else {
            *occupied = 1;
            return buffer;
        }
    } while (i < 2);
    return 0;
}
#ifdef NON_MATCHING
// Unmatched: loop and return-path scheduling differ.
void func_00377C28(void* buffer) {
    s32 i = 0;
    if (buffer == D_0048AB88) {
        D_0048AB88[0].occupied = 0;
        return;
    }
    do {
        i++;
        if (i < 2) {
            if (buffer == &D_0048AB88[i]) {
                D_0048AB88[i].occupied = 0;
                return;
            }
        }
    } while (i < 2);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377C28);
#endif

void * func_00377C80(void *arg0, s32 arg1, s16 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s16 *, 4) = arg2;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    return (func_0031D268(arg0 + 0xC, 1, 1) == 0) ? NULL : arg0;
}


s32 func_00378698(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x340) = 0;
    return (func_0037B1D0(arg0 + 0x104, arg1, 0xBB80, M2C_FIELD(arg2, s32 *, 0), M2C_FIELD(arg2, s32 *, 4), M2C_FIELD(arg2, s32 *, 8)) == 0) ? 0 : arg0;
}


s32 func_00378740(s32 arg0) {
    func_0037B220(arg0 + 0x104);
    return arg0;
}
