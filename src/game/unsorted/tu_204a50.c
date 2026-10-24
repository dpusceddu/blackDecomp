#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_002071C8(void *arg0);
extern s32 func_00207938(void *arg0);
extern s32 func_002789C0();
extern s32 D_003BDCC0;
extern s32 func_00278EA0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00204A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00204AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00204D80);

void func_00204EA0(void) {
    func_00204F90();
}

s32 func_00204EC0(void *arg0) {
    func_002071C8(M2C_FIELD(arg0, void **, 0x60));
    func_002071C8(M2C_FIELD(arg0, void **, 0x60) + 0x1C);
    func_00207938(M2C_FIELD(arg0, void **, 0x64));
    return 1;
}

s32 func_00204F00(s32 arg0) {
    return func_002789C0(arg0, 0xA, 0x1E, 0x1E, D_003BDCC0, 0x1880);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00204F30);

void func_00204F90(void) {
    func_00278EA0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00204FB0);
