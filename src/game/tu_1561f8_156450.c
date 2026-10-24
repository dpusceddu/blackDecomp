#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_Instance.h"
#include "game/layouts/Recovered_WeaponManagerMethods.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_0015D198(Recovered_WeaponManagerMethods *, Recovered_Instance *);
extern void ** D_0040F4E0;
extern void * func_0020BC00(void *, s32);
extern void * D_0040F544;
extern s32 func_00209FF8(void *, s32);
extern s32 func_0027C278(s32);
extern M2C_UNK D_003F4C40;

s32 func_00156450(void *arg0) {
    void *temp_16;

    func_0015D198(D_0040F4E0, M2C_FIELD(arg0, s32 *, 0xF4));
    func_0015D198(D_0040F4E0, M2C_FIELD(arg0, s32 *, 0xF8));
    temp_16 = func_0020BC00(D_0040F544, 2);
    func_00209FF8(temp_16, func_0027C278((s32) &D_003F4C40));
    M2C_FIELD(arg0, s32 *, 0xF0) = 0;
    M2C_FIELD(arg0, s32 *, 0xF4) = 0;
    M2C_FIELD(arg0, s32 *, 0xF8) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001564D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00156A20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00156A88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00156CA0);
