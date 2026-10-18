#include "auto/prelude.h"

extern void func_0018BFE8();
extern s32 func_00181B08();

void func_00185870(s32 *arg0) {
    u8 sp[24];
    func_0018BFE8(sp);
    func_00181B08(*arg0 + 0xEC0, sp);
}
