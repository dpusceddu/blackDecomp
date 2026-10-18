#include "auto/prelude.h"

extern void * func_001AC798();
extern s32 D_0040F50C;
extern s32 func_00345510();
extern s32 func_001AD070();
extern s32 func_003492E0();
extern s32 func_003438D8();

void func_001A6EB8(void *arg0) {
    void *temp_2;
    void *temp_4;

    if ((M2C_FIELD(arg0, void **, 0x58) == NULL) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0x54), s32 *, 4) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0xC4) != 2)) {
        temp_2 = func_001AC798(D_0040F50C, arg0);
        M2C_FIELD(arg0, void **, 0x58) = temp_2;
        if (temp_2 != NULL) {
            M2C_FIELD(temp_2, s32 *, 4) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x54), s32 *, 4);
            temp_4 = M2C_FIELD(arg0, void **, 0x58);
            func_00345510(temp_4, arg0, M2C_FIELD(temp_4, s32 *, 4), 1);
            func_001AD070(M2C_FIELD(arg0, void **, 0x58));
            func_003492E0(M2C_FIELD(arg0, void **, 0x58));
            func_003438D8(M2C_FIELD(arg0, void **, 0x58));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x54), void **, 0x9AC) = (void *) M2C_FIELD(arg0, void **, 0x58);
        }
    }
}
