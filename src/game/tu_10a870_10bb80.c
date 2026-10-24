#include "ps2/prelude.h"

extern s32 func_00108458();
extern void * D_0040F4C4;

s32 func_0010BB80(void) {
    return func_00108458(D_0040F4C4, 0xD, 0) != 0;
}
