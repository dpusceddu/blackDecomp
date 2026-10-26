#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/timed_value_pool.h"
#include "game/sound_bank_load.h"

extern u128 D_00443230;
extern Recovered_SharedBankStream D_00443240;
extern RwaStream* func_00313BF0(void*);
extern void func_0027FBC0(Recovered_SoundBankLoad*);
extern s32 func_002828A8(Recovered_SoundBankLoad*, const char*, RwaStream*, u32, u32, u32, u32, void*);

s32 TimedValuePool_Reset(Recovered_TimedValuePool* self) {
    s32 i;
    TimedValuePool_Clear(self);
    for (i = 3; i >= 0; --i) { self->actions[i] = NULL; }
    self->unk_1218 = 0;
    return 1;
}

#ifdef NON_MATCHING
static inline s32 TimedValueEntry_IsActive(f32 remaining) {
    s32 result = 0;
    if (remaining >= 0.0f) { result = 1; }
    return result;
}

// Unmatched: three loop-setup instructions are scheduled in a different order.
s32 TimedValuePool_Add(Recovered_TimedValuePool* self, u128 value, f32 duration) {
    s32 freeIndex = -1;
    f32* remaining = &self->entries[0].remaining;
    Recovered_TimedValueEntry* entry;
    s16 i;
    for (i = 0; i < 128; ++i, remaining = (f32*)((u8*)remaining + sizeof(Recovered_TimedValueEntry))) {
        if (!(u8)TimedValueEntry_IsActive(*remaining)) {
            freeIndex = i;
            break;
        }
    }
    entry = (Recovered_TimedValueEntry*)(freeIndex * sizeof(Recovered_TimedValueEntry) + (u32)self->entries);
    entry->value = value;
    entry->remaining = duration;
    entry->unk_10 = 0;
    self->active[self->count] = entry;
    ++self->count;
    return freeIndex;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282628", func_00282678);
#endif

void TimedValuePool_Clear(Recovered_TimedValuePool* self) {
    Recovered_TimedValueAction** action = self->actions;
    Recovered_TimedValueEntry* entry;
    Recovered_TimedValueEntry** active;
    s32 i;
    for (i = 3; i >= 0; --i) {
        Recovered_TimedValueAction* current = *action;
        if (current) {
            Recovered_TimedValueActionMethods* methods = current->methods;
            void* receiver = (u8*)current + methods->adjustment;
            methods->call(receiver);
        }
        ++action;
    }
    active = self->active;
    entry = self->entries;
    for (i = 127; i >= 0; --i) {
        entry->value = D_00443230;
        entry->unk_10 = 0;
        entry->remaining = -1.0f;
        *active = NULL;
        ++entry;
        ++active;
    }
    self->count = 0;
}

s32 SoundBankLoad_Initialize(Recovered_SoundBankLoad* self) {
    if (!D_00443240.initialized) {
        D_00443240.stream = func_00313BF0(NULL);
        D_00443240.initialized = 1;
    }
    func_0027FBC0(self);
    self->buffer = NULL;
    self->bank = NULL;
    self->state = 1;
    self->loaded = 0;
    return 1;
}

s32 SoundBankLoad_Poll(Recovered_SoundBankLoad* self, const char* name, u32 arg2, u32 arg3, u32 data, u32 dataSize,
                       void* context) {
    s32 result;
    if (self->loaded) {
        result = 1;
    } else {
        result = func_002828A8(self, name, D_00443240.stream, arg2, arg3, data, dataSize, context);
    }
    return result;
}
