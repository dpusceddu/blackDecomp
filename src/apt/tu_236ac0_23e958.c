#include "auto/prelude.h"

extern s32 func_00386668();
extern s32 func_00386698();

void func_0023E958(void **arg0) {
    s32 *temp_17;
    s32 *var_16;
    void *temp_2;

    var_16 = M2C_FIELD(*arg0, s32 **, 8);
    if (var_16 != NULL) {
        do {
            temp_17 = M2C_FIELD(var_16, s32 **, 8);
            if (var_16 != NULL) {
                temp_2 = M2C_FIELD(var_16, void **, 4);
                M2C_FIELD(var_16, s32 *, 0) = 0;
                M2C_FIELD(var_16, s32 **, 8) = NULL;
                M2C_FIELD(var_16, s32 *, 0xC) = 0;
                if (temp_2 != NULL) {
                    M2C_FIELD(temp_2, s32 *, 0) = 0;
                    M2C_FIELD(temp_2, s32 *, 4) = 0;
                    M2C_FIELD(temp_2, s32 *, 8) = 0;
                    func_00386668(temp_2, 0x1C);
                    M2C_FIELD(var_16, void **, 4) = NULL;
                }
                func_00386698(var_16, 0x14);
            }
            var_16 = temp_17;
        } while (var_16 != NULL);
    }
}
