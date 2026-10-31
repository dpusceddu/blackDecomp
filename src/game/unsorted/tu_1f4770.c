#include "include_asm.h"
#include "ps2/prelude.h"

extern void* D_0040F0E0;
extern s32 func_001F5950(void*, void*);
/* UNVERIFIED: gameplay identities and complete object sizes. */
typedef struct ObjectiveAsset {
    u8 unknown[0x10];
    s32 id;
    s8 total;
    u8 flags;
} ObjectiveAsset;
typedef struct ObjectiveProgress {
    ObjectiveAsset* asset;
    s32 progress;
} ObjectiveProgress;
/* Native localization keys, kept in their owned read-only block. */
const char D_003F9680[] __attribute__((section(".rodata"), aligned(8))) = "FE_PRIMARYOBJ_NEW";
const char D_003F9698[] __attribute__((section(".rodata"), aligned(8))) = "LX_DESTRUCTION";
const char D_003F96A8[] __attribute__((section(".rodata"), aligned(8))) = "FE_BLACKMAILOBJ_UPDATE";
const char D_003F96C0[] __attribute__((section(".rodata"), aligned(8))) = "FE_BLACKMAILOBJ_DONE";
const char D_003F96D8[] __attribute__((section(".rodata"), aligned(8))) = "FE_INTELOBJ_UPDATE";
const char D_003F96F0[] __attribute__((section(".rodata"), aligned(8))) = "FE_INTELOBJ_DONE";
const char D_003F9708[] __attribute__((section(".rodata"), aligned(8))) = "FE_RECONOBJ_DONE";
const char D_003F9720[] __attribute__((section(".rodata"), aligned(8))) = "LX_ARMAMENT";
const char D_003F9730[] __attribute__((section(".rodata"), aligned(8))) = "FE_PRIMARYOBJ_UPDATE";
const char D_003F9748[] __attribute__((section(".rodata"), aligned(8))) = "FE_PRIMARYOBJ_DONE";
const char D_003F9760[] __attribute__((section(".rodata"), aligned(8))) = "FE_SECONDARYOBJ_UPDATE";
const char D_003F9778[] __attribute__((section(".rodata"), aligned(8))) = "FE_PRIMARYOBJ_FAILED";
extern void* D_0040F4C4;
extern char D_0040DDA8;
extern s128 D_0042BE30, D_0042BE40, D_0042BE50, D_0042BE60, D_0042BE70, D_0042BE80;
extern char* func_001087C8(void*, const char*);
extern void* func_00108818(void*, s32);
extern char* func_001F5418(void*, const char*, s32, s32);
struct ObjectiveMessages;
extern void func_001F5498(struct ObjectiveMessages*, const char*, const char*, s128, s32);

void func_001F4E38(void*, ObjectiveProgress*, s32, const char*);

extern s32 func_00275260(const char*, u16*, s32);
extern s32 func_00275128(const u16*, void*, s32);
extern s32 func_003848F8(u16*, const u16*, s32*, s32*, s32*);
/* These call signatures and the output buffer layout remain UNVERIFIED. */
extern void* D_0040F4D0;
extern void* D_0040F4E8;
extern void* func_00122900(void*, s8);
extern s32 func_0012F880(void*, void*, s32, void*);
extern s32 func_00160AA8(void*, s32);

void func_001F4D30(void* owner, const char* text, ObjectiveProgress* target) {
    if (func_001F5950(owner, target)) func_001F4E38(owner, target, 0, text);
}
void func_001F4D88(void* owner, const char* text, ObjectiveProgress* target) {
    if (func_001F5950(owner, target)) func_001F4E38(owner, target, 1, text);
}
void func_001F4DE0(void* owner, const char* text, ObjectiveProgress* target) {
    if (func_001F5950(owner, target)) func_001F4E38(owner, target, 3, text);
}
void func_001F4E38(void* self, ObjectiveProgress* objective, s32 kind, const char* text) {
    ObjectiveAsset* asset = objective->asset;
    switch (kind) {
        case 0:
            if (asset->flags & 2) break;
            if (asset->flags & 4) break;
            if (asset->flags & 8) break;
            if (asset->flags & 0x10) break;
            if (asset->flags & 0x20) break;
            func_001F5498(self, func_001087C8(D_0040F4C4, D_003F9680), text, D_0042BE30, 0xB);
            break;
        case 1: {
            const char* empty = &D_0040DDA8;
            if (asset->flags & 2) {
                const char* formatted = func_001F5418(self, func_001087C8(D_0040F4C4, D_003F9698), objective->progress,
                                                      objective->asset->total);
                func_001F5498(self, empty, formatted, D_0042BE40, 0xD);
            } else if (asset->flags & 4) {
                func_001F5498(self,
                              func_001F5418(self, func_001087C8(D_0040F4C4, D_003F96A8), objective->progress,
                                            objective->asset->total),
                              text, D_0042BE50, 0x13);
                func_001F5498(self, func_001087C8(D_0040F4C4, D_003F96C0), empty, D_0042BE50, 0x13);
            } else if (asset->flags & 8) {
                func_001F5498(self,
                              func_001F5418(self, func_001087C8(D_0040F4C4, D_003F96D8), objective->progress,
                                            objective->asset->total),
                              text, D_0042BE50, 0x13);
                func_001F5498(self, func_001087C8(D_0040F4C4, D_003F96F0), empty, D_0042BE50, 0x13);
            } else if (asset->flags & 0x10) {
                func_001F5498(self,
                              func_001F5418(self, func_001087C8(D_0040F4C4, D_003F9708), objective->progress,
                                            objective->asset->total),
                              text, D_0042BE70, 0xF);
            } else if (asset->flags & 0x20) {
                func_001F5498(self,
                              func_001F5418(self, func_001087C8(D_0040F4C4, D_003F9720), objective->progress,
                                            objective->asset->total),
                              text, D_0042BE80, 0x14);
            } else {
                if (asset->total >= 2) {
                    const char* done;
                    const char* heading = func_001087C8(D_0040F4C4, D_003F9730);
                    func_001F5498(self, heading,
                                  func_001F5418(self, text, objective->progress, objective->asset->total), D_0042BE30,
                                  0xB);
                    done = func_001087C8(D_0040F4C4, D_003F9748);
                    func_001F5498(self, done, func_00108818(D_0040F4C4, asset->id), D_0042BE30, 0);
                } else {
                    func_001F5498(self, func_001087C8(D_0040F4C4, D_003F9748), text, D_0042BE30, 0);
                }
            }
            break;
        }
        case 3:
            if (asset->flags & 2) {
                const char* destruction = func_001087C8(D_0040F4C4, D_003F9698);
                const char* heading = func_001087C8(D_0040F4C4, D_003F9760);
                func_001F5498(self, heading,
                              func_001F5418(self, destruction, objective->progress, objective->asset->total),
                              D_0042BE40, 0xD);
            } else if (asset->flags & 4) {
                func_001F5498(self,
                              func_001F5418(self, func_001087C8(D_0040F4C4, D_003F96A8), objective->progress,
                                            objective->asset->total),
                              text, D_0042BE50, 0x13);
            } else if (asset->flags & 8) {
                func_001F5498(self,
                              func_001F5418(self, func_001087C8(D_0040F4C4, D_003F96D8), objective->progress,
                                            objective->asset->total),
                              text, D_0042BE60, 0x10);
            } else if (asset->flags & 0x10) {
            } else if (asset->flags & 0x20) {
            } else {
                const char* heading = func_001087C8(D_0040F4C4, D_003F9730);
                func_001F5498(self, heading, func_001F5418(self, text, objective->progress, objective->asset->total),
                              D_0042BE60, 0xB);
            }
            break;
        case 2:
            if (asset->flags & 2) break;
            if (asset->flags & 4) break;
            if (asset->flags & 8) break;
            if (asset->flags & 0x10) break;
            func_001F5498(self, func_001087C8(D_0040F4C4, D_003F9778), text, D_0042BE30, 0);
            break;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5410);
#ifdef NON_MATCHING
// Unmatched: destination and output buffer use swapped saved registers.
char* func_001F5418(void* owner, const char* text, s32 first, s32 last) {
    s32 difference;
    s32 last_value;
    s32 first_value;
    u16 input[128];
    u16 output[128];
    char* destination;

    first_value = first;
    last_value = last;
    difference = last - first;
    func_00275260(text, input, 128);
    destination = (char*)owner + 0x18E4;
    func_003848F8(output, input, &first_value, &last_value, &difference);
    func_00275128(output, destination, 128);
    return destination;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5418);
#endif
#ifdef NON_MATCHING
// Unmatched: ring-index promotions and expanded-copy register allocation differ (132 instructions).
extern void* memcpy(void*, const void*, u32);
typedef struct ObjectiveMessage {
    char heading[128];
    char text[128];
} ObjectiveMessage;
/* Accessed native fields; original class and remaining members are UNVERIFIED. */
typedef struct ObjectiveMessages {
    u8 unknown00[0x940];
    s128 colors[8];
    s32 kinds[8];
    u8 unknown9e0[0x704];
    ObjectiveMessage messages[8];
    u8 unknown18e4[0x80];
    u16 head, next, count;
} ObjectiveMessages;

void func_001F5498(ObjectiveMessages* self, const char* heading, const char* text, s128 color, s32 kind) {
    s32 index = self->next;
    u16 count = self->count;
    char* destination;
    if (count >= 8) {
        index = (self->head + count - 1) % 8;
    } else {
        self->count = count + 1;
        self->next = (index + 1) % 8;
    }
    destination = self->messages[index].heading;
    memcpy(destination, heading, 127);
    memcpy(self->messages[index].text, text, 127);
    self->messages[index].heading[127] = 0;
    self->messages[index].text[127] = 0;
    self->colors[index] = color;
    self->kinds[index] = kind;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5498);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f4770", func_001F5770);
s32 func_001F5850(void) {
    s32 output[4];
    void* progress = (u8*)D_0040F4D0 + 0x910;
    void* level = func_00122900(D_0040F4E8, M2C_FIELD(D_0040F4D0, s8*, 0x5AAC));
    s32 difficulty = M2C_FIELD(D_0040F0E0, s32*, 0x2014C);
    s32 kind = func_0012F880(progress, level, difficulty, output);

    switch (kind) {
        case 0: return func_00160AA8((u8*)D_0040F4D0 + 0x8F0, (s8)M2C_FIELD(D_0040F0E0, s32*, 0x2014C));
        case 2: return output[0];
        case 1:
        default: return 0;
    }
}

void func_001F5928(void *arg0) {
    if (M2C_FIELD(D_0040F0E0, s32 *, 0x2014C) != 0) {
        M2C_FIELD(arg0, s8 *, 0x19A4) = 1;
    }
}

extern s32 func_00160E10(void*, s32);
static inline u8 ObjectiveHasNoCategory(u64 value) { return (value & 0x3E0000000000UL) == 0; }
s32 func_001F5950(void* owner, void* progress) {
    s32 allowed = 0;
    if (ObjectiveHasNoCategory(M2C_FIELD(M2C_FIELD(progress, void**, 0), u64*, 0x10)) ||
        func_00160E10(progress, M2C_FIELD(D_0040F0E0, s32*, 0x2014C)))
        allowed = 1;
    return allowed;
}
