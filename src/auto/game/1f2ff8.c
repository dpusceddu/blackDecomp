#include "auto/prelude.h"

extern s32 func_001F1E20();
extern M2C_UNK D_003F9558;
extern M2C_UNK D_003F9570;
extern M2C_UNK D_003F9580;

s32 func_001F2FF8(s32 arg0) {
    func_001F1E20(arg0, (s32) &D_003F9558);
    func_001F1E20(arg0, (s32) &D_003F9570);
    func_001F1E20(arg0, (s32) &D_003F9580);
    return 1;
}
