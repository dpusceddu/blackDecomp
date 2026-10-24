#include "ps2/prelude.h"

extern s32 func_002122A0();
extern s32 func_0020E068();
extern M2C_UNK D_003FB550;
extern M2C_UNK D_003BE844;
extern M2C_UNK D_003FB560;
extern M2C_UNK D_003BE848;
extern s32 func_0020DF68();
extern M2C_UNK D_003FB578;
extern s32 func_002122F0();
extern M2C_UNK D_003FB590;
extern s32 func_00212318();
extern M2C_UNK D_003FB5A8;
extern s32 func_00212338();
extern s32 func_0020DF90();
extern s32 func_0020E0C8();

s32 func_00212190(s32 arg0) {
    func_002122A0();
    func_0020E068(arg0, (s32) &D_003FB550, (s32) &D_003BE844);
    func_0020E068(arg0, (s32) &D_003FB560, (s32) &D_003BE848);
    func_0020DF68(arg0, (s32) &D_003FB578, (s32) func_002122F0);
    func_0020DF68(arg0, (s32) &D_003FB590, (s32) func_00212318);
    func_0020DF68(arg0, (s32) &D_003FB5A8, (s32) func_00212338);
    return 1;
}

s32 func_00212230(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB578);
    func_0020DF90(arg0, (s32) &D_003FB590);
    func_0020DF90(arg0, (s32) &D_003FB5A8);
    func_0020E0C8(arg0, (s32) &D_003FB550);
    func_0020E0C8(arg0, (s32) &D_003FB560);
    return 1;
}
