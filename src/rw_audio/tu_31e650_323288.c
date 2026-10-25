#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00312C48();
extern s32 func_00312C70();

s32 func_00323288(s32 arg0) {
    return func_00312C48(arg0, 0x30810);
}

void func_003232A8(void) {
    func_00312C70();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650_323288", func_003232C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650_323288", func_00323458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650_323288", func_00323688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650_323288", func_00323730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650_323288", func_00323758);
