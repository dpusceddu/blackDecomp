#include "auto/prelude.h"

extern s32 func_00193980();
extern s32 func_00193988();
extern s32 func_001825B0(void *);

void func_00198568(void) {
    func_00193980();
}

void func_00198588(s32 *arg0) {
    func_00193988();
    func_001825B0(*arg0 + 0x810);
}
