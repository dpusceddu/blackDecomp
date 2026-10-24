#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0040EB00;
extern s32 D_0040EB04;
extern s32 D_0040EB18;
extern s32 func_00108328();
extern s32 D_0040F4C4;

void func_001CFF78(void) {
    D_0040EB00 = -1;
    D_0040EB04 = -1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CFF90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CFFB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D0010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D0A68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D0AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D0B20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D0D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D0D80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D0EA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D0EF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D1188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D1218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D1268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D14E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D1A30);

s32 func_001D1B28(void) {
    return 1;
}

void func_001D1B30(void) {

}

void func_001D1B38(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D1B40);

void func_001D1D18(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D1D20);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0042A1E0;
extern M2C_UNK D_004199E0;

s32 * func_001D1DC8(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7) {
    s32 *temp_2;
    void *temp_3;

    temp_3 = arg0 + 0xF;
    temp_2 = D_0042A1E0 + ((s32) &D_004199E0);
    D_0042A1E0 += ((s32) (((s32) temp_3 > -1) ? temp_3 : (arg0 + 0x1E)) >> 4) * 0x10;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D1E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D21F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D22C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D2438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D24F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D28D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D2CC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D2E30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D2F18);

s32 func_001D3040(void) {
    D_0040EB18 = func_00108328(D_0040F4C4, "bulletholes");
    return 1;
}
