#include "auto/prelude.h"

extern s32 func_00193980();
extern s32 func_001A0C18(void *);

void func_001A0B88(void *arg0) {
    func_00193980();
    M2C_FIELD(arg0, s32 *, 8) = 2;
    func_001A0C18(arg0);
}
