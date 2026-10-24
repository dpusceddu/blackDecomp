/* Translation unit kynapse/tu_2e0140 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002EBE90();
extern s32 func_002EBF58();
extern s32 func_002E3928();
extern s32 func_002E3D28();
extern s32 func_002EA898();
extern s32 func_002EAAC8();
extern s32 func_002E2D40();
extern s32 func_002E3578();
extern s32 func_002E3630();
extern s32 func_002E36E8();
extern s32 D_003E7C00;
extern s32 D_003E8010;
extern s32 D_003E6CE8;
extern s32 D_003E8420;

void func_002E1058(void) {
    func_002EBE90();
}

/* Assembly between the functions: func_002E1078 (32 bytes) */

void func_002E1098(void) {
    func_002EBF58();
}

/* Assembly between the functions: func_002E10B8 (32 bytes) */

void func_002E10D8(void) {
    func_002E3928();
}

void func_002E10F8(void) {
    func_002E3D28();
}

/* Assembly between the functions: func_002E1118 (136 bytes), func_002E11A0 (104 bytes) */

void func_002E1208(s32 arg0) {
    if (arg0 != 0) {
        func_002EA898();
    }
}

void func_002E1228(s32 arg0) {
    if (arg0 != 0) {
        func_002EAAC8();
    }
}

/* Assembly between the functions: func_002E1248 (56 bytes), func_002E1280 (48 bytes), func_002E12B0 (208 bytes), func_002E1380 (56 bytes) */

void * func_002E13B8(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *temp_16;

    temp_16 = func_002E2D40(arg0);
    if (arg1 != NULL) {
        func_002E3578(temp_16, arg1);
    }
    if (arg2 != NULL) {
        func_002E3630(temp_16, arg2);
    }
    if (arg3 != NULL) {
        func_002E36E8(temp_16, arg3);
    }
    return temp_16;
}

/* Assembly between the functions: func_002E1438 (56 bytes), func_002E1470 (64 bytes), func_002E14B0 (40 bytes), func_002E14D8 (48 bytes) */

void func_002E1508(void) {
    D_003E7C00 = 0;
}

void func_002E1518(void) {
    D_003E8010 = 0;
}

void func_002E1528(void) {
    D_003E6CE8 = 0;
}

void func_002E1538(void) {
    D_003E8420 = 0;
}
