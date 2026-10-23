#include "auto/prelude.h"

extern s32 func_0018E458();
extern s32 func_0018DDD8();
extern s32 func_001726A0(s32, s32);
extern s32 func_0013D400(s32);
extern s32 func_0018F548(void *);

void func_0018F4E8(void *arg0) {
    func_0018E458();
    M2C_FIELD(arg0, s8 *, 0x16) = 0;
    if ((func_0018DDD8(M2C_FIELD(arg0, s32 *, 4) + 0xC94) == 0) || (func_001726A0(func_0013D400(M2C_FIELD(arg0, s32 *, 4)), M2C_FIELD(arg0, s32 *, 4)) != 0)) {
        func_0018F548(arg0);
    }
}
