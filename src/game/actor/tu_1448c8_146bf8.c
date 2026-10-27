#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/actor/entry_counts.h"
#include "game/effects/asset.h"

extern s32 func_00165BC8();

void func_00146BF8(void) {
    func_00165BC8();
}

#ifdef NON_MATCHING
extern BkActorAssetRecordPS2* func_001AFD80(Recovered_ActorCountEntry*, Recovered_ActorCountSource*);
// Unmatched: two independent zero initializations are reversed.
s32 func_00146C18(Recovered_ActorCountView* self) {
    s32 i;
    s32 offset;
    s32 result;
    u16 flags;
    BkActorAssetRecordPS2* record;
    result = 1;
    if (M2C_FIELD(self, u64*, 0) != 0x90CDAAC55D416000UL) {
        if (self->slotCount) {
            offset = 0;
            i = 0;
            for (;;) {
                record = func_001AFD80((Recovered_ActorCountEntry*)((u8*)self->entries + offset), self->source);
                if (record) {
                    flags = record->flags5a;
                    if (flags & 0x800) {
                        result = 1;
                        if (!(flags & 1)) {
                            if (flags & 2) return 1;
                            goto failure;
                        }
                        return result;
                    }
                }
                ++i;
                offset += 0xC;
                if (i >= self->slotCount) break;
            }
        }
    failure:
        result = 0;
        return result;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_146bf8", func_00146C18);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_146bf8", func_00146CE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_146bf8", func_001471E0);

// Partial contact-result view; other fields and class identity are UNVERIFIED.
typedef struct Recovered_ActorQueryResult {
    u8 unk_000[0x2E0];
    float unk_2E0;
    u8 unk_2E4[0x13C];
} Recovered_ActorQueryResult;

extern void* D_0040F4D0;
extern s32 func_0033B688(void*);
extern s32 func_00263E80(void*, s32, s32, s16);

s32 func_001475F0(Recovered_ActorCountView* self, s32 arg1, s32 arg2, s32 arg3) {
    Recovered_ActorQueryResult* results =
        M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5A94), Recovered_ActorQueryResult**, 0x30);
    if (M2C_FIELD(self, void**, 0xB8)) {
        struct {
            void* object;
            void* matrix;
        } input;
        void* query;
        s32 count;
        s32 i;
        input.object = M2C_FIELD(self, void**, 0xB8);
        input.matrix = (u8*)self + 0x70;
        query = M2C_FIELD(D_0040F4D0, void**, 0x5A94);
        M2C_FIELD(query, s32*, 0x38) = arg1;
        M2C_FIELD(query, void**, 0x4) = &input.matrix;
        M2C_FIELD(query, s32*, 0x8) = 1;
        M2C_FIELD(query, s32*, 0x3C) = arg3;
        M2C_FIELD(query, void**, 0x0) = &input.object;
        M2C_FIELD(query, s32*, 0xC) = 0;
        M2C_FIELD(query, s32*, 0x1C) = 0;
        M2C_FIELD(query, f32*, 0x14) = 0.0f;
        M2C_FIELD(query, s32*, 0x10) = 0;
        count = func_0033B688(M2C_FIELD(D_0040F4D0, void**, 0x5A94));
        for (i = 0; i < count; ++i) {
            if (results[i].unk_2E0 < 0.0f) goto found;
        }
        goto not_found;
    }
    return func_00263E80(M2C_FIELD(self, void**, 0x1B8), arg1, arg3, M2C_FIELD(self, s16*, 0x1E8));
found:
    return 1;
not_found:
    return 0;
}
