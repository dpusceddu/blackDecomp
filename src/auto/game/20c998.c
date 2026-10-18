#include "auto/prelude.h"

extern s32 func_00279940();
extern void * D_0040F544;
extern s32 func_002798B0();
extern s32 func_00279930();

void func_0020C998(s32 arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 0:
        func_00279940(D_0040F544 + 0x36F0, arg0, D_0040F544 + 0x3740);
        return;
    case 1:
        func_002798B0(D_0040F544 + 0x36F0, arg0, D_0040F544 + 0x3740);
        break;
    case -1:
        func_00279930(D_0040F544 + 0x36F0, arg0, D_0040F544 + 0x3740);
        break;
    }
}
