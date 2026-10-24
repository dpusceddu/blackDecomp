#include "ps2/prelude.h"

extern s32 D_003BE808;
extern void * D_0040F0E0;
extern s32 D_003BE80C;
extern s32 D_003BE810;
extern s32 D_003BE814;
extern s32 func_0035E750();
extern s32 func_001EF7B0();
extern void * D_0040F510;
extern s32 D_003BE804;

void func_00210DB8(void) {
    D_003BE808 = (s32) M2C_FIELD(D_0040F0E0, u8 *, 0x20167);
    D_003BE80C = (s32) M2C_FIELD(D_0040F0E0, u8 *, 0x20165);
    D_003BE810 = (s32) M2C_FIELD(D_0040F0E0, u8 *, 0x20168);
    D_003BE814 = (s32) M2C_FIELD(D_0040F0E0, s8 *, 0x20170);
}

void func_00210E00(void) {
    D_003BE808 = func_0035E750();
    func_001EF7B0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x38), D_003BE804);
    M2C_FIELD(D_0040F0E0, s8 *, 0x20167) = (s8) (D_003BE808 != 0);
}

void func_00210E68(void) {
    D_003BE80C = func_0035E750();
    func_001EF7B0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x38), D_003BE804);
    M2C_FIELD(D_0040F0E0, s8 *, 0x20165) = (s8) (D_003BE80C != 0);
}
