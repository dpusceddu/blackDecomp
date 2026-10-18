#include "auto/prelude.h"

extern s32 func_001E8900(s32);
extern void * D_0040F510;

s32 func_00105CB8(void) {
    return func_001E8900(M2C_FIELD(D_0040F510, s32 *, 0xCBD8)) != 0;
}

void func_00105CE8(void) {

}
