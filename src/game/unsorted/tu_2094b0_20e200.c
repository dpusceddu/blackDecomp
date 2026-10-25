#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0020DF90();
extern M2C_UNK D_003FAB48;
extern M2C_UNK D_003FAB50;
extern M2C_UNK D_003FAB60;
extern M2C_UNK D_003FAB88;
extern M2C_UNK D_003FAB90;
extern M2C_UNK D_003FABA0;
extern M2C_UNK D_003FABB0;
extern M2C_UNK D_003FABC0;
extern M2C_UNK D_003FABD8;
extern s32 D_003BE7A8;
extern s32 D_003BE7A4;

#include "ps2/recovered_types.h"
extern s32 func_0020DF68(void *, s32, s32);
extern M2C_UNK D_003FAB48;
extern s32 func_0020E630(s32);
extern M2C_UNK D_003FAB50;
extern s32 func_0020E678(s32);
extern M2C_UNK D_003FAB60;
extern s32 func_0020E720();
extern s32 func_0020E6C8();
extern M2C_UNK D_003FAB88;
extern s32 func_0020E768(s32);
extern M2C_UNK D_003FAB90;
extern s32 func_0020E7A8(s32);
extern M2C_UNK D_003FABA0;
extern s32 func_0020E7F8();
extern M2C_UNK D_003FABB0;
extern s32 func_0020E840();
extern M2C_UNK D_003FABC0;
extern s32 func_0020E8C0();
extern M2C_UNK D_003FABD8;
extern s32 func_0020E880();
extern s32 func_0020DCB0(s32 *);
extern s32 D_00491FA0;
extern s32 func_0020DCF8(void *, void *);
extern M2C_UNK D_003FABF0;
extern s32 D_003BE7A8;

s32 func_0020E200(void *arg0) {
    func_0020DF68(arg0, (s32) &D_003FAB48, (s32) func_0020E630);
    func_0020DF68(arg0, (s32) &D_003FAB50, (s32) func_0020E678);
    func_0020DF68(arg0, (s32) &D_003FAB60, (s32) func_0020E720);
    func_0020DF68(arg0, (s32) "Unset480pAndFinish", (s32) func_0020E6C8);
    func_0020DF68(arg0, (s32) &D_003FAB88, (s32) func_0020E768);
    func_0020DF68(arg0, (s32) &D_003FAB90, (s32) func_0020E7A8);
    func_0020DF68(arg0, (s32) &D_003FABA0, (s32) func_0020E7F8);
    func_0020DF68(arg0, (s32) &D_003FABB0, (s32) func_0020E840);
    func_0020DF68(arg0, (s32) &D_003FABC0, (s32) func_0020E8C0);
    func_0020DF68(arg0, (s32) &D_003FABD8, (s32) func_0020E880);
    func_0020DCB0(&D_00491FA0);
    func_0020DCF8(&D_00491FA0, &D_003FABF0);
    D_003BE7A8 = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20e200", func_0020E338);

s32 func_0020E4A8(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FAB48);
    func_0020DF90(arg0, (s32) &D_003FAB50);
    func_0020DF90(arg0, (s32) &D_003FAB60);
    func_0020DF90(arg0, (s32) &D_003FAB88);
    func_0020DF90(arg0, (s32) &D_003FAB90);
    func_0020DF90(arg0, (s32) &D_003FABA0);
    func_0020DF90(arg0, (s32) &D_003FABB0);
    func_0020DF90(arg0, (s32) &D_003FABC0);
    func_0020DF90(arg0, (s32) &D_003FABD8);
    D_003BE7A8 = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20e200", func_0020E560);

s32 func_0020E620(void) {
    return D_003BE7A4 != 0;
}
