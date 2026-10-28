#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002AC628();
extern s32 func_0035C6EC();
extern s32 func_0027BA68();
extern s32 func_0027B688();
extern s32 func_0027BB98();

void func_0027ACC8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027ACD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B148);
extern void func_002AC568(void*);
extern void func_002AA340(void*);
extern void func_002AF778(void*, void*);
extern s32 func_002A9178(void*);
#ifdef NON_MATCHING
// Unmatched: argument and store scheduling differ.
s32 func_0027B260(void* self) {
    s32 result;
    func_002AC568(M2C_FIELD(self, void**, 0x60));
    func_002AC568(M2C_FIELD(self, void**, 0x64));
    func_002AA340(M2C_FIELD(self, void**, 0x5C));
    func_002AF778(M2C_FIELD(self, void**, 0x58), 0);
    result = func_002A9178(M2C_FIELD(self, void**, 0x58));
    M2C_FIELD(self, void**, 0x68) = 0;
    M2C_FIELD(self, void**, 0x60) = 0;
    M2C_FIELD(self, void**, 0x64) = 0;
    M2C_FIELD(self, void**, 0x58) = 0;
    M2C_FIELD(self, void**, 0x5C) = 0;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B260);
#endif

s32 func_0027B2C8(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x6C) = -1.0f;
    return 1;
}

void func_0027B2E0(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0x68) = arg1;
    M2C_FIELD(arg1, void **, 0x30) = arg0;
}

extern f32 func_0029DD08(f32);
extern void func_002A91D8(void*, f32*);
void func_0027B2F0(void* self, f32 angle) {
    f32 x = func_0029DD08(angle * 0.5f * 0.017453292f) * M2C_FIELD(self, f32*, 0x70);
    f32* values = (f32*)((u8*)self + 0x48);
    f32 y = x / M2C_FIELD(self, f32*, 0x74);
    M2C_FIELD(self, f32*, 0x48) = x;
    values[1] = y;
    M2C_FIELD(self, f32*, 0x54) = 1.0f / y;
    M2C_FIELD(self, f32*, 0x50) = 1.0f / M2C_FIELD(self, f32*, 0x48);
    func_002A91D8(M2C_FIELD(self, void**, 0x58), values);
    M2C_FIELD(self, f32*, 0x6C) = angle;
}

void func_0027B388(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x74) = fparg0;
}

s32 func_0027B390(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_5;

    func_002AC628(M2C_FIELD(arg0, s32 *, 0x60), M2C_FIELD(arg1, s32 *, 0x60), arg2);
    temp_5 = M2C_FIELD(arg1, s32 *, 0x64);
    if (temp_5 != 0) {
        func_002AC628(M2C_FIELD(arg0, s32 *, 0x64), temp_5, arg2);
    }
    M2C_FIELD(arg0, s32 *, 0x78) = (s32) M2C_FIELD(arg2, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x7C) = (s32) M2C_FIELD(arg2, s32 *, 0xC);
    temp_2 = M2C_FIELD(arg1, s32 *, 0x80);
    M2C_FIELD(arg0, s32 *, 0x80) = temp_2;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B408);

void func_0027B648(void *arg0, s32 arg1, s32 arg2)
{
  M2C_FIELD(arg0, s32 *, 8) = arg1;
  M2C_FIELD(arg0, s32 *, 0xC) = arg2;
  M2C_FIELD(arg0, s32 *, 0) = (M2C_FIELD(arg0, s32 *, 4) = 0);
  func_0035C6EC(arg1, 0, arg2 << 5);
}

// UNVERIFIED: original record and ring identities, and unused fields.
typedef struct { s32 key; u8 unknown04[0x1A]; u8 occupied, unknown1F; } Recovered_RingRecord;
typedef struct { s32 cursor, used; Recovered_RingRecord* records; s32 capacity; } Recovered_RecordRing;
s32 func_0027B688(Recovered_RecordRing* ring) {
    s32 index = ring->cursor;
    Recovered_RingRecord* records = ring->records;
    if (records[index].occupied) {
        do {
            index++;
            if (index >= ring->capacity) index = 0;
        } while (records[index].occupied);
    }
    ring->cursor = index;
    return index;
}

s32 func_0027B6D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_18;
    void *temp_4;

    temp_18 = func_0027BA68(arg2, arg3, arg4);
    temp_4 = M2C_FIELD(arg0, s32 *, 8) + (func_0027B688(arg0) << 5);
    M2C_FIELD(temp_4, s32 *, 0xC) = arg2;
    M2C_FIELD(temp_4, s32 *, 0x10) = arg3;
    M2C_FIELD(temp_4, s32 *, 0x14) = arg4;
    M2C_FIELD(temp_4, s32 *, 0x18) = temp_18;
    M2C_FIELD(temp_4, s8 *, 0x1D) = (s8) arg5;
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
    return (s32) temp_4;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BA60);
extern char* func_0035CBC0(char*, const char*);
extern char* func_0035C7A4(char*, const char*);
extern s32 func_0035CCD8(const char*);
extern char D_0040DE88[];
extern s32 func_0027C278(char*);
s32 func_0027BA68(const char* base, const char* path, const char* name) {
    char buffer[512];
    func_0035CBC0(buffer, base);
    func_0035C7A4(buffer, path);
    if (buffer[func_0035CCD8(buffer) - 1] != '/') func_0035C7A4(buffer, D_0040DE88);
    func_0035C7A4(buffer, name);
    return func_0027C278(buffer);
}
#ifdef NON_MATCHING
// Unmatched: loop register allocation differs.
s32 func_0027BAE8(void* object, s32 key) {
    Recovered_RecordRing* ring = object;
    s32 used = ring->used;
    s32 seen = 0;
    s32 i = 0;
    if (used > 0) {
        s32 capacity = ring->capacity;
        if (capacity > 0) {
            Recovered_RingRecord* record = ring->records;
            do {
                if (record->occupied) {
                    seen++;
                    if (record->key == key) return (s32)record;
                }
                record++;
                i++;
            } while (seen < used && i < capacity);
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BAE8);
#endif
// UNVERIFIED: original type and callback identity.
typedef struct { u8 unknown[0x10]; s16 adjustment; u16 unknown12; void (*callback)(void*, s32); } Recovered_RingVtable;
typedef struct { u8 unknown[0x10]; Recovered_RingVtable* vtable; } Recovered_RingOwner;
extern s32 func_0027BAE8(void*, s32);
void func_0027BB50(Recovered_RingOwner* self, s32 arg) {
    s32 result = func_0027BAE8(self, arg);
    if (result) self->vtable->callback((u8*)self + self->vtable->adjustment, result);
}
#ifdef NON_MATCHING
// Unmatched: section is eight bytes shorter despite matching instructions.
s32 func_0027BB98(Recovered_RecordRing* ring, Recovered_RingRecord* record) {
    record->occupied = 0;
    return --ring->used;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BB98);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BBB8);

void func_0027BC38(void) {

}

void func_0027BC40(void) {

}

void func_0027BC48(void) {

}

void func_0027BC50(void) {

}

void func_0027BC58(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BC60);

void func_0027BD00(Recovered_RecordRing* ring, Recovered_RingRecord* record) {
    func_0027BB98(ring, record);
}
