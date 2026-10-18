#include "auto/prelude.h"

extern s32 (*D_003BFAB0)();
extern void * D_0043DC18;
extern void * D_0043DDF8;

void func_00249958(void *arg0, u32 *arg1) {
    s32 var_16;
    void *temp_2;
    void *temp_5;
    void *temp_5_2;
    void *temp_5_3;

    temp_5 = M2C_FIELD(arg0, void **, 8);
    if (temp_5 != NULL) {
        D_003BFAB0(arg1, temp_5, D_0043DC18 + 8);
    }
    temp_5_2 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_5_2 != NULL) {
        D_003BFAB0(arg1, temp_5_2, D_0043DDF8 + 8);
    }
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        var_16 = 0;
        if (M2C_FIELD(arg0, s32 *, 0) > 0) {
            do {
                temp_2 = (var_16 * 8) + M2C_FIELD(arg0, s32 *, 4);
                temp_5_3 = M2C_FIELD(temp_2, void **, 4);
                if (temp_5_3 != NULL) {
                    D_003BFAB0(arg1, temp_5_3, M2C_FIELD(temp_2, s32 *, 0) + 8);
                }
                var_16 += 1;
            } while (var_16 < M2C_FIELD(arg0, s32 *, 0));
        }
    }
}
