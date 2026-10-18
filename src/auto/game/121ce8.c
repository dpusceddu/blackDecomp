#include "auto/prelude.h"

extern s32 func_001033A0();
extern void * D_0040F0E0;
extern s16 func_00122368();
extern void ** D_0040F4DC;

s16 func_00121CE8(void *arg0) {
    s32 temp_3;
    void *temp_2;

    temp_2 = func_001033A0(D_0040F0E0, M2C_FIELD(D_0040F0E0, u8 *, 0x2020C), M2C_FIELD(D_0040F0E0, u8 *, 0x2020E));
    temp_3 = M2C_FIELD(temp_2, s32 *, 0);
    switch (temp_3) {                               /* irregular */
    case 1:
        if (M2C_FIELD(temp_2, s32 *, 4) != temp_3) {
            return func_00122368(D_0040F4DC, 0x20);
        }
    default:
        return (s16) (M2C_FIELD(arg0, u16 *, 0x1C) + M2C_FIELD(arg0, u16 *, 0x1E));
    case 2:
        return M2C_FIELD(arg0, s16 *, 0x44);
    }
}
