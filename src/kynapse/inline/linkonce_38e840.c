#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BA50;
extern s32 func_0038D3E0();
extern s32 func_00370168();
extern s32 D_0040EC00;

s32 * func_0038E840(void) {
    if (D_0049BA50 == 0) {
        func_0038D3E0();
        func_00370168(&D_0049BA50, "Q24Kaim18CBrainServiceClass", &D_0040EC00);
    }
    return &D_0049BA50;
}
