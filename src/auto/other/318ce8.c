#include "auto/prelude.h"

extern s32 func_00317C20(M2C_UNK *, s32 *);
extern M2C_UNK D_00456448;

void func_00318CE8(s32 *arg0) {
    if (!(*arg0 & 1)) {
        func_00317C20(&D_00456448, arg0);
    }
}
