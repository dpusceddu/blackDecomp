#include "auto/prelude.h"

extern s32 func_001E5AF8();
extern s32 func_001E5DD0(void *);

void func_001E5900(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x798) == 8) {
        func_001E5AF8();
        func_001E5DD0(arg0);
    }
}
