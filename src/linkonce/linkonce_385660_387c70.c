#include "ps2/prelude.h"

extern s32 func_00250058(s32, s32);
extern s32 D_0043DEE0;
extern s32 func_0035C6EC(s32, M2C_UNK, s32);

void func_00387C70(void *arg0) {
    s32 temp_2;

    temp_2 = func_00250058(D_0043DEE0, M2C_FIELD(arg0, s32 *, 0) * 8);
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    func_0035C6EC(temp_2, 0, M2C_FIELD(arg0, s32 *, 0) * 8);
}
