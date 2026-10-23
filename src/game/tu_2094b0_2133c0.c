#include "auto/prelude.h"

extern s32 func_0020DF68();
extern M2C_UNK D_003FB780;
extern s32 func_002134F0();
extern s32 func_0020DCB0();
extern M2C_UNK D_00492300;
extern M2C_UNK D_00492310;
extern M2C_UNK D_00492320;
extern s32 func_0020DCF8();
extern s32 func_0020DF90();
extern s32 func_0020DD48();
extern s32 func_0020DF30();

s32 func_002133C0(s32 arg0) {
    func_0020DF68(arg0, (s32) &D_003FB780, (s32) func_002134F0);
    func_0020DCB0((s32) &D_00492300);
    func_0020DCB0((s32) &D_00492310);
    func_0020DCB0((s32) &D_00492320);
    func_0020DCF8((s32) &D_00492300, (s32) "FE_RANKCHANGE");
    func_0020DCF8((s32) &D_00492310, (s32) "FE_NEWRANKMSG");
    func_0020DCF8((s32) &D_00492320, (s32) "FE_NEWRANKNAME");
    return 1;
}

s32 func_00213468(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB780);
    func_0020DD48((s32) &D_00492300);
    func_0020DD48((s32) &D_00492310);
    func_0020DD48((s32) &D_00492320);
    func_0020DF30((s32) &D_00492300);
    func_0020DF30((s32) &D_00492310);
    func_0020DF30((s32) &D_00492320);
    return 1;
}
