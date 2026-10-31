#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00288718(void *);
extern s32 func_0035CCD8(const char *);
extern s32 func_0035D728(char *, const char *, ...);
extern void *func_00108328(void *, const char *);
extern void *D_0040F4C4;
extern const char D_00400818[], D_00400828[], D_00400830[], D_00400838[];
extern void func_00272AA8(void *);
extern void* func_003822E0(void *, s32);
extern void* func_003822F8(void *, s32);
extern void func_0028EED8(void *);
extern void func_001AF930(void *);
extern void func_00108540(void *, s32, void *, s32);

typedef struct {
    u8 unk_00;
    u8 count;
    u8 unk_02[2];
    u8 *entries;
} Recovered_EffectRecordList;

typedef struct {
    char name[0x20];
    void *textures[3];
} Recovered_MuzzleTextures; /* Original structure and names UNVERIFIED. */

typedef struct {
    u8 unk_00[8];
    s32 count;
    void *entries;
} Recovered_EffectArchive;

typedef struct {
    Recovered_EffectArchive *textures;
    Recovered_EffectArchive *models;
} Recovered_EffectPackage; /* Archive roles UNVERIFIED. */

void func_00288788(void) {

}

s32 func_00288790(Recovered_EffectRecordList *list) {
    u8 index = 0;
    if (list->count != 0) {
        do {
            func_00288718(list->entries + (index << 5));
            index++;
        } while (index < list->count);
    }
    return 1;
}
#ifdef NON_MATCHING
// Unmatched: lookup loop scheduling and owned string block differ.
s32 func_002887F8(Recovered_MuzzleTextures *muzzle) {
    char name[16];
    char message[48];
    s32 index = 0;
    if (func_0035CCD8(muzzle->name) == 0) {
        s32 i = 2;
        do {
            muzzle->textures[i] = 0;
            i--;
        } while (i >= 0);
        return i;
    }
    do {
        s32 variant = index + 1;
        func_0035D728(name, D_00400818, D_00400828, muzzle->name, D_00400830, variant);
        muzzle->textures[index] = func_00108328(D_0040F4C4, name);
        if (muzzle->textures[index] == 0) {
            func_0035D728(message, D_00400838, name);
        }
        index = variant;
    } while (index < 3);
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288488_288788", func_002887F8);
#endif

s32 func_00288910(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x10D) = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288488_288788", func_00288920);
void func_00288930(Recovered_EffectPackage* self) {
    s32 textureIndex = 0, modelIndex;
    Recovered_EffectArchive *textures, *models;
    textures = (Recovered_EffectArchive*)((u32)self->textures + (u32)self);
    self->textures = textures;
    self->models = (Recovered_EffectArchive*)((u32)self->models + (u32)self);
    func_00272AA8(textures);
    for (; textureIndex < textures->count; ++textureIndex) func_0028EED8(func_003822E0(textures, textureIndex));
    modelIndex = 0;
    func_00108540(D_0040F4C4, 0, self->textures, 0);
    models = self->models;
    func_00272AA8(models);
    for (; modelIndex < models->count; ++modelIndex) func_001AF930(func_003822F8(models, modelIndex));
    func_00108540(D_0040F4C4, 1, self->models, 0);
}
// Partial native resource header; original class identity remains UNVERIFIED.
typedef struct SectionResourceView {
    u8 unknown[0x1C];
    u32 field1C, field20, field24, field28, field2C, field30, field34, field38, field3C, field40;
} SectionResourceView;
void func_00288A38(SectionResourceView* self) {
    s32 i = 0;
    void* list = (void*)(self->field1C + (u32)self);
    self->field24 += (u32)self;
    self->field1C = (u32)list;
    self->field20 += (u32)self;
    self->field28 += (u32)self;
    self->field2C += (u32)self;
    self->field30 += (u32)self;
    self->field34 += (u32)self;
    self->field38 += (u32)self;
    self->field3C += (u32)self;
    self->field40 += (u32)self;
    func_00272AA8(list);
    for (; i < M2C_FIELD(list, s32*, 8); ++i) func_0028EED8(func_003822E0(list, i));
    i = 0;
    func_00108540(D_0040F4C4, 0, (void*)self->field1C, 0);
    list = (void*)self->field20;
    func_00272AA8(list);
    for (; i < M2C_FIELD(list, s32*, 8); ++i) func_001AF930(func_003822F8(list, i));
    func_00108540(D_0040F4C4, 1, (void*)self->field20, 0);
    func_00272AA8((void*)self->field24);
    func_00272AA8((void*)self->field28);
    func_00272AA8((void*)self->field2C);
    func_00272AA8((void*)self->field30);
    func_00272AA8((void*)self->field34);
}
