#include "auto/prelude.h"

extern s32 func_00193990();
extern s32 func_00199F70();

void func_0019A578(void **arg0) {
    if ((M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x694), u8 *, 0x3B) ^ 1) != 0) {
        func_00193990(arg0, 1);
        return;
    }
    if (func_00199F70(M2C_FIELD(arg0, s32 *, 8)) == 0) {
        func_00193990(arg0, 0);
    }
}
