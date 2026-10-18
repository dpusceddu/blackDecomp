#include "auto/prelude.h"

extern s32 func_00185C38();
extern s32 func_001897E8();

s32 func_0018FB88(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 temp_7;
    s32 var_2;
    void *temp_6;

    temp_6 = M2C_FIELD(arg0, void **, 4);
    temp_5 = M2C_FIELD(arg1, s32 *, 0x380);
    temp_7 = 1 << temp_5;
    var_2 = M2C_FIELD(M2C_FIELD(temp_6, void **, 0x7C), s32 *, 0x3A4);
    if (M2C_FIELD(arg1, s32 *, 0x3A4) != var_2) {
        var_2 = M2C_FIELD(arg1, s32 *, 0x38C);
        if (var_2 == 0) {
            var_2 = M2C_FIELD(temp_6, s32 *, 0x274) & temp_7;
            if (var_2 != temp_7) {
                var_2 = func_00185C38((s32) (temp_6 + 0x6F0), temp_5);
                if (var_2 != 0) {
                    var_2 = func_001897E8((s32) (M2C_FIELD(arg0, void **, 4) + 0x150), M2C_FIELD(arg1, s32 *, 0x380), 0);
                }
            }
        }
    }
    return var_2;
}
