#include "auto/prelude.h"

extern s32 func_00170680();
extern M2C_UNK D_003DD018;
extern s32 func_002DFE40();
extern M2C_UNK D_0044F7C0;
extern M2C_UNK D_0044F9F0;

void * func_00170090(void *arg0) {
    func_00170680();
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003DD018;
    M2C_FIELD(arg0, s32 *, 0xC) = func_002DFE40(arg0, &D_0044F7C0);
    M2C_FIELD(arg0, s32 *, 0x10) = func_002DFE40(arg0, &D_0044F9F0);
    return arg0;
}

void func_001700F0(void) {

}
