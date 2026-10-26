#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/timed_flag_queue.h"

/* The returned end cursor is retained; its caller contract is unknown. */
void* TimedFlagQueue_Reset(Recovered_TimedFlagQueue* self) {
    s32 remaining = 299;
    Recovered_TimedFlagEntry* entry = self->entries;
    do {
        entry->item = NULL;
        remaining--;
        entry->flags = 0;
        entry++;
    } while (remaining >= 0);
    self->head = 0;
    self->tail = 0;
    self->count = 0;
    return entry;
}

#ifdef NON_MATCHING
// Unmatched: flag-rejection branch and early epilogue restoration differ.
s32 TimedFlagQueue_AddFlags(Recovered_TimedFlagQueue* self, Recovered_TimedFlagItem* item, u32 flags) {
    Recovered_TimedFlagEntry* entry;
    if (!TimedFlagItem_HasExpired(item)) {
        if (!(item->previousFlags & flags)) goto enqueue;
        return 0;
    }
    TimedFlagItem_ClearPreviousFlags(item);
enqueue:
    entry = TimedFlagQueue_Find(self, item);
    if (entry == NULL) entry = TimedFlagQueue_Insert(self, item);
    if (entry == NULL) return 0;
    entry->flags |= flags;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_177148_1777d0", func_00177800);
#endif

Recovered_TimedFlagEntry* TimedFlagQueue_Insert(Recovered_TimedFlagQueue* self, Recovered_TimedFlagItem* item) {
    if (!TimedFlagQueue_IsFull(self)) {
        Recovered_TimedFlagEntry* entry = &self->entries[self->tail];
        s32 next = (self->tail + 1) % 300;
        self->count++;
        self->tail = next;
        /* Preserve the native wrap behavior, including the final allowed insert. */
        if (next == self->head) self->head = (next + 1) % 300;
        entry->item = item;
        entry->flags = 0;
        return entry;
    }
    return NULL;
}

Recovered_TimedFlagEntry* TimedFlagQueue_Pop(Recovered_TimedFlagQueue* self) {
    Recovered_TimedFlagEntry* entry = TimedFlagQueue_Peek(self);
    if (entry == NULL) return NULL;
    self->head = (self->head + 1) % 300;
    self->count--;
    return entry;
}

Recovered_TimedFlagEntry* TimedFlagQueue_Find(Recovered_TimedFlagQueue* self, Recovered_TimedFlagItem* item) {
    if (!TimedFlagQueue_IsEmpty(self)) {
        s32 remaining = self->count;
        s32 index = self->head;
        while (--remaining != -1) {
            Recovered_TimedFlagEntry* entry = &self->entries[index];
            if (entry->item == item) return entry;
            index = (index + 1) % 300;
        }
    }
    return NULL;
}
