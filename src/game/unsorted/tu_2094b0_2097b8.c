#include "include_asm.h"
#include "ps2/prelude.h"

extern void * func_0020BC00();
extern void * D_0040F544;
extern s32 func_00209EC8();
extern s32 func_0027C278();
extern s32 func_00209618();
extern M2C_UNK func_00209A60;

void func_002097B8(void) {

}

s32 func_002097C0(void *arg0) {
    void *temp_16;

    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    temp_16 = func_0020BC00(D_0040F544, 2);
    func_00209EC8(temp_16, func_0027C278("FEInputId"), arg0);
    func_00209618(D_0040F544 + 4, "ListenForPlayer", &func_00209A60);
    M2C_FIELD(arg0, s8 *, 8) = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2097b8", func_00209858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2097b8", func_00209930);
