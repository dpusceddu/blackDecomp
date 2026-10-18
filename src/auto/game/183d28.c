#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_0018DDD8();
extern s32 func_00189BF8();
extern s32 func_00189250();
extern s32 func_00189AD0();
extern s32 func_0018C088();
extern s32 func_00181B08();

void func_00183D28(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    void *temp_5;

    if (arg2 != 0) {
        temp_5 = M2C_FIELD(arg0, u32 *, 0);
        if ((M2C_FIELD(arg2, s32 *, 0x3A4) != M2C_FIELD(M2C_FIELD(temp_5, void **, 0x7C), s32 *, 0x3A4)) && ((M2C_FIELD(arg2, s32 *, 0xC4) == 2) || (func_0018DDD8((s32) (temp_5 + 0xC94)) != 0)) && (arg1 > 0) && (arg1 < 4) && (func_00189BF8((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), M2C_FIELD(arg2, s32 *, 0x380)) != 0) && (func_00189250((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), M2C_FIELD(arg2, s32 *, 0x380)) != 0)) {
            func_00189AD0((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), arg2);
            func_0018C088((s32) sp, arg2);
            func_00181B08((s32) (M2C_FIELD(arg0, u32 *, 0) + 0xEC0), (s32) sp);
        }
    }
}
