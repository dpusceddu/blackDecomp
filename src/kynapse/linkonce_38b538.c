#include "ps2/prelude.h"

extern s32 D_00451208;
extern M2C_UNK * func_0038B690(M2C_UNK *arg0);
extern M2C_UNK D_0049AC08;
extern s32 func_0035E690(M2C_UNK *);
extern M2C_UNK func_002DFF00;

M2C_UNK * func_0038B538(void) {
    if (D_00451208 == 0) {
        func_0038B690(&D_0049AC08);
        D_00451208 = 1;
        func_0035E690(&func_002DFF00);
    }
    return &D_0049AC08;
}
