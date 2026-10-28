#include "include_asm.h"
#include "ps2/prelude.h"
extern void func_00383208(void*);

extern M2C_UNK D_003DC348;
extern M2C_UNK D_003DAFD0;
extern M2C_UNK D_003DAF78;
extern M2C_UNK D_003DAF20;
extern M2C_UNK D_003DAEC8;
extern M2C_UNK D_003DAE70;
extern M2C_UNK D_003DAE18;
extern M2C_UNK D_003DADC0;
extern M2C_UNK D_003DAD68;
extern M2C_UNK D_003DAD10;
extern s32 func_00382740();
extern M2C_UNK D_003DC5F8;
extern M2C_UNK D_003DCC20;
extern M2C_UNK D_003DCA38;
extern M2C_UNK D_003DC9F8;
extern M2C_UNK D_003DC9B8;
extern s32 func_00287118();
extern M2C_UNK D_003DDE80;
extern M2C_UNK D_003DDC58;
extern M2C_UNK D_003DDDC8;
extern M2C_UNK D_003DDD10;
extern M2C_UNK D_003DDBA0;
extern M2C_UNK D_003DDAE8;
extern M2C_UNK D_003DDA30;
extern M2C_UNK D_003DD978;
extern M2C_UNK D_003DD8C0;
extern M2C_UNK D_003DD808;
extern M2C_UNK D_003DD750;
extern M2C_UNK D_003DD6F0;
extern M2C_UNK D_003DD690;
extern M2C_UNK D_003DD630;
extern M2C_UNK D_003DD5D0;
extern M2C_UNK D_003DD570;
extern M2C_UNK D_003DD510;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_00382500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_003826A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_00382740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_00382778);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_00382838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_003828D8);

void func_00382BD8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

s32 func_00382BE0(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_00382BE8);

void * func_00382BF0(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x84) = &D_003DC348;
    M2C_FIELD(arg0, M2C_UNK **, 0x13C) = &D_003DAFD0;
    M2C_FIELD(arg0, M2C_UNK **, 0x19C) = &D_003DAF78;
    M2C_FIELD(arg0, M2C_UNK **, 0x1FC) = &D_003DAF20;
    M2C_FIELD(arg0, M2C_UNK **, 0x25C) = &D_003DAEC8;
    M2C_FIELD(arg0, M2C_UNK **, 0x2EC) = &D_003DAE70;
    M2C_FIELD(arg0, M2C_UNK **, 0x38C) = &D_003DAE18;
    M2C_FIELD(arg0, M2C_UNK **, 0x3DC) = &D_003DADC0;
    M2C_FIELD(arg0, M2C_UNK **, 0x42C) = &D_003DAD68;
    M2C_FIELD(arg0, M2C_UNK **, 0x47C) = &D_003DAD10;
    return arg0;
}

#ifdef NON_MATCHING
// Unmatched: loop registers and setup scheduling differ.
void func_00382C70(void* self, s32 unused) {
    u8* header = (u8*)self + 0x14;
    s32 offset;
    u32 i;
    s32 cursor;
    offset = M2C_FIELD(header, s32*, 0);
    if (offset) {
        M2C_FIELD(header, s32*, 0) = offset + (s32)header;
        i = 0;
        if (M2C_FIELD(header, u8*, 0xC)) {
            cursor = 0;
            do {
                i++;
                func_00383208((void*)(M2C_FIELD(header, s32*, 0) + cursor));
                cursor += 0x60;
            } while (i < M2C_FIELD(header, u8*, 0xC));
        }
    }
    offset = M2C_FIELD(header, s32*, 4);
    if (offset) {
        M2C_FIELD(header, s32*, 4) = offset + (s32)header;
        i = 0;
        if (M2C_FIELD(header, u8*, 0xD)) {
            cursor = 0;
            do {
                i++;
                func_00383208((void*)(M2C_FIELD(header, s32*, 4) + cursor));
                cursor += 0x60;
            } while (i < M2C_FIELD(header, u8*, 0xD));
        }
    }
    offset = M2C_FIELD(header, s32*, 8);
    if (offset) {
        M2C_FIELD(header, s32*, 8) = offset + (s32)header;
        i = 0;
        if (M2C_FIELD(header, u8*, 0xE)) {
            cursor = 0;
            do {
                i++;
                func_00383208((void*)(M2C_FIELD(header, s32*, 8) + cursor));
                cursor += 0x60;
            } while (i < M2C_FIELD(header, u8*, 0xE));
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_00382C70);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500", func_00382D60);

void * func_00383068(void *arg0) {
    func_00382740();
    M2C_FIELD(arg0, M2C_UNK **, 0x10) = &D_003DC5F8;
    M2C_FIELD(arg0, M2C_UNK **, 0x574) = &D_003DCC20;
    M2C_FIELD(arg0, M2C_UNK **, 0x6A4) = &D_003DCA38;
    M2C_FIELD(arg0, M2C_UNK **, 0x7B4) = &D_003DC9F8;
    M2C_FIELD(arg0, M2C_UNK **, 0x854) = &D_003DC9B8;
    return arg0;
}


void func_00383208(void* unused) {
    func_00287118();
}


void * func_00383608(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x64) = &D_003DDE80;
    M2C_FIELD(arg0, M2C_UNK **, 0x78) = &D_003DDC58;
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_003DDDC8;
    M2C_FIELD(arg0, M2C_UNK **, 0xA4) = &D_003DDD10;
    M2C_FIELD(arg0, M2C_UNK **, 0xB8) = &D_003DDBA0;
    M2C_FIELD(arg0, M2C_UNK **, 0xD0) = &D_003DDAE8;
    M2C_FIELD(arg0, M2C_UNK **, 0x114) = &D_003DDA30;
    M2C_FIELD(arg0, M2C_UNK **, 0x130) = &D_003DD978;
    M2C_FIELD(arg0, M2C_UNK **, 0x14C) = &D_003DD8C0;
    M2C_FIELD(arg0, M2C_UNK **, 0x170) = &D_003DD808;
    M2C_FIELD(arg0, M2C_UNK **, 0x1A0) = &D_003DD750;
    return arg0;
}

void * func_00383698(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_003DD6F0;
    M2C_FIELD(arg0, M2C_UNK **, 0x160) = &D_003DD690;
    M2C_FIELD(arg0, M2C_UNK **, 0x1D0) = &D_003DD630;
    M2C_FIELD(arg0, M2C_UNK **, 0x260) = &D_003DD5D0;
    M2C_FIELD(arg0, M2C_UNK **, 0x2F0) = &D_003DD570;
    M2C_FIELD(arg0, M2C_UNK **, 0x370) = &D_003DD510;
    return arg0;
}
