#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/actor_slots.h"

extern void* D_0040F4D0;
typedef s32 (*EarlyUpdate)(void*, s128, void*);
#define UPDATE_TYPE_THREE_BANK(listOffset, countOffset)                                                                 \
    if (M2C_FIELD(self, s32*, listOffset)) {                                                                            \
        for (i = 0; i < M2C_FIELD(self, u16*, countOffset); i++) {                                                      \
            s32 offset = i * 4;                                                                                         \
            void* entry = M2C_FIELD(offset + M2C_FIELD(self, s32*, listOffset), void**, 0);                             \
            if (M2C_FIELD(entry, u8*, 0x11C) && M2C_FIELD(entry, s32*, 0x120) == 3) {                                   \
                void* vtable = M2C_FIELD(entry, void**, 0x10);                                                          \
                M2C_FIELD(vtable, EarlyUpdate*, 0xA4)((char*)entry + M2C_FIELD(vtable, s16*, 0xA0), frame, clock);      \
            }                                                                                                           \
        }                                                                                                               \
    }

void func_00165DF0(void* self, s128 frame) {
    s32 i;
    void* clock = (char*)D_0040F4D0 + 0x30;
    UPDATE_TYPE_THREE_BANK(0x48, 0);
    UPDATE_TYPE_THREE_BANK(0x4C, 2);
}
#undef UPDATE_TYPE_THREE_BANK

extern void func_00174578(void*);
typedef s32 (*WideUpdate)(void*, s128, void*);
typedef void (*FloatUpdate)(void*, f32);
typedef void (*ResetUpdate)(void*);
/* Calls reload the bank entry before clearing its flag because updates can move it. */
#define WIDE(P, C, F, S)                                                                                                \
    if (M2C_FIELD(self, s32*, P)) {                                                                                     \
        for (i = 0; i < M2C_FIELD(self, u16*, C); i++) {                                                                \
            s32 offset = i * 4;                                                                                         \
            void* entry = M2C_FIELD(offset + M2C_FIELD(self, s32*, P), void**, 0);                                      \
            if (M2C_FIELD(entry, u8*, F) && (!S || M2C_FIELD(entry, s32*, 0x120) != 3)) {                               \
                void* vtable = M2C_FIELD(entry, void**, 0x10);                                                          \
                if (M2C_FIELD(vtable, WideUpdate*, 0x9C)((char*)entry + M2C_FIELD(vtable, s16*, 0x98), frame, clock))   \
                    M2C_FIELD(M2C_FIELD(offset + M2C_FIELD(self, s32*, P), void**, 0), u8*, F) = 0;                     \
            }                                                                                                           \
        }                                                                                                               \
    }
#define TICK(P, C, F)                                                                                                   \
    if (M2C_FIELD(self, s32*, P)) {                                                                                     \
        for (i = 0; i < M2C_FIELD(self, u16*, C); i++) {                                                                \
            void* entry = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, P), void**, 0);                                       \
            if (M2C_FIELD(entry, u8*, F)) {                                                                             \
                void* vtable = M2C_FIELD(entry, void**, 0x10);                                                          \
                M2C_FIELD(vtable, FloatUpdate*, 0xC)((char*)entry + M2C_FIELD(vtable, s16*, 8), dt);                    \
            }                                                                                                           \
        }                                                                                                               \
    }
#define RESET(P, C)                                                                                                     \
    if (M2C_FIELD(self, s32*, P)) {                                                                                     \
        for (i = 0; i < M2C_FIELD(self, u16*, C); i++) {                                                                \
            void* entry = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, P), void**, 0);                                       \
            if (M2C_FIELD(entry, u8*, 0x1C)) {                                                                          \
                void* vtable = M2C_FIELD(entry, void**, 0x10);                                                          \
                M2C_FIELD(vtable, ResetUpdate*, 0x2C)((char*)entry + M2C_FIELD(vtable, s16*, 0x28));                    \
            }                                                                                                           \
        }                                                                                                               \
    }
#define DIRECT(P, C)                                                                                                    \
    if (M2C_FIELD(self, s32*, P)) {                                                                                     \
        for (i = 0; i < M2C_FIELD(self, u16*, C); i++) {                                                                \
            void* entry = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, P), void**, 0);                                       \
            if (entry) func_00174578(entry);                                                                            \
        }                                                                                                               \
    }
void func_00165F30(void* self, s128 frame, f32 dt) {
    s32 i;
    void* clock = (char*)D_0040F4D0 + 0x30;
    WIDE(0x48, 0, 0x11C, 1);
    WIDE(0x4C, 2, 0x11C, 1);
    TICK(0x58, 8, 0x18);
    TICK(0x5C, 0xA, 0x18);
    RESET(0x68, 0x10);
    RESET(0x6C, 0x12);
    TICK(0xC8, 0x40, 0x1C);
    TICK(0xCC, 0x42, 0x1C);
    RESET(0x70, 0x14);
    RESET(0x74, 0x16);
    DIRECT(0x78, 0x18);
    DIRECT(0x7C, 0x1A);
    WIDE(0x80, 0x1C, 0x130, 0);
    WIDE(0x84, 0x1E, 0x130, 0);
    WIDE(0x88, 0x24, 0x11C, 0);
    WIDE(0x8C, 0x26, 0x11C, 0);
    WIDE(0x90, 0x28, 0x11C, 0);
    WIDE(0x94, 0x2A, 0x11C, 0);
    WIDE(0x98, 0x2C, 0x11C, 0);
    WIDE(0x9C, 0x2E, 0x11C, 0);
}
#undef WIDE
#undef TICK
#undef RESET
#undef DIRECT

/* Detach the bank before releasing its non-null entries. */
void func_00167000(void* self, void* list) {
    s32 remaining;
    s32 count;
    void* vtable;
    void* entry;
    void** cursor;

    if (list == M2C_FIELD(self, void**, 0x68)) {
        count = M2C_FIELD(self, u16*, 0x10);
        M2C_FIELD(self, void**, 0x68) = NULL;
        M2C_FIELD(self, u16*, 0x10) = 0;
    } else {
        count = M2C_FIELD(self, u16*, 0x12);
        M2C_FIELD(self, void**, 0x6C) = NULL;
        M2C_FIELD(self, u16*, 0x12) = 0;
    }
    if (list != NULL) {
        cursor = list;
        if (count != 0) {
            remaining = count;
            do {
                entry = *cursor;
                if (entry != NULL) {
                    vtable = M2C_FIELD(entry, void**, 0x10);
                    M2C_FIELD(vtable, s32 (**)(void*), 0x24)((void*)((s8*)entry + M2C_FIELD(vtable, s16*, 0x20)));
                }
                remaining -= 1;
                cursor = (void**)((s8*)cursor + 4);
            } while (remaining != 0);
        }
    }
}

extern void func_00167A10(void*, void*, void*);
/* Binding descriptors occur at different offsets in each bank family. */
#define VISIT(P, C, F)                                                                                                  \
    if (M2C_FIELD(self, s32*, P)) {                                                                                     \
        for (i = 0; i < M2C_FIELD(self, u16*, C); i++) {                                                                \
            offset = i * 4;                                                                                             \
            listBase = M2C_FIELD(self, s32*, P);                                                                        \
            entry = M2C_FIELD(offset + listBase, void**, 0);                                                            \
            func_00167A10(self, entry, M2C_FIELD(entry, void**, F));                                                    \
        }                                                                                                               \
    }
void func_00167208(void* self) {
    s32 i, offset, listBase;
    void* entry;
    VISIT(0x48, 0, 0x118);
    VISIT(0x4C, 2, 0x118);
    VISIT(0x58, 8, 0x20);
    VISIT(0x5C, 0xA, 0x20);
    VISIT(0x60, 0xC, 0x18);
    VISIT(0x64, 0xE, 0x18);
    VISIT(0x50, 4, 0x1C);
    VISIT(0x54, 6, 0x1C);
    VISIT(0x68, 0x10, 0x18);
    VISIT(0x6C, 0x12, 0x18);
    VISIT(0x70, 0x14, 0x18);
    VISIT(0x74, 0x16, 0x18);
    VISIT(0x78, 0x18, 0x20);
    VISIT(0x7C, 0x1A, 0x20);
    VISIT(0x88, 0x24, 0x118);
    VISIT(0x8C, 0x26, 0x118);
    VISIT(0x90, 0x28, 0x118);
    VISIT(0x94, 0x2A, 0x118);
    VISIT(0x98, 0x2C, 0x118);
    VISIT(0x9C, 0x2E, 0x118);
    VISIT(0xA0, 0x20, 0x110);
    VISIT(0xA4, 0x22, 0x110);
    VISIT(0xA8, 0x30, 0x18);
    VISIT(0xAC, 0x32, 0x18);
    VISIT(0xB0, 0x34, 0x13C);
    VISIT(0xB4, 0x36, 0x13C);
    VISIT(0xD0, 0x44, 0x118);
    VISIT(0xD4, 0x46, 0x118);
}
#undef VISIT

extern void func_00167AA8(void *, void *, s64);

void func_00167A10(void *arg0, void *arg1, void *arg2) {
    s32 i;
    u8 result = M2C_FIELD(arg1, u8 *, 0xE);
    if (result == 0 && arg2 != 0) {
        i = 0;
        if (M2C_FIELD(arg2, u8 *, 4) != 0) {
            do {
                s64 *entry = (s64 *) (i * 8 + M2C_FIELD(arg2, s32 *, 0));
                i++;
                func_00167AA8(arg0, arg1, *entry);
            } while (i < M2C_FIELD(arg2, u8 *, 4));
        }
        M2C_FIELD(arg1, u8 *, 0xE) = 1;
    }
}
extern void func_00165C40(void*, s32);
extern s32 func_0012F2D8(void*, u64, void*);
extern void* D_0040F4E4;
extern void* D_0040F538;

/* Each bank has a separate native pointer/count pair. Keep the shared scan
 * temporaries across banks; callbacks may change the bank storage and counts. */
#define COLLECT_BINDINGS(listOffset, countOffset, skipNull)                        \
    if (M2C_FIELD(self, void***, listOffset)) {                                    \
        i = 0;                                                                   \
        if (M2C_FIELD(self, u16*, countOffset)) {                                  \
            do {                                                                 \
                offset = i * 4;                                                  \
                listBase = M2C_FIELD(self, s32*, listOffset);                      \
                entry = M2C_FIELD(offset + listBase, u64**, 0);                    \
                if (!skipNull || entry) {                                        \
                    value = *entry;                                              \
                    if (value == key) func_00165C40(output, (s32)entry);           \
                }                                                                \
                i++;                                                             \
            } while (i < M2C_FIELD(self, u16*, countOffset));                      \
        }                                                                        \
    }

void func_00167AA8(void* self, void* output, s64 key) {
    u8* pool;
    u8* active;
    s32 i, offset;
    u64 value;
    s32 listBase;
    u64* entry;
    COLLECT_BINDINGS(0x48, 0x0, 0);
    COLLECT_BINDINGS(0x4C, 0x2, 0);
    COLLECT_BINDINGS(0x58, 0x8, 0);
    COLLECT_BINDINGS(0x5C, 0xA, 0);
    COLLECT_BINDINGS(0x60, 0xC, 0);
    COLLECT_BINDINGS(0x64, 0xE, 0);
    COLLECT_BINDINGS(0x50, 0x4, 0);
    COLLECT_BINDINGS(0x54, 0x6, 0);
    COLLECT_BINDINGS(0x68, 0x10, 0);
    COLLECT_BINDINGS(0x6C, 0x12, 0);
    COLLECT_BINDINGS(0xC8, 0x40, 0);
    COLLECT_BINDINGS(0xCC, 0x42, 0);
    COLLECT_BINDINGS(0x70, 0x14, 0);
    COLLECT_BINDINGS(0x74, 0x16, 0);
    COLLECT_BINDINGS(0xC0, 0x3C, 0);
    COLLECT_BINDINGS(0xC4, 0x3E, 0);
    COLLECT_BINDINGS(0x78, 0x18, 0);
    COLLECT_BINDINGS(0x7C, 0x1A, 0);
    pool = D_0040F4E4;
    active = pool + 0x5804;
    {
        u8* entry = pool;
        i = 0;
        do {
            if (active[i]) {
                value = M2C_FIELD(entry, u64*, 0);
                if (value == key) func_00165C40(output, (s32)entry);
            }
            i++;
            entry += 0x160;
        } while (i < 64);
    }
    func_0012F2D8(D_0040F538, key, output);
    COLLECT_BINDINGS(0x88, 0x24, 0);
    COLLECT_BINDINGS(0x8C, 0x26, 0);
    COLLECT_BINDINGS(0x90, 0x28, 0);
    COLLECT_BINDINGS(0x94, 0x2A, 0);
    COLLECT_BINDINGS(0x98, 0x2C, 0);
    COLLECT_BINDINGS(0x9C, 0x2E, 0);
    COLLECT_BINDINGS(0xA0, 0x20, 0);
    COLLECT_BINDINGS(0xA4, 0x22, 0);
    COLLECT_BINDINGS(0xA8, 0x30, 1);
    COLLECT_BINDINGS(0xAC, 0x32, 1);
    COLLECT_BINDINGS(0xB0, 0x34, 0);
    COLLECT_BINDINGS(0xB4, 0x36, 0);
    COLLECT_BINDINGS(0xB8, 0x38, 0);
    COLLECT_BINDINGS(0xBC, 0x3A, 0);
    COLLECT_BINDINGS(0xD0, 0x44, 0);
    COLLECT_BINDINGS(0xD4, 0x46, 0);
}

#undef COLLECT_BINDINGS

extern void* D_0040F514;
typedef void (*BindingAction)(void*, s32);

/* The two nullable banks skip empty entries. All other banks require populated
 * entries. Reload the bank's entry after each matching key before dispatch. */
#define DISPATCH_BANK(listOffset, countOffset, skipNull)                                                     \
    if (M2C_FIELD(self, s32*, listOffset)) {                                                                 \
        for (i = 0; i < M2C_FIELD(self, u16*, countOffset); i++) {                                            \
            s64* node = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, listOffset), s64**, 0);                        \
            if (!skipNull || node) {                                                                       \
                key = *node;                                                                              \
                if (count > 0) {                                                                          \
                    const s64* cursor = keys;                                                             \
                    remaining = count;                                                                    \
                    do {                                                                                  \
                        if (key == *cursor) {                                                             \
                            void* entry = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, listOffset), void**, 0);   \
                            void* vtable = M2C_FIELD(entry, void**, 0x10);                                  \
                            M2C_FIELD(vtable, BindingAction*, 0x1C)(                                       \
                                (char*)entry + M2C_FIELD(vtable, s16*, 0x18), mode);                        \
                        }                                                                                 \
                        remaining--;                                                                      \
                        cursor++;                                                                         \
                    } while (remaining);                                                                  \
                }                                                                                         \
            }                                                                                             \
        }                                                                                                 \
    }

void func_00168618(void* self, const s64* keys, s32 count, s32 mode) {
    s32 i, remaining;
    s64 key;
    if (count) {
        DISPATCH_BANK(0x48, 0, 0);
        DISPATCH_BANK(0x4C, 2, 0);
        DISPATCH_BANK(0x78, 0x18, 0);
        DISPATCH_BANK(0x7C, 0x1A, 0);
        DISPATCH_BANK(0x68, 0x10, 0);
        DISPATCH_BANK(0x6C, 0x12, 0);
        DISPATCH_BANK(0x70, 0x14, 0);
        DISPATCH_BANK(0x74, 0x16, 0);
        DISPATCH_BANK(0x58, 8, 0);
        DISPATCH_BANK(0x5C, 0xA, 0);
        DISPATCH_BANK(0x60, 0xC, 0);
        DISPATCH_BANK(0x64, 0xE, 0);
        DISPATCH_BANK(0x50, 4, 0);
        DISPATCH_BANK(0x54, 6, 0);
        i = 0;
        if (M2C_FIELD(D_0040F514, s32*, 0x79A4) > 0) {
            do {
                void* entry = M2C_FIELD(i * 4 + M2C_FIELD(D_0040F514, s32*, 0x79AC), void**, 0);
                if (entry) {
                    key = M2C_FIELD(entry, s64*, 0);
                    if (count > 0) {
                        const s64* cursor = keys;
                        remaining = count;
                        do {
                            if (key == *cursor) {
                                void* vtable = M2C_FIELD(entry, void**, 0x10);
                                M2C_FIELD(vtable, BindingAction*, 0x1C)(
                                    (char*)entry + M2C_FIELD(vtable, s16*, 0x18), mode);
                            }
                            remaining--;
                            cursor++;
                        } while (remaining);
                    }
                }
                i++;
            } while (i < M2C_FIELD(D_0040F514, s32*, 0x79A4));
        }
        DISPATCH_BANK(0x88, 0x24, 0);
        DISPATCH_BANK(0x8C, 0x26, 0);
        DISPATCH_BANK(0x90, 0x28, 0);
        DISPATCH_BANK(0x94, 0x2A, 0);
        DISPATCH_BANK(0x98, 0x2C, 0);
        DISPATCH_BANK(0x9C, 0x2E, 0);
        DISPATCH_BANK(0xA0, 0x20, 0);
        DISPATCH_BANK(0xA4, 0x22, 0);
        DISPATCH_BANK(0xA8, 0x30, 1);
        DISPATCH_BANK(0xAC, 0x32, 1);
        DISPATCH_BANK(0xB0, 0x34, 0);
        DISPATCH_BANK(0xB4, 0x36, 0);
        DISPATCH_BANK(0xB8, 0x38, 0);
        DISPATCH_BANK(0xBC, 0x3A, 0);
        DISPATCH_BANK(0xC0, 0x3C, 0);
        DISPATCH_BANK(0xC4, 0x3E, 0);
        {
            s32 base = (s32)D_0040F4E4;
            u8* active = (u8*)(base + 0x5804);
            i = 0;
            do {
                if (active[i]) {
                    key = M2C_FIELD(i * 0x160 + base, s64*, 0);
                    if (count > 0) {
                        const s64* cursor;
                        void* entry;
                        remaining = count;
                        cursor = keys;
                        do {
                            /* Keep the receiver construction with each key dispatch;
                             * hoisting it changes the native address lifetimes. */
                            entry = (void*)(i * 0x160 + base);
                            if (key == *cursor) {
                                void* vtable = M2C_FIELD(entry, void**, 0x10);
                                M2C_FIELD(vtable, BindingAction*, 0x1C)(
                                    (char*)entry + M2C_FIELD(vtable, s16*, 0x18), mode);
                            }
                            remaining--;
                            cursor++;
                        } while (remaining);
                    }
                }
                i++;
            } while (i < 64);
        }
    }
}

#undef DISPATCH_BANK

#ifdef NON_MATCHING
// Unmatched: setup copies and cursor registers differ (17 instructions under O2).
void* func_00169898(void* state, s64 key) {
    s64** entries;
    entries = M2C_FIELD(state, s64***, 0x48);
    if (entries) {
        u16 count = M2C_FIELD(state, u16*, 0x0);
        s32 i = 0;
        if (count) {
            s64** cursor = entries;
            do {
                s64* entry = *cursor;
                i++;
                if (key == *entry) return entry;
                cursor++;
            } while (i < count);
        }
    }
    entries = M2C_FIELD(state, s64***, 0x4C);
    if (entries) {
        u16 count = M2C_FIELD(state, u16*, 0x2);
        s32 i = 0;
        if (count) {
            s64** cursor = entries;
            do {
                s64* entry = *cursor;
                i++;
                if (key == *entry) return entry;
                cursor++;
            } while (i < count);
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169898);
#endif
#ifdef NON_MATCHING
// Unmatched: setup copies and cursor registers differ (17 instructions under O2).
void* func_00169920(void* state, s64 key) {
    s64** entries;
    entries = M2C_FIELD(state, s64***, 0x70);
    if (entries) {
        u16 count = M2C_FIELD(state, u16*, 0x14);
        s32 i = 0;
        if (count) {
            s64** cursor = entries;
            do {
                s64* entry = *cursor;
                i++;
                if (key == *entry) return entry;
                cursor++;
            } while (i < count);
        }
    }
    entries = M2C_FIELD(state, s64***, 0x74);
    if (entries) {
        u16 count = M2C_FIELD(state, u16*, 0x16);
        s32 i = 0;
        if (count) {
            s64** cursor = entries;
            do {
                s64* entry = *cursor;
                i++;
                if (key == *entry) return entry;
                cursor++;
            } while (i < count);
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169920);
#endif
/* Each bank entry supplies the callback object at +0x20. Form its native 32-bit address before converting it. */
extern void func_00177EE8(void*, s32, s32);
void func_001699A8(void* self, void* actor) {
    s32 i;
    s32 bit = M2C_FIELD(actor, s32*, 0x380);
    s32 mask = 1 << bit;
    if (M2C_FIELD(self, void**, 0x70)) {
        for (i = 0; i < M2C_FIELD(self, u16*, 0x14); ++i) {
            s32 address = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, 0x70), s32*, 0);
            void* entry = (void*)(address + 0x20);
            if (M2C_FIELD(entry, s32*, 0x64) & mask) func_00177EE8(entry, bit, 0);
        }
    }
    if (M2C_FIELD(self, void**, 0x74)) {
        for (i = 0; i < M2C_FIELD(self, u16*, 0x16); ++i) {
            s32 address = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, 0x74), s32*, 0);
            void* entry = (void*)(address + 0x20);
            if (M2C_FIELD(entry, s32*, 0x64) & mask) func_00177EE8(entry, bit, 0);
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169A98);
/* UNVERIFIED: original bank identities and virtual callback name. */
extern s32 func_001626D0(void*);
void func_00169AA0(void* self) {
    u16 i;
    for (i = 0; i < M2C_FIELD(self, u16*, 0x14); ++i)
        func_001626D0(M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, 0x70), void**, 0));
    for (i = 0; i < M2C_FIELD(self, u16*, 0x16); ++i)
        func_001626D0(M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, 0x74), void**, 0));
    for (i = 0; i < M2C_FIELD(self, u16*, 0x38); ++i) {
        void* entry = M2C_FIELD(i * 4 + M2C_FIELD(self, s32*, 0xB8), void**, 0);
        void* vt = M2C_FIELD(entry, void**, 0x10);
        M2C_FIELD(vt, void (**)(void*), 0x2C)((char*)entry + M2C_FIELD(vt, s16*, 0x28));
    }
}
void func_00169B88(void* state) {
    s32 i;
    for (i = 0; i < M2C_FIELD(state, u16*, 0x44); i++) {
        void* entry = M2C_FIELD(state, void***, 0xD0)[i];
        M2C_FIELD(entry, s8*, 0x11C) = 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016D7F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016D958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016DB58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016DC80);
extern void func_00179B60(void*, void*);
extern s32 func_0016FAB0(void*, void*);
/* UNVERIFIED: surrounding manager layout and remaining removal interfaces. */
s32 func_0016E6B0(void* self, void* actor) {
    s32 index = M2C_FIELD(actor, s32*, 0x380);
    s32 result;
    if (index != -1) {
        ActorSlotTable_Remove((Recovered_ActorSlotTable*)((char*)self + 0xFA8), index);
        M2C_FIELD(actor, s32*, 0x380) = -1;
        func_00179B60((char*)self + 0x1144, actor);
        result = func_0016FAB0((char*)self + 0x22B28, actor);
    } else {
        result = 0;
    }
    return result;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E7A8);
extern s128 D_004432A0;
void func_0016E7F8(void* arg0) {
    void* base = (char*)arg0 + 0x20000;
    s128 value;
    M2C_FIELD(base, s32*, 0x2BCC) = 0;
    value = D_004432A0;
    M2C_FIELD(base, s32*, 0x2BD0) = 0;
    M2C_FIELD(base, s128*, 0x2BE0) = value;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E820);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E928);
typedef struct {
    void** entries;
    u8* occupied;
    s32 count;
} Recovered_ActorPool;

extern void* func_00107D20(u32);

void func_0016EA10(Recovered_ActorPool* pool, s32 count) {
    s32 i;
    pool->count = count;
    pool->entries = func_00107D20(count * 4);
    pool->occupied = func_00107D20(pool->count);
    for (i = 0; i < pool->count; i++) pool->entries[i] = 0;
}
void* func_0016EAD0(Recovered_ActorPool* pool) {
    s32 i;
    for (i = 0; i < pool->count; i++) {
        if (!pool->occupied[i]) {
            pool->occupied[i] = 1;
            return pool->entries[i];
        }
    }
    return 0;
}
void func_0016EB28(Recovered_ActorPool* pool, void* entry) {
    s32 i;
    for (i = 0; i < pool->count; i++) {
        if (pool->entries[i] == entry) {
            pool->occupied[i] = 0;
            return;
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00171ED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001721E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001722A0);
extern void* D_0040F4D4;
/* The native mask query returns a signed 16-bit value. */
static inline s16 ActorMaskBitValue(const u16* mask, s32 bit) { return *mask & (1U << bit); }

/* UNVERIFIED: original mask/container class and full manager layout. */
void* func_00174040(u16* mask) {
    s32 i;
    if (*(s16*)mask == 0) return NULL;
    for (i = 0; i < 16; ++i) {
        if (ActorMaskBitValue(mask, i)) return (char*)D_0040F4D4 + (i * 0x1FD0 + 0x2B00);
    }
    return NULL;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001740A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00174858);
void func_00174930(void* state, void* entry) {
    s32 i;
    for (i = 0; i < M2C_FIELD(M2C_FIELD(state, void**, 0), u8*, 0x34); i++) {
        void** slot = (void**)(i * 4 + M2C_FIELD(state, u32*, 4));
        if (entry == *slot) {
            M2C_FIELD(state, u8*, 8)++;
            *slot = 0;
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176310);
extern void* D_0040F4D4;

void func_00176EE0(void* output) {
    void* state = D_0040F4D4;
    s32 value = M2C_FIELD(state, s32*, 0xA40);
    M2C_FIELD(output, s32*, 0) = value;
    M2C_FIELD(state, s32*, 0xA40) = value + 1;
}

typedef struct {
    s32 unk_00, unk_04, unk_08, unk_0C;
    s8 pending;
} Recovered_PairState;

void func_00176FB0(Recovered_PairState* state, s32 first, s32 second) {
    if (state->pending == 0) {
        state->unk_00 = first;
        state->unk_08 = second;
        state->pending = 1;
    } else {
        state->unk_04 = first;
        state->unk_0C = second;
        state->pending = 0;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176FE0);
typedef struct {
    s32 flags;
    f32 channels[4][2];
} Recovered_Channels;

s32 func_00176FF0(Recovered_Channels* state) {
    s32 i;
    state->flags = 0;
    for (i = 0; i < 2; i++) {
        state->channels[0][i] = 1.0f;
        state->channels[1][i] = 1.0f;
        state->channels[2][i] = 1.0f;
        state->channels[3][i] = 1.0f;
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177030);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001770E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177A70);
s32 func_00177AA0(void* state, s32 value) {
    if (M2C_FIELD(state, s32*, 0x28) == value) return 1;
    if (M2C_FIELD(state, s32*, 0x28) != 0) return 0;
    M2C_FIELD(state, s32*, 0x28) = value;
    return 1;
}

s32 func_00177B48(void* state, s32 bit) {
    u32 mask = 1U << bit;
    return (~(M2C_FIELD(state, u32*, 0x14) | M2C_FIELD(state, u32*, 0x18)) & mask) != 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00179B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00179BD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017A9F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AF20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AFD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A7F88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A80F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A8168);
void func_001A8300(void* base) {
    u32* offsets = (u32*)((u32)base + M2C_FIELD(base, u32*, 0));
    while (*offsets) {
        u32* entry = (u32*)((u32)base + *offsets);
        *entry = *entry + (u32)base;
        offsets++;
    }
    offsets = (u32*)((u32)base + M2C_FIELD(base, u32*, 0));
    *offsets = 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A8350);
