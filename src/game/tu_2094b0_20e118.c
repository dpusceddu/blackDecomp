#include "include_asm.h"

#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * D_0040F0E0;
extern s32 func_001040F8(void *, s32, s32);

void * func_0020E118(void *arg0, void *arg1) {
    u8 temp_4;
    void *var_5;

    temp_4 = M2C_FIELD(D_0040F0E0, u8 *, 0x2020C);
    switch (temp_4) {
    case 0:
        var_5 = (void *)5;
        break;
    case 1:
        var_5 = (arg1 != NULL) ? (void *)7 : (void *)8;
        break;
    case 3:
        var_5 = (arg1 != NULL) ? (void *)0xB : (void *)0xC;
        break;
    case 4:
        var_5 = (arg1 != NULL) ? (void *)0xD : (void *)0xE;
        break;
    case 5:
        var_5 = (arg1 != NULL) ? (void *)9 : (void *)0xA;
        break;
    case 6:
        var_5 = (arg1 != NULL) ? (void *)0xF : (void *)0x10;
        break;
    case 7:
        var_5 = (arg1 != NULL) ? (void *)0x11 : (void *)0x12;
        break;
    case 8:
        var_5 = (arg1 != NULL) ? (void *)0x13 : (void *)0x14;
        break;
    default:
        var_5 = (void *)1;
        break;
    }
    return func_001040F8(D_0040F0E0 + 0x20220, var_5, NULL);
}
