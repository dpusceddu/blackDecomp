#include "auto/prelude.h"

extern s32 D_003BE808;
extern void * D_0040F0E0;
extern s32 D_003BE80C;
extern s32 D_003BE810;
extern s32 D_003BE814;

void func_00210DB8(void) {
    D_003BE808 = (s32) M2C_FIELD(D_0040F0E0, u8 *, 0x20167);
    D_003BE80C = (s32) M2C_FIELD(D_0040F0E0, u8 *, 0x20165);
    D_003BE810 = (s32) M2C_FIELD(D_0040F0E0, u8 *, 0x20168);
    D_003BE814 = (s32) M2C_FIELD(D_0040F0E0, s8 *, 0x20170);
}
