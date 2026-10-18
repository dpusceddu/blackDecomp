#include "auto/prelude.h"

extern s32 func_0020C4B8();
extern s32 func_0020D188();
extern void * D_0040F544;
extern s32 func_0020D1C8();

s32 func_0020C448(void *arg0) {
    s32 temp_2;

    if (!(M2C_FIELD(arg0, s32 *, 0x58) & 0x406)) {
        func_0020C4B8(M2C_FIELD(arg0, s32 *, 0x5C), 0);
    }
    temp_2 = func_0020D188(D_0040F544 + 0xE90, 0x50);
    func_0020D1C8(temp_2, arg0);
    return temp_2;
}
