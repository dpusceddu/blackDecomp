#include "auto/prelude.h"

extern void * func_001AFD80();

u8 func_00152108(void *arg0) {
    void *temp_2;
    void *temp_2_2;

    temp_2_2 = func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
    if (temp_2_2 == NULL) {
        return 0U;
    }
    temp_2 = M2C_FIELD(temp_2_2, void **, 0xC0);
    if (temp_2 == NULL) {
        return 0U;
    }
    return M2C_FIELD(*M2C_FIELD(temp_2, void ***, 0x24), u8 *, 4);
}
