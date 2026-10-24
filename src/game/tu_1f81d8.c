#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F1C08();
extern void func_00200A68(void *arg0);

void func_001F81D8(void *arg0) {
    func_001F1C08();
    func_00200A68(arg0 + 0x20);
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
}
