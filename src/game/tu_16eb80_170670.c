#include "ps2/prelude.h"

extern s32 func_002DFB00();
extern M2C_UNK D_003DD048;

void func_00170670(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), f32 *, 4) = fparg0;
}

M2C_UNK ** func_00170680(M2C_UNK **arg0) {
    func_002DFB00();
    *arg0 = &D_003DD048;
    return arg0;
}

void func_001706B8(void) {

}
