#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_0013EC10(void* self, s32 mode);

void func_001306A0(void* self) {
    func_0013EC10(self, 0);
    M2C_FIELD(self, s8*, 0x102) = 0;
}
