#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "game/actor_records.h"

extern s32 func_00179258();
extern s32 D_0040F4D4;
extern s32 func_00178F18();
extern s32 func_00176310();
extern s32 func_00173610();

extern s32 func_00188F10(void*);
extern void* func_00188F80(void*);
extern u8 func_00178FD8(void*);
extern s32 func_00189BF8(void*, s32);
extern s32 func_00189490(s32);
extern void* D_0040F4D0;

static inline Recovered_ActorRecord* ActorRecordAt(Recovered_ActorRecords* self, s32 index) {
    return (Recovered_ActorRecord*)((index * 0x60) + (u32)self);
}

#ifdef NON_MATCHING
// Unmatched: current-index and stride register allocation differ.
s32 func_001891C0(Recovered_ActorRecords* self) {
    s32 result;
    if (func_00188F10(self)) {
        result = ActorRecordAt(self, self->current)->unk_06;
    } else {
        result = 0;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1891c0", func_001891C0);
#endif

#ifdef NON_MATCHING
// Unmatched: current-index and stride register allocation differ.
s32 func_00189208(Recovered_ActorRecords* self) {
    s32 result;
    if (func_00188F10(self)) {
        result = ActorRecordAt(self, self->current)->unk_05;
    } else {
        result = 0;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1891c0", func_00189208);
#endif

#ifdef NON_MATCHING
// Unmatched: record cursor and return-block layout differ.
s32 func_00189250(Recovered_ActorRecords* self, s32 id) {
    s32 cursor;
    s32 end;
    if (!func_00189BF8(self, id)) return 0;
    cursor = (s32)self;
    end = cursor + 0x120;
    do {
        Recovered_ActorRecord* record = (Recovered_ActorRecord*)cursor;
        s32 found = record->id == id;
        cursor += sizeof(Recovered_ActorRecord);
        if (found) return record->unk_05;
    } while (cursor < end);
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1891c0", func_00189250);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1891c0", func_001892C0);
u8 ActorRecords_CurrentKindAllowed(Recovered_ActorRecords* self) {
    u8 result;
    if (func_00188F10(self)) {
        result = func_00178FD8(func_00188F80(self));
    } else {
        result = 0;
    }
    return result;
}

f32 ActorRecords_ElapsedTime(Recovered_ActorRecords* self) {
    if (M2C_FIELD(self->owner, u8*, 0xD27) && func_00189208(self) &&
        !func_001891C0(self) && !func_00189490((s32)self)) {
        return 0.0f;
    }
    return M2C_FIELD(D_0040F4D0, f32*, 0x20) -
           ((Recovered_ActorRecord*)(self->current * 0x60 + (s32)self))->startTime;
}

void * func_001893A0(void *arg0) {
    return (M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0 + 0x20;
}

s32 func_001893B8(s32 arg0, s32 arg1) {
    s32 temp_21;
    s32 temp_2;
    s32 temp_5;
    s32 var_17;
    s32 var_20;

    var_20 = 0;
    if (arg1 != 0) {
        var_17 = arg0;
        temp_21 = var_17 + 0x120;
        do {
            temp_5 = M2C_FIELD(var_17, s32 *, 0);
            if (temp_5 != -1) {
                temp_2 = func_00179258(D_0040F4D4 + 0xFA8, temp_5);
                if ((func_00178F18(temp_2) != 0) && (func_00176310(D_0040F4D4 + 0xFA0, M2C_FIELD(temp_2, s32 *, 8), arg1) != 0)) {
                    var_20 = (var_20 + 1) & 0xFF;
                }
            }
            var_17 += 0x60;
        } while (var_17 < temp_21);
    }
    return var_20;
}

void * func_00189478(void *arg0) {
    return (M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0 + 0x30;
}

s32 func_00189490(s32 arg0) {
    return (func_00173610((M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0 + 0x50) ^ 1) & 0xFF;
}
