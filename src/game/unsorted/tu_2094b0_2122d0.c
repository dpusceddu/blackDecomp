#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_0040F0E0;
extern s32 D_003BE844;
extern s32 func_0035E750();
extern void * D_0040F544;
extern s32 func_0035CBC0();
extern s32 func_0020DF68();
extern M2C_UNK D_003FB5D0;
extern s32 func_00212440();
extern M2C_UNK D_003FB5E0;
extern s32 func_00212490();
extern M2C_UNK D_003FB5F0;
extern s32 func_002124D0();
extern s32 func_0020DF90();

void func_002122D0(void) {
    M2C_FIELD(D_0040F0E0, s32 *, 0x2014C) = (s32) D_003BE844;
}

void func_002122F0(void) {
    D_003BE844 = func_0035E750();
    func_002122D0();
}

void func_00212318(void) {
    func_00212338(0);
}

void func_00212338(void) {
    void *temp_16;

    temp_16 = D_0040F544;
    func_0035CBC0(temp_16 + 0x3820, "OptionsMenu");
    if (M2C_FIELD(temp_16, s8 *, 0x3840) == 0) {
        M2C_FIELD(temp_16, s32 *, 0x388C) = 1;
        return;
    }
    M2C_FIELD(temp_16, s32 *, 0x3884) = 1;
}

s32 func_00212388(s32 arg0) {
    func_0020DF68(arg0, (s32) &D_003FB5D0, (s32) func_00212440);
    func_0020DF68(arg0, (s32) &D_003FB5E0, (s32) func_00212490);
    func_0020DF68(arg0, (s32) &D_003FB5F0, (s32) func_002124D0);
    return 1;
}

s32 func_002123F0(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB5D0);
    func_0020DF90(arg0, (s32) &D_003FB5E0);
    func_0020DF90(arg0, (s32) &D_003FB5F0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00212440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00212490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002124D0);
