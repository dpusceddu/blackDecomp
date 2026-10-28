#include "include_asm.h"
#include "game/actor/entry_counts.h"
#include "game/effects/asset.h"
extern BkActorAssetRecordPS2* func_001AFD80(Recovered_ActorCountEntry*, Recovered_ActorCountSource*);
extern s32 func_0026F190(void*, s128);
extern u8 D_0040D9B1;
s32 func_00147140(Recovered_ActorCountView* self, s32 index, void* segment) {
    BkActorAssetRecordPS2* record = func_001AFD80(&self->entries[index], self->source);
    if (!D_0040D9B1 || self->indices[index] == -1) return 1;
    if (record) return func_0026F190(segment, M2C_FIELD(record, s128*, 0xB0)) != 0;
    return 0;
}
