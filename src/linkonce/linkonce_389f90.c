#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049AA58;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_00389F90(void) {
    if (D_0049AA58 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, "Q24Kaim7CObject");
        }
        func_00370168(&D_0049AA58, "Q24Kaim16CEntityAttribute", &D_0040EBC0);
    }
    return &D_0049AA58;
}
