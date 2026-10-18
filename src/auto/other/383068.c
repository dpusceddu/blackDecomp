#include "auto/prelude.h"

extern s32 func_00382740();
extern M2C_UNK D_003DC5F8;
extern M2C_UNK D_003DCC20;
extern M2C_UNK D_003DCA38;
extern M2C_UNK D_003DC9F8;
extern M2C_UNK D_003DC9B8;

void * func_00383068(void *arg0) {
    func_00382740();
    M2C_FIELD(arg0, M2C_UNK **, 0x10) = &D_003DC5F8;
    M2C_FIELD(arg0, M2C_UNK **, 0x574) = &D_003DCC20;
    M2C_FIELD(arg0, M2C_UNK **, 0x6A4) = &D_003DCA38;
    M2C_FIELD(arg0, M2C_UNK **, 0x7B4) = &D_003DC9F8;
    M2C_FIELD(arg0, M2C_UNK **, 0x854) = &D_003DC9B8;
    return arg0;
}
