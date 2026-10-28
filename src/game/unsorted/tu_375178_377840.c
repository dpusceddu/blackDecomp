#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_003753E0();
extern s32 func_003778D8();
extern s32 func_00377968();
extern s32 func_0031D268(void *, M2C_UNK, M2C_UNK);
extern s32 func_0037B1D0();
extern s32 func_0037B220(s32);

void func_00377840(void) {
    func_003753E0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377860);

void func_00377868(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_003778D8() << 5));
}

void func_003778A0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14C) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), s32 *, 0x10) + (func_00377968() << 5));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_003778D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377968);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377A10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377A20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377BD8);
// UNVERIFIED: original buffer type and identity.
typedef struct { u8 data[0x2000]; s32 occupied; } Recovered_ScratchBuffer;
extern Recovered_ScratchBuffer D_0048AB88[2];
void* func_00377BE0(void) {
    s32 i = 0;
    u8* buffer = (u8*)D_0048AB88;
    s32* occupied = &D_0048AB88[0].occupied;
    do {
        i++;
        if (*occupied) {
            buffer += 0x2004;
            occupied = (s32*)((u8*)occupied + 0x2004);
        } else {
            *occupied = 1;
            return buffer;
        }
    } while (i < 2);
    return 0;
}
#ifdef NON_MATCHING
// Unmatched: loop and return-path scheduling differ.
void func_00377C28(void* buffer) {
    s32 i = 0;
    if (buffer == D_0048AB88) {
        D_0048AB88[0].occupied = 0;
        return;
    }
    do {
        i++;
        if (i < 2) {
            if (buffer == &D_0048AB88[i]) {
                D_0048AB88[i].occupied = 0;
                return;
            }
        }
    } while (i < 2);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_375178_377840", func_00377C28);
#endif

void * func_00377C80(void *arg0, s32 arg1, s16 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s16 *, 4) = arg2;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    return (func_0031D268(arg0 + 0xC, 1, 1) == 0) ? NULL : arg0;
}


s32 func_00378698(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x340) = 0;
    return (func_0037B1D0(arg0 + 0x104, arg1, 0xBB80, M2C_FIELD(arg2, s32 *, 0), M2C_FIELD(arg2, s32 *, 4), M2C_FIELD(arg2, s32 *, 8)) == 0) ? 0 : arg0;
}


s32 func_00378740(s32 arg0) {
    func_0037B220(arg0 + 0x104);
    return arg0;
}
