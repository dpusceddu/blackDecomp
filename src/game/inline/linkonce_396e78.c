#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BFA0;
extern s32 func_00396EC8();
extern s32 func_00370168();
extern M2C_UNK D_0049BFB0;

s32 * func_00396E78(void) {
    if (D_0049BFA0 == 0) {
        func_00396EC8();
        func_00370168(&D_0049BFA0, "Q24Kaim14CXmlDataReader", &D_0049BFB0);
    }
    return &D_0049BFA0;
}
