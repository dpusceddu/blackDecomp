#include "auto/prelude.h"

extern s32 func_00173168();
extern s32 D_0040F4D4;
extern void func_00139060();
extern s32 D_0040F514;
extern s32 func_00176F00();
extern void func_0013D680();
extern s32 func_00180610();
extern s32 func_00183AA0();
extern s32 func_00188D08();
extern s32 func_00187F90();
extern s32 func_00182138();
extern s32 func_00185DA8();
extern s32 func_0018ADE0();
extern s32 func_0018D108();
extern s32 func_00183260();

void func_0013D588(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1FC0) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void ***, 0x7C), s32 *, 0x3A4) == 0) {
            func_00173168(D_0040F4D4 + 0x22800, arg0);
        }
        func_00139060(D_0040F514, M2C_FIELD(arg0, void ***, 0x7C));
        M2C_FIELD(arg0, u8 *, 0x1FC0) = 0U;
    }
}

void func_0013D5F8(void *arg0) {
    if (func_00176F00(arg0 + 0x1FCC) & 0xFF) {
        func_0013D680(arg0);
    }
    func_00180610(arg0 + 0xB30);
    func_00183AA0(arg0 + 0x6F0);
    func_00188D08(arg0 + 0x150);
    func_00187F90(arg0 + 0x290);
    func_00182138(arg0 + 0x810);
    func_00185DA8(arg0 + 0x90);
    func_0018ADE0(arg0 + 0xCC0);
    func_0018D108(arg0 + 0xD10);
    func_00183260(arg0 + 0x1EB0);
}
