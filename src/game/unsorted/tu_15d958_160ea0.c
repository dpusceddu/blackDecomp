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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161378);
// Partial action view; original class and fields are UNVERIFIED.
typedef struct { u64 id; char unknown08[0x18]; void* data; } ActionInitView;

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
typedef struct { u128 vector; float field10, field14, field18; } ActionNativeDataDraft;
typedef struct { char unknown00[0x5c80]; u64 value; } ActionClockDraft;
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
typedef struct { u128 vector; float field10; } ActionScalarDataDraft;
typedef struct { char unknown00[0x5c88]; u64 value; } ActionClock2Draft;
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
typedef struct { u64 id; s32 value; s8 mode; } ActionModeData;
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_001616A8);
s32 func_00161730(ActionInitView* self, u64 id, void* data) {
    func_00160EA0(self);
    self->id = id;
    self->data = data;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_00161808);

void func_00161920(void) {
    func_00160E70();
}

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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_160ea0", func_001619B8);

s32 func_00161CB8(void) {
    func_00160ED8();
    return 1;
}


void func_00161D58(void) {
    func_00160E70();
}


s32 func_00161DC8(void) {
    func_00160ED8();
    return 1;
}
