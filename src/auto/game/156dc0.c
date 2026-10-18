#include "auto/prelude.h"

extern s32 func_00155118();
extern void func_0015A830();

s32 func_00156DC0(void *arg0) {
    s32 var_2;
    void *temp_4;
    void *temp_5;

    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xF0), s32 *, 0xC4) == 2) {
        var_2 = 0;
        if (func_00155118(M2C_FIELD(arg0, s32 *, 0xFC), M2C_FIELD(M2C_FIELD(arg0, void **, 0xEC), s32 *, 0x64)) != 0) {
            temp_5 = M2C_FIELD(arg0, void **, 0xF4);
            temp_4 = M2C_FIELD(arg0, void **, 0xEC);
            var_2 = 0;
            if (M2C_FIELD(temp_5, s16 *, 0x18) != M2C_FIELD(temp_4, s32 *, 0x60)) {
                M2C_FIELD(arg0, s8 *, 0x10B) = 0;
                if (M2C_FIELD(temp_4, u8 *, 0xC7) == 0) {
                    M2C_FIELD(arg0, s32 *, 0xD8) = 4;
                } else {
                    M2C_FIELD(arg0, s32 *, 0xD8) = 5;
                    M2C_FIELD(arg0, s8 *, 0x101) = (s8) ((u8) M2C_FIELD(temp_4, s32 *, 0x60) - (u8) M2C_FIELD(temp_5, s16 *, 0x18));
                }
                return 1;
            }
        }
        /* Duplicate return node #8. Try simplifying control flow for better match */
        return var_2;
    }
    func_0015A830(M2C_FIELD(arg0, void **, 0xF4));
    var_2 = 1;
    M2C_FIELD(arg0, s32 *, 0xD8) = 4;
    return var_2;
}
