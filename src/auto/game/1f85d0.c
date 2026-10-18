#include "auto/prelude.h"

extern s32 func_001F1C08();
extern void func_00200F00(void *);
extern void func_00200A68(void *arg0);

void func_001F85D0(void *arg0) {
    func_001F1C08();
    M2C_FIELD(arg0, s32 *, 0x1BC) = 0;
    func_00200F00(arg0 + 0x120);
    func_00200A68(arg0 + 0x1C0);
}
