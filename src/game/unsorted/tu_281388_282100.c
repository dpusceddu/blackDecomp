#include "include_asm.h"
#include "game/aligned_buffer.h"
#include "ps2/prelude.h"
#include "game/timed_value_pool.h"

extern u128 D_00443230;

extern s32 func_00274FC8(s32);
extern s32 func_00274F60(s32);

s32 func_00282100(void *arg0) {
    s32 temp_16;

    temp_16 = M2C_FIELD(arg0, s32 *, 0x54);
    if (temp_16 != 1) {
        if (temp_16 < 2) {
            if (temp_16 != 0) {
                return 0;
            }
            goto block_7;
        }
        if (temp_16 != 2) {
            return 0;
        }
        goto block_7;
    }
    func_00282170(arg0);
    M2C_FIELD(arg0, s32 *, 0x54) = temp_16;
block_7:
    return 1;
}

s32 func_00282170(void *arg0) {
    func_00274FC8(arg0 + 0x38);
    M2C_FIELD(arg0, s32 *, 0x54) = 2;
    return 1;
}

s32 func_002821A8(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {                                 /* irregular */
    case 0:
        return (s32)AlignedBuffer_Allocate((Recovered_AlignedBuffer*)(arg0 + 0x1C), arg1);
    case 1:
        return (s32)AlignedBuffer_Allocate((Recovered_AlignedBuffer*)(arg0 + 0x38), arg1);
    default:
        return 0;
    }
}

void func_002821F0(s32 arg0) {
    func_00274F60(arg0 + 0x38);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282100", func_00282210);
void TimedValuePool_Initialize(Recovered_TimedValuePool* self) {
    Recovered_TimedValueEntry* entry;
    Recovered_TimedValueEntry** active;
    s32 i;
    self->unk_1218 = 0;
    self->count = 0;
    self->unk_1214 = 0;
    active = self->active;
    entry = self->entries;
    for (i = 127; i >= 0; --i) {
        entry->value = D_00443230;
        entry->unk_10 = 0.0f;
        entry->remaining = -1.0f;
        *active = NULL;
        ++entry;
        ++active;
    }
    for (i = 3; i >= 0; --i) { self->actions[i] = NULL; }
}
s32 TimedValuePool_SetActions(Recovered_TimedValuePool* self, Recovered_TimedValueAction** actions, u16 count, u32 value) {
    Recovered_TimedValueAction** destination = self->actions;
    if (count != 0) {
        u32 remaining = count;
        do {
            *destination = *actions;
            --remaining;
            ++actions;
            ++destination;
        } while (remaining != 0);
    }
    self->unk_1218 = count;
    self->unk_1214 = value;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282100", func_002822C8);
void TimedValuePool_Sort(Recovered_TimedValuePool* self) {
    s32 index;
    for (index = 1; index < self->count; ++index) {
        Recovered_TimedValueEntry* entry = self->active[index];
        s32 insertion = index;
        do {
            Recovered_TimedValueEntry* previous = self->active[insertion - 1];
            // The positive <= test also preserves the native behavior for NaN keys.
            if (previous->unk_10 <= entry->unk_10) break;
            self->active[insertion] = previous;
            --insertion;
        } while (insertion > 0);
        self->active[insertion] = entry;
    }
}
