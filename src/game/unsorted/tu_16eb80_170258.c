#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK ** func_00171AE8();
extern M2C_UNK D_003DCFE0;
extern void * func_002E4D18();
extern M2C_UNK D_004504E0;
extern M2C_UNK D_00450940;
extern M2C_UNK D_00450198;
extern M2C_UNK D_004503C8;
extern s32 func_002DFB00();
extern M2C_UNK D_003DD048;

M2C_UNK ** func_00170258(M2C_UNK **arg0) {
    func_00171AE8();
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003DCFE0;
    M2C_FIELD(arg0, void **, 0x60) = func_002E4D18(arg0, &D_004504E0);
    M2C_FIELD(arg0, void **, 0x64) = func_002E4D18(arg0, &D_00450940);
    M2C_FIELD(arg0, void **, 0x68) = func_002E4D18(arg0, &D_00450198);
    M2C_FIELD(arg0, void **, 0x6C) = func_002E4D18(arg0, &D_004503C8);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), f32 *, 4) = 2.0f;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x64), f32 *, 4) = 0.7f;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 4) = 0.7f;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x68), f32 *, 4) = 1.7f;
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170258", func_00170320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16eb80_170258", func_00170668);

void func_00170670(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), f32 *, 4) = fparg0;
}

M2C_UNK ** func_00170680(M2C_UNK **arg0) {
    func_002DFB00();
    *arg0 = &D_003DD048;
    return arg0;
}

void func_001706B8(void) {

}
