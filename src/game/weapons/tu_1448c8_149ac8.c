#include "include_asm.h"
#include "ps2/prelude.h"

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
    char *table;
    u32 unk14;
    void *data;
    u8 enabled;
    u8 unk1D[3];
    void *definition;
    s32 state;
    float remaining;
    s32 unk2C;
} ActionView;

typedef struct CounterDefinition { u8 unk00[8]; u8 count; u8 repeat; } CounterDefinition;
typedef struct CounterAction {
    u64 id;
    u8 unk08[8];
    char *table;
    u32 unk14;
    s32 count;
    CounterDefinition *definition;
} CounterAction;
typedef struct CountdownDefinition { u8 unk00[8]; float duration; } CountdownDefinition;
typedef struct CountdownAction {
    u64 id;
    u8 unk08[8];
    char *table;
    u32 unk14;
    u8 enabled;
    u8 unk19[3];
    float remaining;
    CountdownDefinition *definition;
} CountdownAction;
extern void func_00160E70(void *);
extern void func_00160EA0(void *);
extern void func_00160EF8(void *);
extern void func_00165AF8(void *);

#define ACTION_OFFSET(type, field) ((u32)&((type *)0)->field)
typedef char ActionIdWidth[(sizeof(((ActionView *)0)->id) == 8) ? 1 : -1];
typedef char ActionTableOffset[(ACTION_OFFSET(ActionView, table) == 0x10) ? 1 : -1];
typedef char ActionDefinitionOffset[(ACTION_OFFSET(ActionView, definition) == 0x20) ? 1 : -1];
typedef char CounterDefinitionOffset[(ACTION_OFFSET(CounterAction, definition) == 0x1C) ? 1 : -1];
typedef char CountdownDefinitionOffset[(ACTION_OFFSET(CountdownAction, definition) == 0x20) ? 1 : -1];
#undef ACTION_OFFSET


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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00149B60);

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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014CDB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014CE00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014CE68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014D358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DA80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DB90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DC18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DC78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DE58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DF68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014E018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014EC10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014EC40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014EC90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014F7F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014F838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014F888);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014FDA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014FEE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001507E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00152A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00153448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001534A8);
s32 func_001550C0(u16 *counts, s32 index, u8 amount) {
    counts = (u16 *)((s8 *)counts + index * 2);
    if (*counts < amount) return 0;
    *counts -= amount;
    return 1;
}
s32 func_001550F0(u16 *counts, s32 index) {
    counts = (u16 *)((s8 *)counts + index * 2);
    if (*counts) {
        --*counts;
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155B08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155E48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00156110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00158E88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00161DF0);
void func_00162160(ActionView *self, s32 arg) {
    func_00160E70(self);
    self->definition = NULL;
    self->state = 0;
    self->unk2C = 0;
    func_00165BC8(self, arg);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001621A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162600);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001626D0);
s32 func_00162758(ActionView *self, u64 id, void *definition) {
    func_00160EA0(self);
    self->definition = definition;
    self->id = id;
    self->data = definition;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001627D0);
s32 func_001628E8(ActionView *self, u64 id, void *definition) {
    func_00160EA0(self);
    self->definition = definition;
    self->id = id;
    self->data = definition;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162960);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162A60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162F28);
s32 func_001630E8(ActionView *self, u64 id, void *definition) {
    func_00160EA0(self);
    self->id = id;
    self->definition = definition;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163158);
s32 func_001631B0(ActionView *self, u64 id, void *definition) {
    func_00160EA0(self);
    self->id = id;
    self->definition = definition;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001634D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001635D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163628);
void func_00163AB8(ActionView *self, s32 arg) {
    func_00160E70(self);
    self->state = 0;
    func_00165BC8(self, arg);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163B50);
void func_00163C58(ActionView *self) {
    func_00160EF8(self);
    self->definition = NULL;
    self->state = 5;
    self->data = NULL;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163DB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163FD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001640D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001641A8);
typedef struct GroupAction { u8 unk00[0x69]; u8 count; } GroupAction;

s32 func_00164238(GroupAction *self) {
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

s32 func_001650F8(CounterAction *self, u64 id, CounterDefinition *definition) {
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
void func_00165170(CounterAction *self) {
    if (++self->count == self->definition->count) {
        char *table = self->table;
        (*(void (**)(void *))(table + 0x14))((char *)self + *(s16 *)(table + 0x10));
        if (self->definition->repeat) self->count = 0;
    }
}
void func_001651D0(CountdownAction *self, s32 arg) {
    func_00165AE0(self);
    self->enabled = 0;
    func_00165BC8(self, arg);
}
s32 func_00165210(CountdownAction *self, u64 id, CountdownDefinition *definition) {
    func_00165AF8(self);
    self->id = id;
    self->definition = definition;
    self->remaining = definition->duration;
    self->enabled = 0;
    return 1;
}
void func_00165268(CountdownAction *self, float dt) {
    self->remaining -= dt;
    if (self->remaining <= 0.0f) {
        char *table;
        self->enabled = 0;
        table = self->table;
        (*(void (**)(void *, s32))(table + 0x14))((char *)self + *(s16 *)(table + 0x10), 0);
    }
}

s32 func_001652B8(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001652D8);
void func_001652F0(ActionView *self, s32 arg) {
    func_00165AE0(self);
    self->enabled = 0;
    func_00165BC8(self, arg);
}
s32 func_00165330(ActionView *self, u64 id, void *definition) {
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
