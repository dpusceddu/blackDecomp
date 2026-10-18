#include "auto/prelude.h"

extern u8 D_0040EAE0;
extern s32 func_001034B0(void *, void *);
extern void * D_0040F0E0;
extern void * D_0040EADC;

void func_00103DB0(s32 arg0) {
    if ((arg0 == 0) || (D_0040EAE0 != 0)) {
        func_001034B0(D_0040F0E0, D_0040EADC);
    }
}
