#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_0048EC20;
extern s32 func_0037B988();
extern s32 func_003230C0();
extern s32 func_0037B608();
extern s32 func_003110B0();
extern s32 func_00323188();

s32 func_00378D90(s32 arg0)
{
 do { } while (0);
  func_0037B2D0(arg0 + 0x104, arg0 + 0x16C);
  return arg0;
  if (((!arg0) && (!arg0)) && (!arg0))
  {
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_00378DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_00378DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_00379298);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_003792D0);
extern char D_0040C6E0, D_003D9B68, D_003D9BD0;
extern s32 func_00311BF8(void*);
extern s32 func_00311BB8(void*, void*, s32);
extern void* func_00311E60(void*, void*, s32, void*, s32);

void* func_00379330(void) {
    void* result;
    if (func_00311BF8(&D_0048EC20)) {
        func_00311BB8(&D_0048EC20, &D_0040C6E0, 0);
        func_00311E60(&D_0048EC20, &D_003D9B68, 5, &D_003D9BD0, 5);
        result = &D_0048EC20;
    } else {
        result = NULL;
    }
    return result;
}

void func_003793A0(void) { func_00311CA0(&D_0048EC20); }

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_003793C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_00379528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_00379658);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_00379A88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_00379DF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037A160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037A478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037AE38);
#ifdef NON_MATCHING
// Partial resource views; original types and field meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x5c];
    s32 flags;
    char unknown60[8];
    s32 field68;
    char unknown6c[4];
    s32 field70;
    char unknown74[0xd4];
    s32 field148, field14c, field150;
} AudioResourceDraft;
extern AudioResourceDraft* func_0037B318(AudioResourceDraft*, void*, void*, s32, s32, s32, s32, s32);
extern s32 func_00379658(AudioResourceDraft*, s32*, s32*);
extern void func_0037B470(AudioResourceDraft*, s32*, s32*);
extern s32 func_003230F0(void*, s32, s32);

// Unmatched: initial argument move differs.
AudioResourceDraft* func_0037B1D0(AudioResourceDraft* self, s32 a, s32 b, s32 c, s32 d, s32 e) {
    AudioResourceDraft* result = func_0037B318(self, &self->field68, &self->field70, a, b, c, d, e);
    if (result) {
        result->field14c = 0;
        result->field150 = 0;
        result->field148 = 0;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B1D0);
#endif
#ifdef NON_MATCHING
// Unmatched: saved-register allocation differs.
s32 func_0037B220(AudioResourceDraft* self) {
    s32 result = func_00379658(self, &self->field68, &self->field70);
    if (!(self->flags & 1)) func_0037B470(self, &self->field68, &self->field148);
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B220);
#endif
s32 func_0037B288(void* self, void* list) {
    s32 result;
    if (M2C_FIELD(self, s32*, 8) == 5) {
        void* voice = (void*)func_0037B988(self, list, 0);
        result = func_003230F0(voice, M2C_FIELD(voice, s32*, 0x80), 3);
    } else
        result = 0;
    return result;
}

s32 func_0037B2D0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_2;

    temp_2 = func_0037B988(arg0, arg1, M2C_FIELD(arg2, s32 *, 4));
    return func_003230C0((s32) temp_2, M2C_FIELD(temp_2, s32 *, 0x80), 2, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B310);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B318);

void func_0037B450(void) {
    func_0037B608();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B518);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B740);

s32 func_0037B8A8(s32 arg0, s32 arg1) {
    *M2C_FIELD(arg0, void ***, 0x48) = M2C_FIELD(arg0, void **, 0x44);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x48);
    return func_003110B0(arg0, M2C_FIELD(arg1, s32 *, 0x54), M2C_FIELD(arg1, s32 *, 0x58));
}

s32 func_0037B8E8(s32 arg0, s32 arg1) {
    return func_00323188(arg0, M2C_FIELD(arg0, s32 *, 0x40), 2, arg1);
}

// Partial linked-list and parameter views; field meanings are UNVERIFIED.
typedef struct AudioNodeDraft {
    struct AudioNodeDraft* next;
    char unknown04[0x38];
    s32 channel;
} AudioNodeDraft;
typedef struct {
    char unknown00[0x20];
    AudioNodeDraft* first;
} AudioListOwnerDraft;
typedef struct {
    s32 unknown00;
    u32 count;
} AudioListDraft;
typedef struct {
    char unknown00[0x18];
    f32 values[0]; /* Trailing parameter values; allocation covers list->count entries. */
} AudioParamsDraft;
/* Forwards the parameter callback result; its original result type is UNVERIFIED. */
extern s32 func_003231D0(void*, s32, s32, f32);

void func_0037B910(AudioListOwnerDraft* self, AudioListDraft* list, AudioParamsDraft* data) {
    AudioNodeDraft* node = self->first;
    u32 i;
    for (i = 0; i < list->count; i++) {
        func_003231D0((char*)node - 0x44, node->channel, 1, data->values[i]);
        node = node->next;
    }
}

#ifdef NON_MATCHING
// Unmatched: traversal loop shape and register allocation differ.
typedef struct AudioLinkDraft {
    struct AudioLinkDraft* next;
    struct AudioLinkDraft* previous;
} AudioLinkDraft;
typedef struct {
    char unknown00[0x20];
    AudioLinkDraft* first;
    AudioLinkDraft* last;
} AudioLinkOwnerDraft;
s32 func_0037B988(AudioLinkOwnerDraft* self, AudioListDraft* list, u32 index) {
    AudioLinkDraft* node;
    u32 i;
    if (index < list->count / 2) {
        node = self->first;
        if (index != 0) {
            i = 1;
            do { node = node->next; } while (i++ != index);
        }
    } else {
        node = self->last;
        if (list->count - 1 != index) {
            i = list->count - 2;
            do { node = node->previous; } while (i-- != index);
        }
    }
    return (s32)((char*)node - 0x44);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037B988);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_378d90", func_0037BA00);
