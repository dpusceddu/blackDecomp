#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035D728(void *, M2C_UNK *, s32);
extern M2C_UNK D_003F9598;
extern s32 func_00275260(void *, s32, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fba78", func_001FBA78);

void func_001FBB40(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fba78", func_001FBD90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fba78", func_001FC188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fba78", func_001FC280);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fba78", func_001FC320);
#ifdef NON_MATCHING
// Unmatched: clamp branch and definition-field load width differ.
// Partial state and definition views; original types and field meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x158];
    f32 limit, current;
    char unknown160[0x35];
    s8 index;
} WeaponScaleStateDraft;
typedef struct {
    char unknown00[0x60];
    s32 value;
} WeaponScaleDefinitionDraft;
extern void* D_0040F4E0;
extern WeaponScaleDefinitionDraft* func_0015D248(void*, s32, s32);
extern s32 func_001FC558(void*, s32, s32);

s32 func_001FC400(WeaponScaleStateDraft* self, u16 amount) {
    WeaponScaleDefinitionDraft* definition = func_0015D248(D_0040F4E0, self->index, 0);
    f32 ratio = self->current / self->limit;
    if (ratio > 1.0f) ratio = 1.0f;
    return func_001FC558(self, (s32)(amount * ratio) & 0xffff, definition->value & 0xffff);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fba78", func_001FC400);
#endif

#include "ps2/recovered_types.h"
extern s32 func_001FC558(void*, s32, s32);

s32 func_001FC490(void* arg0) {
    f32 var_f1;

    var_f1 = M2C_FIELD(arg0, f32 *, 0x15C) / M2C_FIELD(arg0, f32 *, 0x158);
    if (var_f1 > 1.0f) {
        var_f1 = 1.0f;
    }
    return func_001FC558(arg0, (s32) ((f32) M2C_FIELD(arg0, u16 *, 0x144) * (1.0f - var_f1)) & 0xFFFF, (s32) M2C_FIELD(arg0, u16 *, 0x146));
}

void func_001FC4F8(void) {

}

void func_001FC500(void) {

}

void func_001FC508(s32 arg0, s32 arg1) {
    void *temp_16;

    temp_16 = arg0 + 0x16C;
    func_0035D728(temp_16, &D_003F9598, arg1 & 0xFFFF);
    func_00275260(temp_16, arg0 + 0x17C, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fba78", func_001FC558);
