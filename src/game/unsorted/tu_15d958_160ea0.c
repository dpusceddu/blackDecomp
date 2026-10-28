#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00165AF8();
extern s32 func_00165B98();
extern s32 func_00165BB0();
extern s32 func_00160E70();
extern s32 func_00165BC8(void *, s32);
extern s32 func_00160ED8();
extern char* D_0040F4D0;

s32 func_00160EA0(void *arg0) {
    func_00165AF8();
    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    return 1;
}

void func_00160ED0(void) {

}

s32 func_00160ED8(void) {
    func_00165B98();
    return 1;
}

void func_00160EF8(void) {
    func_00165BB0();
}

void func_00160F18(void) {

}

void func_00160F20(void *arg0, s32 arg1) {
    func_00160E70();
    func_00165BC8(arg0, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00160F60);

s32 func_00161350(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161370);
#ifdef NON_MATCHING
// Unmatched: call argument load scheduling differs.
// Partial action and vtable views; field meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x20];
    u64 id;
    char unknown28[0x18];
    f32 field40, field44;
} ActionEffectDataDraft;
typedef struct {
    s16 adjustment, unknown02;
    void (*callback)(void*, s32);
} ActionEffectEntryDraft;
typedef struct {
    char unknown00[0x10];
    ActionEffectEntryDraft entry;
} ActionEffectTableDraft;
typedef struct {
    char unknown00[0x10];
    ActionEffectTableDraft* table;
    char unknown14[0xc];
    ActionEffectDataDraft* data;
    char unknown24[0x2c];
    u128 field50, field60;
} ActionEffectViewDraft;
extern void func_0012C428(void*, u128, u128, u64, s32, s32, s32, s32, s32, f32, f32);

void func_00161378(ActionEffectViewDraft* self, s32 arg) {
    ActionEffectDataDraft* data = self->data;
    s32 flag = 0;
    if (data->field44 > 0.1f) flag = 1;
    func_0012C428(D_0040F4D0, self->field60, self->field50, data->id, 1, 0, 0, flag, 0, data->field40, data->field44);
    self->table->entry.callback((char*)self + self->table->entry.adjustment, arg);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161378);
#endif
// Partial action view; original class and fields are UNVERIFIED.
typedef struct {
    u64 id;
    char unknown08[0x18];
    void* data;
} ActionInitView;

s32 func_00161418(ActionInitView* self, u64 id, void* data) {
    func_00160EA0(self);
    self->id = id;
    self->data = data;
    return 1;
}

s32 func_00161460(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161480);
#ifdef NON_MATCHING
// Unmatched: clock and manager address lifetimes differ.
// Partial native storage views; field meanings are UNVERIFIED.
typedef struct {
    u128 vector;
    float field10, field14, field18;
} ActionNativeDataDraft;
typedef struct {
    char unknown00[0x5c80];
    u64 value;
} ActionClockDraft;
extern void* D_0040F528;
extern void func_0016B5E0(void*, ActionNativeDataDraft*);
void func_00161488(ActionInitView* self) {
    ActionClockDraft* clock = (ActionClockDraft*)D_0040F4D0;
    if (clock->value != self->id) {
        ActionNativeDataDraft* data = (ActionNativeDataDraft*)self->data;
        ActionNativeDataDraft temp;
        clock->value = self->id;
        temp.vector = data->vector;
        temp.field10 = data->field10;
        temp.field14 = data->field14;
        temp.field18 = data->field18;
        func_0016B5E0(D_0040F528, &temp);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161488);
#endif
s32 func_001614E8(ActionInitView* self, u64 id, void* data) {
    func_00160EA0(self);
    self->id = id;
    self->data = data;
    return 1;
}

s32 func_00161530(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161550);
#ifdef NON_MATCHING
// Unmatched: clock and manager address lifetimes differ.
// Partial native storage views; field meanings are UNVERIFIED.
typedef struct {
    u128 vector;
    float field10;
} ActionScalarDataDraft;
typedef struct {
    char unknown00[0x5c88];
    u64 value;
} ActionClock2Draft;
extern void func_0016B590(void*, ActionScalarDataDraft*);
void func_00161558(ActionInitView* self) {
    ActionClock2Draft* clock = (ActionClock2Draft*)D_0040F4D0;
    if (clock->value != self->id) {
        ActionScalarDataDraft* data = (ActionScalarDataDraft*)self->data;
        ActionScalarDataDraft temp;
        clock->value = self->id;
        temp.vector = data->vector;
        temp.field10 = data->field10;
        func_0016B590(D_0040F528, &temp);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161558);
#endif
s32 func_001615A8(ActionInitView* self, u64 id, void* data) {
    func_00160EA0(self);
    self->id = id;
    self->data = data;
    return 1;
}
// Partial action data view; field meanings are UNVERIFIED.
typedef struct {
    u64 id;
    s32 value;
    s8 mode;
} ActionModeData;
extern void func_00160808(void*, u64, s32);
extern void func_00160898(void*, u64, s32);

void func_001615F0(ActionInitView* self) {
    ActionModeData* data = (ActionModeData*)self->data;
    switch (data->mode) {
        case 0: func_00160808(D_0040F4D0 + 0x8f0, data->id, 1); break;
        case 1: func_00160898(D_0040F4D0 + 0x8f0, data->id, data->value); break;
        case 2: return;
    }
}
s32 func_00161660(ActionInitView* self, u64 id, void* data) {
    func_00160EA0(self);
    self->id = id;
    self->data = data;
    return 1;
}
// Partial manager views; original type and method names are UNVERIFIED.
typedef void (*ActionManagerCallback)(void*, s32, s32);
typedef struct {
    s16 adjustment, unknown02;
    ActionManagerCallback callback;
} ActionManagerEntry;
typedef struct {
    char unknown00[0x40];
    ActionManagerEntry action;
} ActionManagerTable;
typedef struct {
    char unknown00[8];
    ActionManagerTable* table;
} ActionManagerView;
typedef struct {
    char unknown00[0x21070];
    ActionManagerView* manager;
} ActionSystemView;
extern ActionSystemView* D_0040F0E0;

void func_001616A8(ActionInitView* self) {
    if (*(s8*)self->data == 0) {
        ActionManagerView* manager = D_0040F0E0->manager;
        manager->table->action.callback((char*)manager + manager->table->action.adjustment, 0, 1);
    } else {
        ActionManagerView* manager = D_0040F0E0->manager;
        manager->table->action.callback((char*)manager + manager->table->action.adjustment, 0, 0);
    }
}
s32 func_00161730(ActionInitView* self, u64 id, void* data) {
    func_00160EA0(self);
    self->id = id;
    self->data = data;
    return 1;
}
// Partial action and camera views; field meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x94];
    s32 value;
    char unknown98;
    u8 field99;
} ActionCameraData;
typedef struct {
    char unknown00[0x1c];
    s8 state;
    char unknown1d[3];
    ActionCameraData* data;
} ActionCameraView;
typedef struct {
    u64 id;
} ActionCameraRecord;
extern ActionCameraRecord** D_0040F4BC;
extern void* D_0040F4F4;
extern void func_00168618(void*, s32, s32, s32);

void func_00161778(ActionCameraView* self) {
    u64 id = 0x6d6123044330fccfUL;
    ActionCameraRecord* record = *D_0040F4BC;
    if (record) id = record->id;
    if (id != 0x594c3cc765b41051UL) {
        func_00168618(D_0040F4F4, self->data->value, self->data->field99, 0);
        self->state = 0;
    }
}
#ifdef NON_MATCHING
// Unmatched: identifier and vector copy scheduling differ.
// Partial action, argument and camera views; field meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x20];
    u64 id;
    char unknown28[8];
    u128 vectors[4];
    f32 field70;
    u16 field74;
    char unknown76[2];
    f32 field78;
    s32 field7c;
    f32 field80, field84, field88, field8c;
    s32 field90;
    char unknown94[4];
    u8 field98, field99, field9a, field9b;
} ActionSetupDataDraft;
typedef struct {
    char unknown00[0x1c];
    u8 state;
    char unknown1d[3];
    ActionSetupDataDraft* data;
} ActionSetupViewDraft;
typedef struct {
    void* value;
    f32 field04;
    u8 flag08, flag09;
    s32 type;
    u16 field10;
    f32 field14;
    s32 field18;
    f32 field1c, field20, field24, field28;
} ActionSetupArgsDraft;
typedef struct {
    s16 adjustment, unknown02;
    void (*callback)(void*, s32, ActionSetupArgsDraft*);
} ActionSetupEntryDraft;
typedef struct {
    char unknown00[0x20];
    ActionSetupEntryDraft entry;
} ActionSetupTableDraft;
typedef struct {
    char unknown00[0x14];
    ActionSetupTableDraft* table;
} ActionSetupCameraDraft;

void func_00161808(ActionSetupViewDraft* self) {
    ActionSetupDataDraft* data = self->data;
    u64 id;
    u128 vectors[4];
    ActionSetupArgsDraft args;
    vectors[0] = data->vectors[0];
    id = data->id;
    vectors[1] = data->vectors[1];
    vectors[2] = data->vectors[2];
    vectors[3] = data->vectors[3];
    args.field04 = data->field70;
    args.flag08 = data->field9a == 1;
    args.flag09 = data->field9b == 1;
    args.field10 = data->field74;
    args.field14 = data->field78;
    args.field18 = data->field7c;
    args.field1c = data->field80;
    args.field20 = data->field84;
    args.field24 = data->field88;
    args.field28 = data->field8c;
    if (!id) {
        args.value = vectors;
        args.type = 1;
    } else {
        args.value = &id;
        args.type = 2;
    }
    ((ActionSetupCameraDraft*)D_0040F4BC)
        ->table->entry.callback((char*)D_0040F4BC + ((ActionSetupCameraDraft*)D_0040F4BC)->table->entry.adjustment, 7,
                                &args);
    func_00168618(D_0040F4F4, self->data->field90, self->data->field98, 0);
    self->state = 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161808);
#endif

void func_00161920(void) { func_00160E70(); }

// Partial action view; the duplicated pointer's role is UNVERIFIED.
typedef struct {
    u64 id;
    char unknown08[0x10];
    void* mirror;
    char unknown1c[4];
    void* data;
} ActionMirrorInitView;

s32 func_00161940(ActionMirrorInitView* self, u64 id, void* data) {
    func_00160EA0(self);
    self->id = id;
    self->data = data;
    self->mirror = data;
    return 1;
}

s32 func_00161990(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_001619B0);
// Partial managed-actor views; field meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x1fc0];
    u8 flag;
} ActionListActor;
typedef struct {
    u64 id;
} ActionListRef;
typedef struct {
    char unknown00[0x79a4];
    s32 count;
    char unknown79a8[4];
    ActionListRef** items;
} ActionListManager;
typedef struct {
    u64* ids;
    u8 count;
} ActionListData;
typedef struct {
    char unknown00[0x20];
    ActionListData* data;
} ActionListView;
extern ActionListManager* D_0040F514;
extern ActionListActor* func_00135550(ActionListRef*);

void func_001619B8(ActionListView* self) {
    s32 i;
    for (i = 0; i < self->data->count;) {
        s32 next = i + 1;
        u64 id = self->data->ids[i];
        s32 j;
        j = 0;
        if (D_0040F514->count > 0) do {
                ActionListRef* ref = D_0040F514->items[j];
                if (ref && id == ref->id) {
                    ActionListActor* actor = func_00135550(ref);
                    if (actor) actor->flag = 1;
                }
            } while (++j < D_0040F514->count);
        i = next;
    }
}

s32 func_00161CB8(void) {
    func_00160ED8();
    return 1;
}

void func_00161D58(void) { func_00160E70(); }

s32 func_00161DC8(void) {
    func_00160ED8();
    return 1;
}
