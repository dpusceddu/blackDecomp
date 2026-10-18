#include "auto/prelude.h"

extern s32 func_001AFDE0();
extern s32 func_001AFE38();
extern s32 func_001C6F10(s32, u64, M2C_UNK, M2C_UNK);
extern void * D_0040F4C0;

void func_001C65E8(void) {
    func_001AFDE0();
}

s32 func_001C6608(s32 arg0) {
    func_001AFE38();
    func_001C6F10(arg0 + 0x70, (u64) ((s64) ((u32) M2C_FIELD(D_0040F4C0, u32 *, 0xD5E0) >> 0xB) << 0x20) >> 0x20, 0, 0xC);
    return 1;
}
