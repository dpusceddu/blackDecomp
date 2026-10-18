#include "auto/prelude.h"

extern s32 func_00138390();
extern s32 func_0018D9E8();
extern s32 func_00181AB0();
extern s32 func_0018DCE0();
extern s32 func_0018D4C8();

void func_0013D430(void *arg0, s32 arg1) {
    s32 temp_18;
    void *temp_2;

    temp_18 = arg0 + 0xC94;
    temp_2 = M2C_FIELD(arg0, void **, 0x7C);
    M2C_FIELD(temp_2, s32 *, 0x39C) = arg1;
    func_00138390(M2C_FIELD(temp_2, s32 *, 0x328), temp_2 + 0x3B9, arg1);
    func_0018D9E8(temp_18, arg1);
    func_00181AB0(arg0 + 0xEC0, func_0018DCE0(temp_18));
    func_0018D4C8(arg0 + 0xD10);
}
