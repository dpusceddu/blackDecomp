#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_003C3D80;
extern M2C_UNK D_0044E750;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002B6FD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002B7550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002B8858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BA398);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BA948);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BACF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BAF08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BB148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BB538);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BB830);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BBBE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BC4B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BC6C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BC9B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BCCF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BCDE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BD010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BD188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BD2C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BD5B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BD6A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BDDC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BE120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BEE30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BF160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BF168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BF298);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BF478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BF670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BF748);

M2C_UNK * func_002BFE58(void) {
    return &D_003C3D80;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFE68);

M2C_UNK * func_002BFEC0(void) {
    return &D_0044E750;
}

s32 func_002BFED0(s32 arg0) {
    s32 var_2;
    s32 var_4;

    var_4 = arg0;
    var_2 = -1;
    if (var_4 != 0) {
        do {
            var_4 = (s32) ((u32) var_4 >> 1);
            var_2 += 1;
        } while (var_4 != 0);
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002BFF88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C00F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002C0168);

s32 func_002C01C0(s32 *arg0) {
    s32 var_3;

    var_3 = 0;
    if (arg0 != NULL) {
        var_3 = (*arg0 == 0) ? 0 : 4;
    }
    return var_3;
}
