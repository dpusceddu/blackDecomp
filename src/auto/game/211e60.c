#include "auto/prelude.h"

extern s32 func_001EF7B0();
extern void * D_0040F510;
extern s32 D_003BE820;
extern s32 D_003BE830;
extern s32 func_0035E750();
extern s32 func_00211D78();
extern s32 D_003BE834;

void func_00211E60(s32 arg0) {
    func_001EF7B0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x38), D_003BE820);
    D_003BE830 = func_0035E750(arg0);
    func_00211D78();
}

void func_00211EB8(s32 arg0) {
    func_001EF7B0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x38), D_003BE820);
    D_003BE834 = func_0035E750(arg0);
    func_00211D78();
}
