#include "auto/prelude.h"

extern s32 func_00193980();
extern s32 func_00182380();
extern void * func_001830D0();
extern void * func_00183110();
extern s32 func_001828C0();

void func_00197518(s32 *arg0) {
    s32 temp_16;
    void *temp_2;

    func_00193980();
    temp_16 = *arg0;
    func_00182380(temp_16 + 0x810, M2C_FIELD(func_001830D0(temp_16 + 0xD10), s128 *, 0x20), 0);
    if (M2C_FIELD(func_001830D0(*arg0 + 0xD10), f32 *, 0x30) <= 0.0f) {
        temp_2 = func_00183110(*arg0 + 0xD10);
        if (temp_2 != NULL) {
            func_001828C0(*arg0 + 0x810, M2C_FIELD(temp_2, s128 *, 0x20));
        }
    }
}
