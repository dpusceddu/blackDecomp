#include "auto/prelude.h"

extern s32 func_00193980();
extern s32 func_00180CC8(void *, M2C_UNK);

void func_001949F8(void **arg0) {
    func_00193980();
    M2C_FIELD(*arg0, s8 *, 0x845) = 1;
    func_00180CC8(*arg0 + 0xB30, 1);
}
