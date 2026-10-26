#include "include_asm.h"
#include "game/actor_slots.h"
#ifdef NON_MATCHING
// Unmatched: boolean normalization and result-register copy differ.
extern "C" s32 ActorSlot_IsState0Kind2(Recovered_ActorSlot* entry) {
    return entry->state == 0 && entry->actor->unk_C4 == 2;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_178f18_178f28", func_00178F28);
#endif
