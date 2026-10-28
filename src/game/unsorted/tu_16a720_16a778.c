#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00169EB8();
extern s32 func_00169EF8();
extern s32 func_00107D20();
extern s32 func_00160E70();
extern s32 func_00160ED8();
extern s32 func_001D4268();
extern s32 func_001C31F8();
extern s32 func_001C3228(f32);
extern s32 func_001C32B8();

s32 func_0016A778(void) {
    func_00169EB8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016A798);

void func_0016A7A0(void) {
    func_00169EF8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016A7C0);
extern s32 func_0016A4C0(void *, s32);
extern void func_00168618(void *, void *, s32, s32);
extern void *D_0040F4F4;

s32 func_0016AA78(void *arg0, s32 arg1, s32 arg2) {
    s32 result = func_0016A4C0(arg0, arg1);
    if (M2C_FIELD(arg0, u8 *, 0x11D)) {
        if (result != 0) {
            return 0;
        }
        {
            void *data;
            M2C_FIELD(arg0, u8 *, 0x11C) = 0;
            data = M2C_FIELD(arg0, void **, 0x160);
            func_00168618(D_0040F4F4, M2C_FIELD(data, void **, 0x54), M2C_FIELD(data, u8 *, 0x59), arg2);
        }
    } else if (result != 0) {
        void *data = M2C_FIELD(arg0, void **, 0x160);
        M2C_FIELD(arg0, u8 *, 0x11D) = 1;
        func_00168618(D_0040F4F4, M2C_FIELD(data, void **, 0x50), M2C_FIELD(data, u8 *, 0x58), arg2);
    }
    return 0;
}

s32 func_0016AB18(void) {
    func_0016A778();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016AB38);

void func_0016AB40(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x11D) = 0;
    M2C_FIELD(arg0, u8 *, 0x11C) = (u8) (M2C_FIELD(arg0, u8 *, 0x11C) ^ 1);
}

s32 func_0016AB58(s32 arg0, s32 arg1)
{
  s32 temp_2;
  temp_2 = func_00107D20(arg1 * 0xC);
  M2C_FIELD(arg0, s16 *, 4) = (s16) arg1;
  temp_2++;
  temp_2--;
  M2C_FIELD(arg0, s32 *, 0) = temp_2;
 do { M2C_FIELD(arg0, s16 *, 6) = 0; } while (0);
  return temp_2;
}

void func_0016ABA0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 6) = 0;
}

void func_0016ABA8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 > 0) {
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0) = arg1;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 4) = arg2;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 8) = arg3;
        M2C_FIELD(arg0, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 6) + 1);
    }
}

// UNVERIFIED: field meanings beyond the offsets used here.
typedef struct {
    void *value;
    s32 size;
    s32 flags;
} QueueEntry;
typedef struct {
    QueueEntry *entries;
    s16 capacity;
    s16 count;
} Queue;

void func_0016AC08(Queue *queue) {
    s32 i;
    for (i = 0; i < queue->count; i++) {
        func_00168618(D_0040F4F4, queue->entries[i].value, queue->entries[i].size, queue->entries[i].flags);
    }
    func_0016ABA0(queue);
}

void func_0016AC98(void) {
    func_00160E70();
}

extern void func_00160EA0(void *);

s32 func_0016ACB8(void *arg0, s64 arg1, s32 arg2, s32 arg3) {
    func_00160EA0(arg0);
    M2C_FIELD(arg0, s32 *, 0x24) = arg2;
    M2C_FIELD(arg0, s64 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x20) = arg3;
    M2C_FIELD(arg0, s32 *, 0x18) = arg2;
    return 1;
}

s32 func_0016AD18(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016AD38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016AD40);

void func_0016ADE0(void) {
    func_0016B670();
    func_001D4268();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016AE08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016AFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016B118);
extern s32 func_001D4630(s128, f32, f32);
extern s32 func_001D4858(void);
extern u8 D_0040D9B3;
extern s32 func_001D4A50(s32, f32);
extern s32 func_001D4998(void);

#ifdef NON_MATCHING
// Unmatched: global access uses different small-data addressing.
s32 func_0016B4F8(s32 arg0, s128 arg1) {
    func_001D4630(arg1, 0.0f, 0.0f);
    func_001D4858();
    if (D_0040D9B3 != 0) {
        func_001D4A50(3, 0.0f);
        func_001D4A50(4, 0.0f);
        func_001D4A50(5, 0.0f);
    } else {
        func_001D4A50(0, 0.0f);
        func_001D4A50(1, 0.0f);
        func_001D4A50(2, 0.0f);
    }
    return func_001D4998();
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016B4F8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016B590);
extern s32 D_0040F0E0;

#ifdef NON_MATCHING
// Unmatched: address formation and register scheduling differ.
s128 func_0016B5E0(void *arg0, void *arg1) {
    f32 value = M2C_FIELD(D_0040F0E0 + 0x20120, f32 *, 0x20);
    s128 result;
    M2C_FIELD(arg0, s128 *, 0x90) = M2C_FIELD(arg0, s128 *, 0xD0);
    M2C_FIELD(arg0, s128 *, 0x80) = M2C_FIELD(arg0, s128 *, 0xC0);
    result = M2C_FIELD(arg1, s128 *, 0);
    M2C_FIELD(arg0, s128 *, 0xA0) = result;
    M2C_FIELD(arg0, f32 *, 0x98) = value;
    M2C_FIELD(arg0, s128 *, 0xB0) = M2C_FIELD(arg1, s128 *, 0x10);
    M2C_FIELD(arg0, f32 *, 0xB8) = value + M2C_FIELD(arg1, f32 *, 0x18);
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016B5E0);
#endif
extern s32 func_0016B788(void);
extern s32 func_001D4618(void);

s32 func_0016B630(void) {
    if (!func_0016B788()) {
        return 0;
    }
    return func_001D4618();
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016B668);

void func_0016B670(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x48) = 1;
    func_001C31F8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16a720_16a778", func_0016B690);

void func_0016B710(void *arg0) {
    func_001C3228(M2C_FIELD(arg0, f32 *, 0x44));
}

extern void func_001C3278(void *, s128, f32, f32);

void func_0016B730(void *arg0) {
    func_001C3278(arg0, M2C_FIELD(arg0, s128 *, 0x30), M2C_FIELD(arg0, f32 *, 0x40), 0.0f);
}

void func_0016B758(void) {
    func_001C32B8();
}
