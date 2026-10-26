#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00288718(void *);
extern s32 func_0035CCD8(const char *);
extern s32 func_0035D728(char *, const char *, ...);
extern void *func_00108328(void *, const char *);
extern void *D_0040F4C4;
extern const char D_00400818[], D_00400828[], D_00400830[], D_00400838[];

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
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288488_288788", func_002887F8);

s32 func_00288910(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x10D) = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288488_288788", func_00288920);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288488_288788", func_00288930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_288488_288788", func_00288A38);
