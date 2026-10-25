#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00312C70();
extern s32 func_00317C20();
extern M2C_UNK * D_0045C938;
extern M2C_UNK * D_0045C960;

void func_00329958(M2C_UNK *arg0) {
    s32 var_17;
    u8 temp_3;

    temp_3 = M2C_FIELD(arg0, u8 *, 9);
    var_17 = 0;
    if (temp_3 & 1) {
        var_17 = 1;
        M2C_FIELD(arg0, u8 *, 9) = (u8) (temp_3 & 0xFE);
    }
    if (M2C_FIELD(arg0, u8 *, 9) & 2) {
        func_00312C70(M2C_FIELD(arg0, M2C_UNK **, 0));
    }
    if (M2C_FIELD(arg0, u8 *, 9) & 1) {
        func_00317C20(&D_0045C938, arg0);
    }
    if (var_17 != 0) {
        func_00317C20(&D_0045C960, arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_003299E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_00329B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_00329B08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_00329C70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_00329E20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_00329E90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_00329F40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_00329F70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_0032A080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329958", func_0032A0B0);
