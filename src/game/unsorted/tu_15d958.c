#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F2A38();
extern s32 D_0040F51C;
extern s32 func_00108818();
extern s32 D_0040F4C4;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_0015D958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_0015EF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_0015FDC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160398);
// Partial action-list views; field meanings are UNVERIFIED.
typedef struct {
    u32 type;
    char unknown04[12];
} ActionListItem;
typedef struct {
    s32 count;
    ActionListItem* items;
} ActionList;
extern char* D_0040F4D4;
extern void func_00172ED8(void*, ActionListItem*, ActionList*, s32);

void func_001603A0(void* unused, ActionList* list, s8 flag) {
    s32 i;
    for (i = 0; i < list->count; i++) {
        ActionListItem* item = &list->items[i];
        if (item->type < 3) func_00172ED8(D_0040F4D4 + 0x22800, item, list, flag);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160448);
// Partial lookup views; original types are UNVERIFIED.
typedef struct {
    u64 id;
} ActionLookupEntry;
typedef struct {
    char unknown00[0x3c];
    ActionLookupEntry** entries;
    char unknown40[0x3c];
    s32 count;
} ActionLookupView;

ActionLookupEntry* func_00160458(ActionLookupView* self, u64 id) {
    s32 i;
    for (i = 0; i < self->count; i++) {
        ActionLookupEntry* entry = self->entries[i];
        if (entry->id == id) return entry;
    }
    return NULL;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_001604A0);
// Partial action-list initialization views; field meanings are UNVERIFIED.
typedef struct {
    char data[24];
} ActionInitDefinition;
typedef struct {
    void* definition;
    s32 value, state;
} ActionInitEntry;
typedef struct {
    ActionInitEntry* entries;
    s32 count;
} ActionInitPool;
typedef struct {
    s32 count;
    ActionInitDefinition* definitions;
} ActionInitData;
extern char D_0040F0F0;
extern s32 func_00107CE8(void*);
extern void func_00107CC8(void*, s32);
extern void* func_00107D20(s32);
extern void func_00160B30(void*, s32);
extern void func_00160950(ActionInitPool*);

void func_00160648(ActionInitPool* self, ActionInitData* data) {
    s32 saved = func_00107CE8(&D_0040F0F0);
    s32 i;
    func_00107CC8(&D_0040F0F0, 4);
    if ((self->count = data->count) == 0)
        self->entries = NULL;
    else
        self->entries = func_00107D20(self->count * sizeof(ActionInitEntry));
    for (i = 0; i < self->count; i++) { func_00160B30(&self->entries[i], (s32)&data->definitions[i]); }
    func_00160950(self);
    func_00107CC8(&D_0040F0F0, saved);
}
#ifdef NON_MATCHING
// Partial action records; original types and field meanings are UNVERIFIED.
typedef struct {
    u64 id;
    char unknown08[13];
    u8 flags;
} ActionRecordDefinitionDraft;
typedef struct {
    ActionRecordDefinitionDraft* definition;
    s32 value, state;
} ActionRecordDraft;
typedef struct {
    ActionRecordDraft* entries;
    s32 count;
} ActionRecordPoolDraft;
void func_00160B60(s64**, s32);
void func_00160B48(void*);
void func_00160808(ActionRecordPoolDraft*, u64, s32);

// Unmatched: flag tests and register allocation differ.
s32 func_00160738(ActionRecordPoolDraft* self) {
    s32 i;
    for (i = 0; i < self->count; i++) {
        u8 flags;
        func_00160B48(&self->entries[i]);
        flags = self->entries[i].definition->flags;
        if ((flags & 4) || (flags & 8) || (flags & 2) || (flags & 0x20) || (flags & 0x10)) {
            func_00160808(self, self->entries[i].definition->id, 0);
        }
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160738);
#endif
#ifdef NON_MATCHING
// Unmatched: address addition operand order differs.

void func_00160808(ActionRecordPoolDraft* self, u64 id, s32 flag) {
    s32 i;
    for (i = 0; i < self->count; i++) {
        ActionRecordDraft* entry = &self->entries[i];
        if (entry->definition->id == id) func_00160B60((s64**)entry, flag);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160808);
#endif
#ifdef NON_MATCHING
// Unmatched: address addition operand order differs.
// Partial system view; the embedded manager's role is UNVERIFIED.
typedef struct {
    char unknown00[0x20f78];
    char manager[0xf8];
    void* active;
} ActionSystemDraft;
extern ActionSystemDraft* D_0040F0E0;
extern void func_00160BD0(ActionRecordDraft*, s32);

void func_00160898(ActionRecordPoolDraft* self, u64 id, s32 value) {
    s32 i;
    if (D_0040F0E0->active == D_0040F0E0->manager) {
        for (i = 0; i < self->count; i++) {
            ActionRecordDraft* entry = &self->entries[i];
            if (entry->definition->id == id) func_00160BD0(entry, value);
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160898);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160950);
// Partial aggregate view; field meanings are UNVERIFIED.
typedef struct {
    char unknown00[8];
    s32 field08, field0c, field10, field14, field18;
} ActionTotals;

s32 func_00160AA8(ActionTotals* self, s8 mode) {
    switch (mode) {
        case 0: return 0;
        case 1:
        case 2: return self->field0c + self->field10 + self->field14 + self->field18;
        case 3: return self->field08 + self->field0c + self->field10 + self->field14 + self->field18;
        default: return 0;
    }
}

void func_00160B30(void* arg0, s32 arg1) {
    M2C_FIELD(arg0, s32*, 0) = arg1;
    M2C_FIELD(arg0, s32*, 4) = 1;
    M2C_FIELD(arg0, s32*, 8) = 0;
}

void func_00160B48(void* arg0) {
    M2C_FIELD(arg0, s32*, 8) = 0;
    M2C_FIELD(arg0, s32*, 4) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160B58);

void func_00160B60(s64** arg0, s32 arg1) {
    if ((u32)(M2C_FIELD(arg0, s32*, 8) - 1) >= 3U) {
        M2C_FIELD(arg0, s32*, 8) = 1;
        if (arg1 != 0) {
            func_001F2A38(D_0040F51C, func_00108818(D_0040F4C4, M2C_FIELD(M2C_FIELD(arg0, s64**, 0), s32*, 0x10)),
                          arg0);
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160BD0);
// Partial action definition view; flag meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x15];
    s8 flags;
} ActionFlagDefinition;
typedef struct {
    ActionFlagDefinition* definition;
} ActionFlagView;

s32 func_00160E10(ActionFlagView* self, s32 mode) {
    if (!self->definition->flags) return 0;
    switch (mode) {
        case 0: return 0;
        case 1:
        case 2: return (self->definition->flags & 2) < 1;
        case 3: return 1;
        default: return 1;
    }
}
