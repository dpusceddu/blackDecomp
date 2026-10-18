#include "auto/prelude.h"

extern s32 func_0020DC60();
extern s32 func_00275340(void *);
extern s32 func_00275398(s32, s32, void *);

void func_0020DE78(s32 *arg0, void *arg1) {
    func_0020DC60(arg0, func_00275340(arg1));
    func_00275398(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 0), arg1);
}
