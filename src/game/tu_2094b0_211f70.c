#include "auto/prelude.h"

extern s32 func_00212048();
extern s32 func_0020E068();
extern M2C_UNK D_003FB500;
extern s32 D_003BE83C;
extern s32 D_003BE840;
extern s32 func_0020DF68();
extern M2C_UNK D_003FB528;
extern s32 func_002120F0();
extern M2C_UNK D_003FB540;
extern s32 func_00212140();
extern s32 func_0020DF90();
extern s32 func_0020E0C8();

void func_00211F70(void) {

}

void func_00211F78(void) {

}

s32 func_00211F80(s32 arg0) {
    func_00212048();
    func_0020E068(arg0, (s32) &D_003FB500, (s32) &D_003BE83C);
    func_0020E068(arg0, (s32) "FEGammaLevel", (s32) &D_003BE840);
    func_0020DF68(arg0, (s32) &D_003FB528, (s32) func_002120F0);
    func_0020DF68(arg0, (s32) &D_003FB540, (s32) func_00212140);
    return 1;
}

s32 func_00212008(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB528);
    func_0020E0C8(arg0, (s32) &D_003FB500);
    return 1;
}
