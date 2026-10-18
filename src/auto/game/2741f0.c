#include "auto/prelude.h"

extern s32 D_003BFB40;
extern s32 D_0040EB74;
extern s32 D_0040EB78;

void func_002741F0(s32 arg0, s32 arg1, s32 arg2) {
    D_003BFB40 = arg0;
    if (arg0 > 0) {
        D_0040EB74 = arg1;
        D_0040EB78 = arg2;
        return;
    }
    D_0040EB74 = 0;
    D_0040EB78 = 0;
}
