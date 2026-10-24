#include "ps2/prelude.h"

extern s32 func_00317C20(M2C_UNK *, void *);
extern M2C_UNK D_00455F30;

void func_00310940(void *arg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x10) & 1)) {
        func_00317C20(&D_00455F30, arg0);
    }
}
