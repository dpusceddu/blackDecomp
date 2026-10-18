#include "auto/prelude.h"

extern s32 func_00105228();
extern void * D_0040F0E0;

void func_001067A0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) | 2);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), u8 *, 0x35) != 0) {
        func_00105228(D_0040F0E0 + 0x20220, 5);
        return;
    }
    func_00105228(D_0040F0E0 + 0x20220, 4);
}
