#include "auto/prelude.h"

extern s32 * func_0018A678();
extern s32 func_00176F00();
extern void func_00186E68();
extern s32 func_00186988();
extern s32 func_00185FF0();
extern void func_00186218();

void func_00185DA8(void *arg0) {
    s32 *temp_17;

    temp_17 = func_0018A678(M2C_FIELD(arg0, s32 *, 0xA4) + 0x150);
    if (func_00176F00(M2C_FIELD(arg0, s32 *, 0xA4) + 0x1FCC) & 0xFF) {
        func_00186E68(arg0, temp_17);
    }
    func_00186988(arg0, temp_17);
    func_00185FF0(arg0, temp_17, M2C_FIELD(arg0, u8 *, 0x76) ^ 1);
    func_00186218(arg0, temp_17, M2C_FIELD(arg0, u8 *, 0x82) ^ 1);
}
