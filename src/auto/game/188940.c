#include "auto/prelude.h"

extern void * func_0015D2A8();
extern s32 D_0040F4E0;
extern void * D_0040F4D0;
extern s32 func_00158088();
extern s32 func_00173640(void **, f32);
extern s32 func_00173610();

void func_00188940(void *arg0, s32 arg1) {
    s8 *temp_17;
    void *temp_18;
    void *temp_3;

    if (arg1 != 0) {
        temp_3 = M2C_FIELD(arg0, void **, 0x3AC);
        temp_17 = M2C_FIELD(M2C_FIELD(temp_3, void **, 0x7C), s8 **, 0x2A4);
        if (temp_17 == NULL) {
            M2C_FIELD(temp_3, s8 *, 0x6CD) = 0;
            return;
        }
        temp_18 = func_0015D2A8(D_0040F4E0, *temp_17);
        M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 4) + M2C_FIELD(D_0040F4D0, f32 *, 0x1C));
        if (M2C_FIELD(temp_18, u8 *, 0x10) == 0) {
            if (func_00158088(temp_17) != 0) {
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x3AC), s8 *, 0x6CD) = 0;
                func_00173640(arg0 + 0x10, M2C_FIELD(temp_18, f32 *, 0xC));
                return;
            }
            if (func_00173610(arg0 + 0x10) != 0) {
                goto block_7;
            }
        } else {
block_7:
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x3AC), s8 *, 0x6CD) = 1;
        }
    } else {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x3AC), s8 *, 0x6CD) = 0;
    }
}
