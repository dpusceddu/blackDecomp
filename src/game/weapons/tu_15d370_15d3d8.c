#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/weapons/shot.h"

extern s32 func_0015D620();

void func_0015D3D8(void *arg0) {
    BkShotDeactivatePS2(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_15d370_15d3d8", func_0015D3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_15d370_15d3d8", func_0015D440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_15d370_15d3d8", func_0015D620);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_15d370_15d3d8", func_0015D750);

void func_0015D850(void *arg0, s128 arg1) {
    ((BkMovingShotPS2*)arg0)->endpoint = arg1;
    func_0015D620();
}

