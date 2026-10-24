#include "ps2/prelude.h"

extern s32 func_002123F0(s32);
extern s32 func_001B0A20(void *);
extern void * D_0040F4C0;

void func_001217C8(void) {

}

s32 func_001217D0(s32 arg0) {
    func_002123F0(arg0 + 0xC);
    func_001B0A20(D_0040F4C0 + 0xD290);
    return 1;
}
