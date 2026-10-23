#include "auto/prelude.h"

extern s32 func_00188F10();
extern s32 func_0018AB08();
extern void * func_0013D400();
extern s32 func_001897E8();

void func_0018A548(s32 *arg0) {
    s32 temp_5;
    void *temp_2;

    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), s32 *, 0x1EE0) != 0) && ((func_00188F10() == 0) || (func_0018AB08(arg0) == 0))) {
        temp_2 = func_0013D400(M2C_FIELD(arg0, void **, 0x130));
        if (temp_2 != NULL) {
            temp_5 = M2C_FIELD(temp_2, s32 *, 0x1C);
            if (temp_5 != -1) {
                func_001897E8(arg0, temp_5, 0);
            }
        }
    }
}
