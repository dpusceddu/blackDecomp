#include "rwa_ee/bank.h"

extern s32 D_0040E158;
extern void *func_002A9910(void);
extern void *func_002A9AE8(void);
extern s32 func_002A9E38(void);

s32 func_003131C0(void) {
    s32 result = D_0040E158;
    if (!result) {
        func_002A9910();
        func_002A9AE8();
        result = func_002A9E38();
    }
    return result;
}
