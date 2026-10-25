#include "include_asm.h"
#include "ps2/prelude.h"

extern void * func_001AFD80();
extern s32 func_0014C140();
extern s32 func_00151B40();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_00150D68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_00150F98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_00151288);

s32 func_001513A0(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_001513A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_001515F8);

s32 func_001517A8(void *arg0) {
    void *temp_2;

    temp_2 = func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
    if (temp_2 == NULL) {
        return 0;
    }
    return ((u16) M2C_FIELD(temp_2, u16 *, 0x5A) >> 0xF) ^ 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_001517E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_001519C8);

void func_00151AE8(void *arg0) {
    void *temp_2;

    func_0014C140();
    temp_2 = func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
    if ((temp_2 != NULL) && (M2C_FIELD(temp_2, u16 *, 0x5A) & 0x10)) {
        func_00151B40(arg0, 0, 0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_00151B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_00151CB0);

void func_00151E60(void *arg0) {
    func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_00151E80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68", func_00152000);
