#include "auto/prelude.h"

extern s32 func_0018E4C0();

s32 func_0018FFC0(void *arg0, s32 *arg1) {
    void *temp_3;

    func_0018E4C0();
    if (*arg1 == 2) {
        temp_3 = M2C_FIELD(arg0, void **, 0x10);
        M2C_FIELD(temp_3, M2C_UNK (**)(void *, M2C_UNK), 0x84)(arg0 + M2C_FIELD(temp_3, s16 *, 0x80), 3);
    }
    return 0;
}
