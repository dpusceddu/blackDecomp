#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035E7D8(s32);
extern void *D_0040F4D0;
extern s32 func_00170740();
extern s32 func_002F4A48();
extern M2C_UNK D_003DD198;
extern s32 func_0028B2A8(void *, s32);
extern void * D_0040F4D4;
extern s32 func_002F4620(s32, s32, s32);
extern s32 func_0028B1F0(void *, s32);
extern s32 func_002F47B0(s32, s32, s32);
extern s32 func_002E1548();
extern M2C_UNK D_003DCFA0;
extern s32 func_002E1818();

// Partial state and virtual-call views; original class and field meanings are UNVERIFIED.
typedef struct {
    s16 adjustment, unknown02;
    void (*callback)(void*);
} SequenceMethodView;
typedef struct {
    char unknown00[0x88];
    SequenceMethodView method;
} SequenceTableView;
typedef struct {
    SequenceTableView* table;
    char unknown04[0x60];
    s32 count;
    char unknown68[8];
    void* data;
    f32 time;
    u8 flag;
    char unknown79[3];
    s32 state, field80;
} SequenceStateView;

void func_00170798(void* arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = func_0035E7D8(arg1 * 0x10);
    M2C_FIELD(arg0, s32*, 0x6C) = arg1;
    M2C_FIELD(arg0, s32*, 0x60) = temp_2;
}

#ifdef NON_MATCHING
// Unmatched: clock load and vector address scheduling differ.
// Partial matrix views; original types and field meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x70];
    u128 vectors[4];
} SequenceSourceDraft;
typedef struct {
    char unknown00[0x70];
    SequenceSourceDraft* source;
    f32 time;
    u8 flag;
    char unknown79[3];
    s32 state, field80;
    char unknown84[12];
    u128 vectors[4];
} SequenceSetupDraft;
extern void func_00171200(SequenceStateView*);

void func_001707D8(SequenceSetupDraft* self, SequenceSourceDraft* source, u8 flag) {
    u128* vectors = source->vectors;
    self->source = source;
    self->time = M2C_FIELD(D_0040F4D0, f32*, 0x20);
    self->state = 0;
    self->field80 = 0;
    self->vectors[0] = vectors[0];
    self->vectors[1] = vectors[1];
    self->vectors[2] = vectors[2];
    self->vectors[3] = vectors[3];
    self->flag = flag;
    func_00171200((SequenceStateView*)self);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170798", func_001707D8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170798", func_00170838);
s32 func_00170C90(SequenceStateView* self) {
    if (self->count) self->table->method.callback((char*)self + self->table->method.adjustment);
    self->data = NULL;
    return 1;
}

void func_00170CD8(void *arg0)
{
  f32 new_var;
  if ((M2C_FIELD(arg0, s32 *, 0x7C)) == 3)
  {
    new_var = (f32) (M2C_FIELD(D_0040F4D0, f32 *, 0x20));
 dummy_label_91248: ;
    *((s32 *) ((0, ((s8 *) arg0) + 0x7C))) = 4;
    M2C_FIELD(arg0, f32 *, 0x74) = new_var;
    return;
  }
  func_00170740(arg0, arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170798", func_00170D20);

void * func_00171110(void *arg0) {
    func_002F4A48();
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003DD198;
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
    M2C_FIELD(arg0, s32 *, 0x80) = 0;
    return arg0;
}

s32 func_00171158(void) {
    return 1;
}

s32 func_00171160(void) { return 0; }

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170798", func_00171168);
void func_00171200(SequenceStateView* self) {
    self->state = 2;
    if (self->count) self->table->method.callback((char*)self + self->table->method.adjustment);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170798", func_00171240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170798", func_00171398);

s32 func_00171758(void* arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32*, 0x7C);
    if (((u32)(temp_3 - 3) < 2U) || (temp_3 == 1)) { return 0; }
    return 1;
}

void func_00171788(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        func_0028B2A8(D_0040F4D4 + 0x13D0, arg2);
    }
    func_002F4620(arg0, arg1, arg2);
}

void func_001717E8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        func_0028B1F0(D_0040F4D4 + 0x13D0, arg2);
    }
    func_002F47B0(arg0, arg1, arg2);
}

#ifdef NON_MATCHING
// Unmatched: indexed-entry temporary registers differ.
// Partial cleanup views; field meanings are UNVERIFIED.
typedef struct { s32 unknown00, unknown04, value, unknown0c; } SequenceCleanupEntryDraft;
typedef struct { char unknown00[0x60]; SequenceCleanupEntryDraft* entries; s32 count; } SequenceCleanupDraft;
extern void func_002F44E8(void*);

void func_00171848(SequenceCleanupDraft* self) {
    s32 i = self->count;
    while (--i >= 0) {
        s32 value = self->entries[i].value;
        if (value) func_0028B1F0((char*)D_0040F4D4 + 0x13d0, value);
    }
    func_002F44E8(self);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170798", func_00171848);
#endif

void func_001718C8(void) {}

#include "ps2/recovered_types.h"
extern s32 func_00171918(void*, s32);

void func_001718D0(void* arg0, s32* arg1, s32 arg2) {
    if (M2C_FIELD(arg0, s32*, 0x7C) == 3) { M2C_FIELD(arg0, s32*, 0x7C) = 1; }
    if (M2C_FIELD(arg0, s32*, 0x7C) == 2) { func_00171918(arg0, 1); }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170798", func_00171918);

M2C_UNK** func_00171A08(M2C_UNK** arg0) {
    func_002E1548();
    *arg0 = &D_003DCFA0;
    return arg0;
}

s32 func_00171A40(void* arg0, void* arg1) { return func_002E1818() != 0; }

s32 func_00171A60(void) { return 0; }
