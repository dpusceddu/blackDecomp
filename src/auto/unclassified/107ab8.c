#include "auto/prelude.h"

extern s32 func_00274F58(void *, s32);
extern s32 func_00274F70(void *);

void func_00107AB8(void *arg0, s32 arg1) {
    void *temp_2;

    M2C_FIELD(arg0, s32 *, 0x3B4) = arg1;
    temp_2 = arg0 + ((arg1 * 0x24) + 4);
    M2C_FIELD(arg0, void **, 0x3AC) = temp_2;
    func_00274F58(temp_2, 0x80);
    func_00274F70(M2C_FIELD(arg0, void **, 0x3AC));
}

void func_00107B08(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3AC) = 0;
    M2C_FIELD(arg0, s32 *, 0x3B4) = -1;
}
