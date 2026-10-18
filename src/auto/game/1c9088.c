#include "auto/prelude.h"

extern s32 func_001C9110();
extern s32 func_001CA0F0(void *);
extern void func_001CA200(void *);

void func_001C9088(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 0x40) != 0) && (M2C_FIELD(arg0, u8 *, 0x178) != 0)) {
        func_001C9110();
        func_001CA0F0(arg0);
        func_001CA200(arg0);
    }
}
