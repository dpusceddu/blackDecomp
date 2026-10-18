#include "auto/prelude.h"

extern void * D_0040F0E8;
extern s32 func_0027C320();
extern void * D_0040F0E0;
extern s32 func_0010BC08();
extern s32 D_0040F4F0;
extern s32 func_0027C328();

void func_001005A0(void *arg0)
{
 do { M2C_FIELD(arg0, s32 *, 0x10290) = 0x200000; M2C_FIELD(arg0, s32 *, 0x10288) = 0 & 0xFFFFu; } while (0);
  M2C_FIELD(arg0, s32 *, 0x1028C) = 0;
}

void func_001005C0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xA0) = (s32) M2C_FIELD(D_0040F0E8, s32 *, 0x618);
    if (M2C_FIELD(arg0, s32 *, 0) == 0) {
        func_0027C320(arg0, M2C_FIELD(D_0040F0E0, s32 *, 0x2107C));
    }
    func_0010BC08(D_0040F4F0);
    func_0027C328(arg0);
}
