#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/actor_slots.h"

/* UNVERIFIED: partial layouts inferred from the accesses below. */
typedef struct Recovered_MovementEventActor {
    u8 pad[0x380];
    s32 index;
} Recovered_MovementEventActor;
typedef struct Recovered_MovementEventOwner {
    u8 pad[0x7C];
    Recovered_MovementEventActor *actor;
    u8 pad2[0xC90];
    u8 data[1];
} Recovered_MovementEventOwner;
typedef struct Recovered_MovementEventState {
    struct Recovered_MovementEventResource *eventResource;
    Recovered_MovementEventOwner *owner;
    u8 pad2[0xC];
    s32 choices[5];
    s32 current;
    u64 *list;
    u8 pad3[4];
    f32 time;
    struct Recovered_MovementModeResource *resource;
    u8 count;
    u8 pad4[3];
    u8 flag;
} Recovered_MovementEventState;
typedef struct Recovered_MovementEvent {
    u8 pad[0x24];
    s32 type;
    u8 pad2[0x3C];
    u32 mask;
} Recovered_MovementEvent;

extern s32 func_0018E488();
extern u8 *D_0040F4D0;
extern u8 *D_0040F4D4;
extern void func_00190380(void *, s32, u8);
extern s32 func_0018D698(s32, M2C_UNK);
extern s32 func_00185C38();
extern s32 func_001897E8();
extern s32 func_00180A00(s32);
extern s32 func_0018E4C0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18f7c8", func_0018F7C8);

void func_0018FB40(void *arg0) {
    func_0018E488();
    func_00190380(arg0, M2C_FIELD(arg0, s32 *, 0x2C), M2C_FIELD(arg0, u8 *, 0x3C));
    func_0018D698(M2C_FIELD(arg0, s32 *, 4) + 0xD10, 0);
}

s32 func_0018FB88(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 temp_7;
    s32 var_2;
    void *temp_6;

    temp_6 = M2C_FIELD(arg0, void **, 4);
    temp_5 = M2C_FIELD(arg1, s32 *, 0x380);
    temp_7 = 1 << temp_5;
    var_2 = M2C_FIELD(M2C_FIELD(temp_6, void **, 0x7C), s32 *, 0x3A4);
    if (M2C_FIELD(arg1, s32 *, 0x3A4) != var_2) {
        var_2 = M2C_FIELD(arg1, s32 *, 0x38C);
        if (var_2 == 0) {
            var_2 = M2C_FIELD(temp_6, s32 *, 0x274) & temp_7;
            if (var_2 != temp_7) {
                var_2 = func_00185C38((s32) (temp_6 + 0x6F0), temp_5);
                if (var_2 != 0) {
                    var_2 = func_001897E8((s32) (M2C_FIELD(arg0, void **, 4) + 0x150), M2C_FIELD(arg1, s32 *, 0x380), 0);
                }
            }
        }
    }
    return var_2;
}

#ifdef NON_MATCHING
/* UNVERIFIED: partial views of the manager and its movement slots. */
typedef struct Recovered_MovementBatchSlot {
    u8 pad[0x78];
    u8 active;
    u8 pad2[3];
    void *actor;
    u8 pad3[0x1F50];
} Recovered_MovementBatchSlot;
typedef struct Recovered_MovementBatchManager {
    u8 pad[0x2B00];
    Recovered_MovementBatchSlot slots[16];
} Recovered_MovementBatchManager;
typedef struct Recovered_MovementBatchState {
    u8 pad[4];
    Recovered_MovementBatchSlot *owner;
} Recovered_MovementBatchState;

// Unmatched: indexed manager address adds its operands in the opposite order.
void func_0018FC18(Recovered_MovementBatchState *self) {
    int i;
    func_0018FB88((s32)self, (s32)(D_0040F4D0 + 0x30));
    for (i = 0; i < 16; i++) {
        if (((Recovered_MovementBatchManager *)D_0040F4D4)->slots[i].active &&
            &((Recovered_MovementBatchManager *)D_0040F4D4)->slots[i] != self->owner)
            func_0018FB88((s32)self, (s32)((Recovered_MovementBatchManager *)D_0040F4D4)->slots[i].actor);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18f7c8", func_0018FC18);
#endif
/* UNVERIFIED: partial configuration view for the actor key lookup and event modes. */
typedef struct Recovered_MovementEventConfig {
    u8 pad[0x28];
    s32 values[5];
    u8 pad2[4];
    u64 *keys;
    u8 pad3[0x3A];
    u8 counts[5];
    u8 pad4;
    u8 count;
} Recovered_MovementEventConfig;
typedef struct Recovered_MovementEventResource {
    u8 pad[0x28];
    Recovered_MovementEventConfig *config;
} Recovered_MovementEventResource;

s32 func_0018FCB8(Recovered_MovementEventState *self, s32 index) {
    Recovered_ActorSlot entry = *ActorSlotTable_GetEntry((Recovered_ActorSlotTable *)(D_0040F4D4 + 0xFA8), index);
    Recovered_MovementEventConfig *config = self->eventResource->config;
    if (ActorSlot_IsState0(&entry)) {
        if (config->count) {
            s32 found = 0;
            int i;
            for (i = 0; i < config->count; i++) {
                if (config->keys[i] == *(u64 *)entry.actor) {
                    found = 1;
                    break;
                }
            }
            if (!found) return 0;
        }
    }
    return 1;
}
#ifdef NON_MATCHING
#include "game/ai/actor_slot_values.h"
/* UNVERIFIED: only the target pointer used by this predicate is described. */
typedef struct Recovered_MovementTargetState {
    u8 pad[0x28];
    void *target;
} Recovered_MovementTargetState;
extern s64 Allowed__Q28Graphics12MovementCorel(Recovered_MovementTargetState *, s64);
extern s32 func_0018E680(Recovered_MovementTargetState *, s128, void *);

// Unmatched: return joins and branch placement differ.
s32 func_0018FD80(Recovered_MovementTargetState *self, s64 index) {
    Recovered_ActorSlot entry;
    if (Allowed__Q28Graphics12MovementCorel(self, index)) {
        if (index != -1) {
            entry = *ActorSlotTable_GetEntry((Recovered_ActorSlotTable *)(D_0040F4D4 + 0xFA8), index);
            if (ActorSlot_IsState0(&entry)) {
                if (self->target) {
                    if (!func_0018E680(self, *func_00178D30(&entry), self->target)) return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18f7c8", func_0018FD80);
#endif

u8 func_0018FE28(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x40);
}

void func_0018FE30(void *arg0) {
    func_00180A00(M2C_FIELD(arg0, s32 *, 4) + 0xB30);
}

s32 func_0018FE50(void) {
    return 1;
}

extern void func_0016ABA8(void *, s32, u8, void *);

s32 func_0018FE58(Recovered_MovementEventState *self, u32 mode) {
    Recovered_MovementEventConfig *config = self->eventResource->config;
    switch (mode) {
    case 0:
        func_0016ABA8((u8 *)self->owner + 0x1F90, config->values[0], config->counts[0], self->owner->actor);
        return 1;
    case 1:
        func_0016ABA8((u8 *)self->owner + 0x1F90, config->values[1], config->counts[1], self->owner->actor);
        return 1;
    case 2:
        func_0016ABA8((u8 *)self->owner + 0x1F90, config->values[2], config->counts[2], self->owner->actor);
        return 1;
    case 3:
        func_0016ABA8((u8 *)self->owner + 0x1F90, config->values[4], config->counts[4], self->owner->actor);
        self->time = M2C_FIELD(D_0040F4D0, f32 *, 0x20);
        return 1;
    case 5:
        func_0016ABA8((u8 *)self->owner + 0x1F90, config->values[3], config->counts[3], self->owner->actor);
        return 1;
    default:
        return 0;
    }
}
extern Recovered_MovementEventOwner *func_00177E98(Recovered_MovementEvent *);

f32 func_0018FF38(Recovered_MovementEventState *self, Recovered_MovementEvent *event) {
    if (event->type == 3 && (event->mask & (1U << self->owner->actor->index))) {
        if (func_00177E98(event) != self->owner) return 1.0f;
        return 0.5f;
    }
    return 0.0f;
}

s32 func_0018FFC0(void *arg0, s32 *arg1) {
    void *temp_3;

    func_0018E4C0();
    if (*arg1 == 2) {
        temp_3 = M2C_FIELD(arg0, void **, 0x10);
        M2C_FIELD(temp_3, M2C_UNK (**)(void *, M2C_UNK), 0x84)(arg0 + M2C_FIELD(temp_3, s16 *, 0x80), 3);
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18f7c8", func_00190020);

const char D_003F5768[] = "Message to Level Designer :\n"
                          "Never give a teammate a firesector with multiple volumes!\n"
                          "Only the first will be used\n";
/* UNVERIFIED: partial views of the mode configuration and movement state. */
typedef struct Recovered_MovementModeConfig {
    u8 pad[0x58];
    u64 *lists[5];
    u8 pad2[0x1E];
    u8 counts[5];
} Recovered_MovementModeConfig;
typedef struct Recovered_MovementModeResource {
    u8 pad[0x28];
    Recovered_MovementModeConfig *config;
} Recovered_MovementModeResource;
extern void func_001902D0(Recovered_MovementEventState *, u64 *, u8);

void func_001901E0(Recovered_MovementEventState *self, u8 mode) {
    Recovered_MovementModeConfig *config = self->resource->config;
    func_00190380(self, (s32)self->list, self->count);
    switch (mode) {
    case 0:
        self->list = config->lists[0];
        self->count = config->counts[0];
        break;
    case 1:
        self->list = config->lists[1];
        self->count = config->counts[1];
        break;
    case 2:
        self->list = config->lists[2];
        self->count = config->counts[2];
        break;
    case 3:
        self->list = config->lists[3];
        self->count = config->counts[3];
        break;
    case 4:
        self->list = config->lists[4];
        self->count = config->counts[4];
        break;
    }
    func_001902D0(self, self->list, self->count);
    self->current = self->choices[mode];
    func_0018D698((s32)self->owner->data, self->current);
}
extern void *D_0040F4F4;
extern void *func_00169920(void *, u64);
extern void func_00177EE8(void *, s32, s32);

void func_001902D0(Recovered_MovementEventState *self, u64 *values, u8 count) {
    u8 found = 0;
    s32 index = self->owner->actor->index;
    if (count) {
        u64 *cursor = values;
        int remaining = count;
        do {
            u8 *item = func_00169920(D_0040F4F4, *cursor);
            if (item) {
                func_00177EE8(item + 0x20, index, 1);
                found++;
            }
            remaining--;
            cursor++;
        } while (remaining);
    }
    if (found >= 2) self->flag = 1;
}
void func_00190380(void *obj, s32 values, u8 count) {
    Recovered_MovementEventState *self = (Recovered_MovementEventState *)obj;
    s32 index = self->owner->actor->index;
    if (count) {
        u64 *cursor = (u64 *)values;
        int remaining = count;
        do {
            u8 *item = func_00169920(D_0040F4F4, *cursor);
            if (item && index != -1) func_00177EE8(item + 0x20, index, 0);
            remaining--;
            cursor++;
        } while (remaining);
    }
    self->flag = 0;
}
