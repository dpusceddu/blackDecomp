#include "auto/prelude.h"

extern s32 func_001984F0();
extern s32 func_00193A08();
extern s32 func_00193990(void **, M2C_UNK);

void func_00199468(void **arg0) {
    func_001984F0();
    if ((func_00193A08(arg0) == 0) && (M2C_FIELD(M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), void **, 0x7C), u8 *, 0x3AA) == 0)) {
        func_00193990(arg0, 0);
    }
}
