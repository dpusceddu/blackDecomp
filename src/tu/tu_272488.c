/* Translation unit tu_272488 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

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

/* Assembly between the functions: func_00272C28 (48 bytes), func_00272C58 (104 bytes), func_00272CC0 (296 bytes), func_00272DE8 (696 bytes), func_002730A0 (576 bytes), func_002732E0 (96 bytes), func_00273340 (56 bytes), func_00273378 (104 bytes), func_002733E0 (80 bytes), func_00273430 (136 bytes), func_002734B8 (176 bytes), func_00273568 (224 bytes) ... */

s32 func_00274018(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_2;

    var_2 = arg1 + 8;
    if (arg2 != 0) {
        var_2 = ((var_2 + arg2) - 1) & -arg2;
    }
    return (var_2 * arg0) + arg2;
}

/* Assembly between the functions: func_00274040 (152 bytes) */

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

/* Assembly between the functions: func_00274138 (88 bytes), func_00274190 (96 bytes) */

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

/* Assembly between the functions: func_00274228 (72 bytes), func_00274270 (224 bytes) */

void func_00274350(s32 arg0) {
    D_003BFB3C = arg0;
}

/* Assembly between the functions: func_00274360 (120 bytes), func_002743D8 (360 bytes), func_00274540 (992 bytes) */

void func_00274920(void) {

}
