#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003BFB40;
extern s32 D_0040EB74;
extern s32 D_0040EB78;
extern s32 D_003BFB3C;

void func_00272C18(s32 arg0, s32 arg1, f32 fparg0)
{
  unsigned int new_var;
 new_var = arg1 * 4; dummy_label_840098: ;
  *((f32 *) (((s8 *) (arg0 + new_var)) + (0x24 & 0xFFFFFFFFu))) = fparg0;
}

#include "ps2/recovered_types.h"
extern s32 func_002732E0(void *, void *);

s32 func_00272C28(void *arg0, void *arg1, s128 arg2, s32 *arg3) {
    M2C_FIELD(arg1, s128 *, 0) = (s128) arg2;
    M2C_FIELD(arg1, s32 **, 0x34) = arg3;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0x24) = 0;
    return func_002732E0(arg0, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272CC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272DE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002730A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002732E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273378);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002733E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002734B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273708);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002737E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273888);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273960);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273A18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00273F30);

s32 func_00274018(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_2;

    var_2 = arg1 + 8;
    if (arg2 != 0) {
        var_2 = ((var_2 + arg2) - 1) & -arg2;
    }
    return (var_2 * arg0) + arg2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274040);

void func_002740D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

s32 func_002740E8(s32 arg0, s32 arg1) {
    M2C_UNK *temp_2;
    M2C_UNK *temp_2_2;
    M2C_UNK *temp_3;
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0);
    temp_3 = M2C_FIELD(temp_5, M2C_UNK **, 0x10);
    if (temp_3 == NULL) {
        goto block_2;
    }
    goto block_4;
block_2:
    return 0;
block_4:
    M2C_FIELD(temp_5, M2C_UNK **, 0x10) = (M2C_UNK *) *temp_3;
    temp_2 = *temp_3;
    if (temp_2 == NULL) {
        goto block_6;
    }
    M2C_FIELD(temp_2, s32 *, 4) = 0;
block_6:
    temp_2_2 = M2C_FIELD(arg0, M2C_UNK **, 4);
    if (temp_2_2 == NULL) {
        goto block_8;
    }
    *temp_3 = temp_2_2;
    goto block_10;
block_8:
    *temp_3 = NULL;
    goto block_11;
block_10:
    M2C_FIELD(temp_2_2, M2C_UNK **, 4) = temp_3;
block_11:
    M2C_FIELD(arg0, M2C_UNK **, 4) = temp_3;
    return (s32) temp_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274138);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274190);

void func_002741F0(s32 arg0, s32 arg1, s32 arg2) {
    D_003BFB40 = arg0;
    if (arg0 > 0) {
        D_0040EB74 = arg1;
        D_0040EB78 = arg2;
        return;
    }
    D_0040EB74 = 0;
    D_0040EB78 = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274270);

void func_00274350(s32 arg0) {
    D_003BFB3C = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002743D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274540);

void func_00274920(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274928);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002749C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002749C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274CD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274D40);
