#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern void func_00181AD0(void *arg0, s32 arg1);
extern s32 func_00160E70();
extern s32 func_00165BC8(s32, s32);
extern s32 func_0018DDD8();
extern s32 func_00189BF8();
extern s32 func_00189250();
extern s32 func_00189AD0();
extern s32 func_0018C088();
extern s32 func_00181B08();
extern s32 func_00173610();

/* Local PS2 views; original class names and untouched fields are UNVERIFIED. */
typedef struct AiEntryTableDefinition {
    u8 unknown00[0x20];
    s64* identities;
    u8 count;
    u8 mode;
} AiEntryTableDefinition;

typedef struct AiEntryTable {
    void** entries;
    s32 mode;
    s32 count;
    u32 unknown0C;
    s64 identity;
    AiEntryTableDefinition* definition;
} AiEntryTable;

typedef struct AiVectorDefinition {
    u8 unknown00[0x10];
    s128 vector;
    f32 value;
} AiVectorDefinition;

typedef struct AiVectorEntry {
    u8 unknown00[0x18];
    AiVectorDefinition* definition;
    u32 unknown1C;
    s128 vector;
    f32 value;
    u32 unknown34;
    s64 identity;
    AiVectorDefinition* source;
} AiVectorEntry;

typedef struct AiReactionTuning {
    f32 low, high, gainLimit, secondaryLow, secondaryHigh, multiplier;
    s32 minimumLevel, maximumLevel;
    f32 nearDistance, farDistance;
} AiReactionTuning;

extern s128 D_00415870, D_004432A0;
extern s32 func_00160EA0(void*);
extern void* func_00107D20(s32);
extern s8 func_00183858(void*, s8);
extern s8 func_00183888(void*, s8);
extern s8 func_001838C0(AiEntryTable*, s8, s32);
extern void func_00173640(f32*, f32);
extern AiReactionTuning D_003F6350[];
extern s32 func_00183FD8(void*, s32, s128, void*, f32);
extern void func_001858A8(void*, s32, s128, f32, void*);
extern void func_001840C8(void*, s32, s128, void*, s32, f32);

const f32 D_003F6570[] = {30.0f, 1.5f, 10.0f, 0.0f};

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183380);

void func_001834B0(s32 *arg0) {
    func_00181AD0(*arg0 + 0xEC0, 0xD);
}

void func_001834D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x30) = arg1;
}

s32 func_001834E0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30);
}

s32 func_001834E8(void *arg0) {
    s32 var_2;

    var_2 = M2C_FIELD(arg0, s32 *, 4);
    if (var_2 < 0) {
        var_2 = M2C_FIELD(arg0, s32 *, 8);
    }
    return var_2;
}

s32 func_00183500(void *arg0)
{
  void *temp_2;
  temp_2 = *((void **) (((s8 *) arg0) + 0x30));
  if (temp_2 == NULL)
  {
    return 0;
  }
  if (arg0 || temp_2)
  {
    return *((s32 *) (((s8 *) temp_2) + (0x10 & 0xFFFFFFFFFFFFFFFFu)));
  }
  else
  {
    return M2C_FIELD(temp_2, s32 *, 0x10);
  }
}

s128 func_00183520(void* self) {
    if (M2C_FIELD(self, f32*, 0xC) > 0.0f) return D_00415870;
    return D_004432A0;
}

s128 func_00183558(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0xC4) == 2) {
        return M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s128 *, 0x30);
    }
    return M2C_FIELD(arg1, s128 *, 0xA0);
}

void func_00183578(s32 arg0, s32 arg1) {
    func_00160E70();
    func_00165BC8(arg0, arg1);
}

s32 func_001835B8(AiVectorEntry* self, s64 identity, AiVectorDefinition* definition) {
    func_00160EA0(self);
    self->identity = identity;
    self->source = definition;
    self->vector = definition->vector;
    self->value = definition->value;
    self->definition = definition;
    return 1;
}

void func_00183618(AiEntryTable* self, s64 identity, AiEntryTableDefinition* definition) {
    s32 i;
    self->identity = identity;
    self->definition = definition;
    self->count = definition->count;
    self->entries = func_00107D20(self->count * sizeof(*self->entries));
    for (i = 0; i < self->count; i++) {
        self->entries[i] = NULL;
    }
}

s32 func_00183688(void *arg0, s64 arg1, void *arg2) {
    M2C_FIELD(arg0, s64 *, 0x10) = arg1;
    M2C_FIELD(arg0, void **, 0x18) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg2, u8 *, 0x24);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg2, u8 *, 0x25);
    return 1;
}

s32 func_001836A8(AiEntryTable* self, AiVectorEntry* entry) {
    s64 identity = entry->identity;
    s32 i;
    s32 found = 0;
    for (i = 0; i < self->count; i++) {
        if (self->definition->identities[i] == identity) {
            self->entries[i] = entry;
            found = 1;
        }
    }
    return found;
}

s32 func_00183710(void *arg0, s8 arg1) {
    if ((arg1 >= 0) && (arg1 < M2C_FIELD(arg0, s32 *, 8))) {
        return M2C_FIELD(((arg1 * 4) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0);
    }
    return 0;
}

s8 func_00183748(AiEntryTable* self, s8 index, s32 forward) {
    s8 next = index;
    s8 previous = index;
    switch (self->mode) {
        case 0: next = func_00183858(self, next); break;
        case 1: next = func_00183888(self, next); break;
        case 2: next = func_001838C0(self, next, forward); break;
    }
    if (self->entries[next] == NULL) {
        s32 direction = previous < next;
        s8 result;
        do {
            result = func_00183748(self, next, direction);
        } while (self->entries[result] == NULL && next != result);
        if (result == next) return previous;
        next = result;
    }
    return next;
}

s8 func_00183858(void *arg0, s8 arg1) {
    s8 var_5;

    var_5 = arg1;
    if (var_5 < (M2C_FIELD(arg0, s32 *, 8) - 1)) {
        var_5 += 1;
    }
    return var_5;
}

s8 func_00183888(void *arg0, s8 arg1)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 8;
  if (arg1 < ((*((s32 *) new_var)) - 1))
  {
    arg1 = arg1 + 1;
  }
  else
  {
    arg1 = 0;
  }
  return arg1;
}

s8 func_001838C0(AiEntryTable* self, s8 index, s32 forward) {
    if (forward) {
        if (index < self->count - 1) index++;
        else if (index > 0) index--;
    } else {
        if (index > 0) index--;
        else index++;
    }
    return index;
}

void func_00183910(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183AA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183BC0);

#include "ps2/recovered_types.h"
extern M2C_UNK D_003F6540;

s32 func_00183C80(s32 *arg0, s32 arg1, s32 arg2, f32 fparg0) {
    switch (arg1) {
    case 1:
    case 2:
    case 3:
    case 7:
    case 11:
        if (M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) != M2C_FIELD(arg2, s32 *, 0x3A4)) {
            return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
        }
        return 0;
    case 5:
        if ((M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) != M2C_FIELD(arg2, s32 *, 0x3A4)) && (M2C_FIELD(arg0, s32 *, 0x64) >= 2)) {
            /* Duplicate return node #6. Try simplifying control flow for better match */
            return 0;
        }
        /* Duplicate return node #3. Try simplifying control flow for better match */
        return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
    default:
        return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
    }
}

void func_00183D28(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    void *temp_5;

    if (arg2 != 0) {
        temp_5 = M2C_FIELD(arg0, u32 *, 0);
        if ((M2C_FIELD(arg2, s32 *, 0x3A4) != M2C_FIELD(M2C_FIELD(temp_5, void **, 0x7C), s32 *, 0x3A4)) && ((M2C_FIELD(arg2, s32 *, 0xC4) == 2) || (func_0018DDD8((s32) (temp_5 + 0xC94)) != 0)) && (arg1 > 0) && (arg1 < 4) && (func_00189BF8((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), M2C_FIELD(arg2, s32 *, 0x380)) != 0) && (func_00189250((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), M2C_FIELD(arg2, s32 *, 0x380)) != 0)) {
            func_00189AD0((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), arg2);
            func_0018C088((s32) sp, arg2);
            func_00181B08((s32) (M2C_FIELD(arg0, u32 *, 0) + 0xEC0), (s32) sp);
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183E00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183EA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183EA8);
void func_00183EF8(void* self, s32 kind, s128 vector, void* actor, f32 scale) {
    s32 changed;
    f32 value;
    if (scale <= 0.0f) return;
    changed = func_00183FD8(self, kind, vector, actor, scale);
    func_001858A8(self, kind, vector, scale, actor);
    func_001840C8(self, kind, vector, actor, changed, scale);
    value = M2C_FIELD(self, f32*, 0x30);
    value += __ee_max_s(scale * (D_003F6350[kind].gainLimit - value), 0.0f);
    M2C_FIELD(self, f32*, 0x30) = value;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00183FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_001840C8);

void * func_00184238(void *arg0, void *arg1) {
    return (void *) ((func_00173610(arg0 + (((s32) arg1 * 4) + 0x34)) ^ 1) & 0xFF);
}

s32 func_00184268(void* self, s32 index) {
    f32* timer = (f32*)((u8*)self + (index * 4 + 0x34));
    s32 expired = func_00173610(timer);
    func_00173640(timer, D_003F6570[index]);
    return expired;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_001842C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_001843C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_00184550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260", func_001847B8);
