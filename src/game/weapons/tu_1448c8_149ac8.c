#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/effects/asset.h"

extern s32 func_001B37C8();
extern s32 D_0040F4D8;
extern s32 func_00165AE0();
extern s32 func_00165BC8();
extern s32 func_00165B98();
extern void func_00169BF0();

/* Private partial views: matched accesses verify offsets, not original class identities or complete sizes. */
typedef struct ActionView {
    u64 id;
    u8 unk08[8];
    char* table;
    u32 unk14;
    void* data;
    u8 enabled;
    u8 unk1D[3];
    void* definition;
    s32 state;
    float remaining;
    s32 unk2C;
} ActionView;

typedef struct CounterDefinition {
    u8 unk00[8];
    u8 count;
    u8 repeat;
} CounterDefinition;
typedef struct CounterAction {
    u64 id;
    u8 unk08[8];
    char* table;
    u32 unk14;
    s32 count;
    CounterDefinition* definition;
} CounterAction;
typedef struct CountdownDefinition {
    u8 unk00[8];
    float duration;
} CountdownDefinition;
typedef struct CountdownAction {
    u64 id;
    u8 unk08[8];
    char* table;
    u32 unk14;
    u8 enabled;
    u8 unk19[3];
    float remaining;
    CountdownDefinition* definition;
} CountdownAction;
extern void func_00160E70(void*);
extern void func_00160EA0(void*);
extern void func_00160EF8(void*);
extern void func_00165AF8(void*);

#define ACTION_OFFSET(type, field) ((u32) & ((type*)0)->field)
typedef char ActionIdWidth[(sizeof(((ActionView*)0)->id) == 8) ? 1 : -1];
typedef char ActionTableOffset[(ACTION_OFFSET(ActionView, table) == 0x10) ? 1 : -1];
typedef char ActionDefinitionOffset[(ACTION_OFFSET(ActionView, definition) == 0x20) ? 1 : -1];
typedef char CounterDefinitionOffset[(ACTION_OFFSET(CounterAction, definition) == 0x1C) ? 1 : -1];
typedef char CountdownDefinitionOffset[(ACTION_OFFSET(CountdownAction, definition) == 0x20) ? 1 : -1];
#undef ACTION_OFFSET

typedef struct GroupMember {
    u8 unk00[0xEC0];
    u8 control;
} GroupMember;
typedef struct GroupView {
    u64 id;
    u8 unk08[0x10];
    const char* name;
    GroupMember* members[16];
    char sound[13];
    u8 count;
} GroupView;
extern void func_00165AF8(void*);
extern char* func_0035CBC0(char*, const char*);
extern void func_00181AD0(void*, s32);
typedef struct GlobalTime {
    u8 unk00[0x20];
    float time;
} GlobalTime;

typedef struct SoundManager {
    u8 unk00[4];
    void* player;
    u8 unk08[0x1C];
    void* channel;
} SoundManager;
typedef struct GameSound {
    u8 unk00[0x4BD8];
    SoundManager* sound;
} GameSound;
extern GameSound* D_0040F510;
extern void func_001E6058(void*, float, float, float);
extern void func_001E6088(void*);

typedef struct CommandWeapon {
    u8 unk00[0x118];
    BkActorAssetPS2* definition;
    u8 unk11C[0x84];
    BkActorTimerPS2* timers;
    u8 unk1A4[0x18];
    s32 unk1BC;
    s32 unk1C0;
} CommandWeapon;
extern s32 func_001AFDA8(BkActorTimerPS2*);
extern void* func_00147988(CommandWeapon*, s32);
extern void* func_0014DE58(void*, void*, BkActorAssetPS2*, s32, void*, s32, s32, s32);
typedef struct InventoryPool {
    u8 objects[0x3600];
    s32 firstTypes[32];
    s32 secondTypes[16];
    u8 unk36C0[0x40];
    u8 firstUsed[32];
    u8 secondUsed[16];
} InventoryPool;
typedef struct Definition {
    u8 unk00[0x48];
    s32* indices;
} Definition;
typedef struct WeaponRecord {
    u8 unk00[0x54];
    s32 kind;
    u16 flags58;
    u16 flags5A;
    u8 unk5C[4];
    u64 id;
    u8 unk68[0x68];
} WeaponRecord;
typedef struct WeaponDefinition {
    u8 unk00[0x48];
    WeaponRecord* records;
    u8 unk4C[0xC];
    s32* values;
    u8 unk5C[8];
    s32* indices;
    u8 unk68[2];
    u8 kind;
} WeaponDefinition;
typedef struct WeaponView {
    u8 unk00[0x118];
    WeaponDefinition* definition;
    void* owner;
    void* state;
    u8 unk124[0x80];
    s32* indices;
    u8 unk1A8[0x4D];
    u8 count;
} WeaponView;
typedef struct BindingDefinition {
    u8 unk00[0x10];
    u128 value;
} BindingDefinition;
typedef struct BindingAction {
    u8 unk00[0x20];
    u8 child[0x70];
    void* binding;
    BindingDefinition* definition;
} BindingAction;
extern void* D_0040F4D4;
extern void* func_0017B8A8(void*, u128);
extern void func_00177C78(void*, void*);
typedef struct RegionRecord {
    u64 id;
    u8 unk08[0xD2];
    u8 enabled;
    u8 unkDB[0x15];
} RegionRecord;
typedef struct RegionHeader {
    u8 unk00[0x90];
    u16 count;
} RegionHeader;
typedef struct Region {
    u8 unk00[0xC];
    RegionHeader* header;
    u32 unk10;
    RegionRecord* records;
} Region;
typedef struct WorldClock {
    u8 unk00[0x5AB0];
    s32 regionIndex;
} WorldClock;

extern Region* func_0012BD98(WorldClock*, s32);
typedef struct RegionDefinition {
    u64* ids;
    u8 count;
    u8 unk05[3];
    u8 enabled;
} RegionDefinition;
typedef struct RegionAction {
    u8 unk00[0x20];
    RegionDefinition* definition;
} RegionAction;

typedef struct Resource {
    u8 unk00[0x118];
    void* definition;
    void* owner;
    void* link;
    u8 unk124[0xC];
    s32 index;
    u8 unk134[9];
    u8 active;
    u8 unk13E[0x92];
    u8 used;
    u8 unk1D1[0xF];
} Resource;
typedef struct ResourcePool {
    Resource* items;
    s32 count;
} ResourcePool;
typedef struct ResourceRef {
    u8 unk00[0x18];
    Resource* resource;
    u8 unk1C[0x114];
    s32 index;
} ResourceRef;
typedef struct ResourceGroups {
    ResourceRef** first;
    ResourceRef** second;
    s32 firstCount;
    s32 secondCount;
    s32 nextIndex;
} ResourceGroups;
extern void* D_0040F4D0;
extern u8 D_0040F0F0[];
extern void func_00129240(void*, Resource*, s32);
extern void func_001507B8(Resource*);
extern s32 func_00107BC0(void*, void*);
typedef char ResourceStride[(sizeof(Resource) == 0x1E0) ? 1 : -1];
typedef struct EffectAction {
    u8 unk00[0x20];
    u8 child[0x14];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} EffectAction;
extern void func_00160E70(void*);
extern void func_00280FE0(void*, void*);
typedef struct ClockView {
    u8 unk00[0x20];
    float time;
} ClockView;
extern ClockView* D_0040F0E0;
typedef struct TimedDefinition {
    u8 unk00[0x28];
    float duration;
    float x, y, z;
} TimedDefinition;
typedef struct TimedAction {
    u8 unk00[0x20];
    TimedDefinition* definition;
    s32 state;
    float deadline;
} TimedAction;

extern s32 func_00165BC8(void *, s32);
extern s32 func_00169EB8();

void func_00149AC8(void *arg0) {
    s32 var_16;
    u16 *temp_3;

    var_16 = 0;
    if (M2C_FIELD(arg0, u8 *, 0x1F6) != 0) {
        do {
            temp_3 = (var_16 * 2) + M2C_FIELD(arg0, s32 *, 0x1B0);
            if (*temp_3 != 0xFFFF) {
                func_001B37C8(D_0040F4D8 + 0x33C40, *temp_3);
            }
            var_16 += 1;
        } while (var_16 < (s32) M2C_FIELD(arg0, u8 *, 0x1F6));
    }
}

s32 func_00149B60(WeaponView* self, s32 index) {
    s32 value = self->indices[index];
    if (value == -1) return self->count != 1;
    {
        s32 i;
        for (i = 0; i < self->count; i++) {
            s32 candidate = self->indices[i];
            if (candidate != -1 && self->definition->values[candidate] == value) return 1;
        }
    }
    return 0;
}

void func_00149BE8(s32 arg0, s32 arg1, s32 arg2)
{
  u8 *temp_7;
  s32 new_var;
  u8 var_2;
  arg1 = arg1;
  arg1 = arg1 * 2;
  temp_7 = arg1 + (M2C_FIELD(arg0, s32 *, 0x1AC));
  var_2 = *temp_7;
  new_var = M2C_FIELD(arg0, s32 *, 0x1AC);
  if (var_2 == 0)
  {
    *temp_7 = 1;
    ;
    *((s8 *) ((arg1 + (M2C_FIELD(arg0, s32 *, 0x1AC))) + 1)) = (s8) arg2;
  }
  return (s32) (arg1 + new_var);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00149C18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00149CA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00149D58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A438);

s32 func_0014A560(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A6A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014BD58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014CE68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DA80);
void func_0014DB90(ResourcePool* self) {
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (self->items[i].used) func_00129240(D_0040F4D0, &self->items[i], 0);
    }
}
void func_0014DC18(ResourcePool* self) {
    s32 i;
    for (i = 0; i < self->count; i++) func_001507B8(&self->items[i]);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DC78);
void* func_0014DD98(void* pool, void* arg, CommandWeapon* weapon, s32 index, s32 kind) {
    BkActorAssetPS2* definition = weapon->definition;
    s32 record = func_001AFDA8(&weapon->timers[index]);
    void* matrix;
    if (record != -1) {
        matrix = func_00147988(weapon, index);
        return func_0014DE58(pool, arg, definition, record, matrix, weapon->unk1BC, weapon->unk1C0, kind);
    }
    return NULL;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DE58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DF68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014E018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014EC10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014EC90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014F888);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014FDA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014FEE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001507E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00152A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00153448);
void func_001534A8(ResourceGroups* self, ResourceRef** items) {
    s32 i;
    if (items) {
        if (items == self->first) {
            for (i = 0; i < self->firstCount; i++) func_00129240(D_0040F4D0, self->first[i]->resource, 1);
            self->first = NULL;
            self->firstCount = 0;
        } else {
            for (i = 0; i < self->secondCount; i++) func_00129240(D_0040F4D0, self->second[i]->resource, 1);
            self->second = NULL;
            self->secondCount = 0;
        }
    }
}
s32 func_001550C0(u16* counts, s32 index, u8 amount) {
    counts = (u16*)((s8*)counts + index * 2);
    if (*counts < amount) return 0;
    *counts -= amount;
    return 1;
}
s32 func_001550F0(u16* counts, s32 index) {
    counts = (u16*)((s8*)counts + index * 2);
    if (*counts) {
        --*counts;
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155B08);
void func_00155DC8(InventoryPool* self) {
    s8 i;
    for (i = 0; i < 32; i++) {
        self->firstUsed[i] = 0;
        self->firstTypes[i] = 0;
    }
    for (i = 0; i < 16; i++) {
        self->secondUsed[i] = 0;
        self->secondTypes[i] = 0;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155E48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00156110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00158E88);
void func_00161DF0(RegionAction* self) {
    s32 i;
    for (i = 0; i < self->definition->count; i++) {
        Region* region = func_0012BD98(D_0040F4D0, ((WorldClock*)D_0040F4D0)->regionIndex);
        u64 id = self->definition->ids[i];
        s32 j;
        for (j = 0; j < region->header->count; j++) {
            RegionRecord* record = &region->records[(u16)j];
            if (record->id == id) record->enabled = self->definition->enabled != 0;
        }
    }
}
void func_00162160(ActionView* self, s32 arg) {
    func_00160E70(self);
    self->definition = NULL;
    self->state = 0;
    self->unk2C = 0;
    func_00165BC8(self, arg);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001621A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162600);
s32 func_001626D0(BindingAction* self) {
    u128 value = self->definition->value;
    if (self->binding) return 0;
    self->binding = func_0017B8A8((s8*)D_0040F4D4 + 0x1290, value);
    if (self->binding) {
        func_00177C78(self->binding, self->child);
        return 1;
    }
    return 0;
}
s32 func_00162758(ActionView* self, u64 id, void* definition) {
    func_00160EA0(self);
    self->definition = definition;
    self->id = id;
    self->data = definition;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001627D0);
s32 func_001628E8(ActionView* self, u64 id, void* definition) {
    func_00160EA0(self);
    self->definition = definition;
    self->id = id;
    self->data = definition;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162960);
s32 func_00162A60(ActionView* self, u64 id, void* definition, void* arg) {
    func_00160EA0(self);
    self->state = (s32)definition;
    self->id = id;
    self->definition = arg;
    self->data = definition;
    return 1;
}
s32 func_00162D10(ActionView* self, u64 id, void* definition, void* arg) {
    func_00160EA0(self);
    self->state = (s32)definition;
    self->id = id;
    self->definition = arg;
    self->data = definition;
    return 1;
}
s32 func_00162F28(ActionView* self, u64 id, void* definition, void* arg) {
    func_00160EA0(self);
    self->state = (s32)definition;
    self->id = id;
    self->definition = arg;
    self->data = definition;
    return 1;
}
s32 func_001630E8(ActionView* self, u64 id, void* definition) {
    func_00160EA0(self);
    self->id = id;
    self->definition = definition;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163158);
s32 func_001631B0(ActionView* self, u64 id, void* definition) {
    func_00160EA0(self);
    self->id = id;
    self->definition = definition;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001634D8);
void func_001635D0(EffectAction* self, s32 arg) {
    func_00160E70(self);
    self->unk38 = 0;
    self->unk3C = 0;
    self->unk34 = 0;
    func_00280FE0(self->child, NULL);
    func_00165BC8(self, arg);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163628);
void func_00163AB8(ActionView* self, s32 arg) {
    func_00160E70(self);
    self->state = 0;
    func_00165BC8(self, arg);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163AF8);
void func_00163B50(TimedAction* self) {
    GlobalTime* clock = (GlobalTime*)((s8*)D_0040F0E0 + 0x20120);
    float time = clock->time;
    switch (self->state) {
        case 1: break;
        case 2: {
            GameSound* game = (GameSound*)((s8*)D_0040F510 + 0x8000);
            func_001E6058(game->sound->player, self->definition->x, self->definition->y, self->definition->z);
            self->state = 3;
        }
        case 3:
            if (time < self->deadline) return;
            {
                GameSound* game = (GameSound*)((s8*)D_0040F510 + 0x8000);
                func_001E6088(game->sound->player);
                self->state = 1;
            }
            break;
    }
}
void func_00163C58(ActionView* self) {
    func_00160EF8(self);
    self->definition = NULL;
    self->state = 5;
    self->data = NULL;
}
void func_00163C90(TimedAction* self) {
    ClockView* clock = (ClockView*)((s8*)D_0040F0E0 + 0x20120);
    float time = clock->time;
    float duration = self->definition->duration;
    self->state = 2;
    self->deadline = time + duration;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163DB8);
s32 func_00163E08(GroupView* self, u64 id, const char* name) {
    s32 i;
    func_00165AF8(self);
    self->id = id;
    self->name = name;
    for (i = 15; i >= 0; i--) self->members[i] = NULL;
    self->count = 0;
    func_0035CBC0(self->sound, self->name);
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163F30);
void func_00163FD0(GroupView* self, GroupMember* member) {
    s32 removed = 0;
    s32 i;
    for (i = 0; i < 16; i++) {
        if (self->members[i] == member) {
            self->members[i] = NULL;
            removed = 1;
            self->count--;
            break;
        }
    }
    if (removed) {
        if (self->count < 2) func_0035CBC0(self->sound, self->name);
        func_00164078(self);
    }
}
void func_00164078(GroupView* self) {
    GroupMember** cursor = self->members;
    s32 i = 15;
    do {
        GroupMember* member = *cursor++;
        if (member) func_00181AD0(&member->control, 14);
    } while (--i >= 0);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001640D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001641A8);
typedef struct GroupAction {
    u8 unk00[0x69];
    u8 count;
} GroupAction;

s32 func_00164238(GroupAction* self) {
    u8 single = 1;
    return self->count > single;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164F50);

void func_001650B8(void *arg0, s32 arg1) {
    func_00165AE0();
    func_00165BC8(arg0, arg1);
}

s32 func_001650F8(CounterAction* self, u64 id, CounterDefinition* definition) {
    func_00165AF8(self);
    self->id = id;
    self->definition = definition;
    self->count = 0;
    return 1;
}

s32 func_00165148(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00165168);
void func_00165170(CounterAction* self) {
    if (++self->count == self->definition->count) {
        char* table = self->table;
        (*(void (**)(void*))(table + 0x14))((char*)self + *(s16*)(table + 0x10));
        if (self->definition->repeat) self->count = 0;
    }
}
void func_001651D0(CountdownAction* self, s32 arg) {
    func_00165AE0(self);
    self->enabled = 0;
    func_00165BC8(self, arg);
}
s32 func_00165210(CountdownAction* self, u64 id, CountdownDefinition* definition) {
    func_00165AF8(self);
    self->id = id;
    self->definition = definition;
    self->remaining = definition->duration;
    self->enabled = 0;
    return 1;
}
void func_00165268(CountdownAction* self, float dt) {
    self->remaining -= dt;
    if (self->remaining <= 0.0f) {
        char* table;
        self->enabled = 0;
        table = self->table;
        (*(void (**)(void*, s32))(table + 0x14))((char*)self + *(s16*)(table + 0x10), 0);
    }
}

s32 func_001652B8(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001652D8);
void func_001652F0(ActionView* self, s32 arg) {
    func_00165AE0(self);
    self->enabled = 0;
    func_00165BC8(self, arg);
}
s32 func_00165330(ActionView* self, u64 id, void* definition) {
    func_00165AF8(self);
    self->id = id;
    self->data = definition;
    self->enabled = 0;
    return 1;
}

s32 func_00165380(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001653A0);

void func_001653F0(void *arg0, s32 arg1) {
    func_00169BF0();
    func_00165BC8(arg0, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00165430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001656F0);

s32 func_00165A38(void) {
    func_00169EB8();
    return 1;
}
