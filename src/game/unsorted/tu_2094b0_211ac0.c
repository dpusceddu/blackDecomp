#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00211D10();
extern s32 func_0020E068();
extern M2C_UNK D_003FB490;
extern s32 D_003BE82C;
extern M2C_UNK D_003FB218;
extern s32 D_003BE830;
extern M2C_UNK D_003FB228;
extern s32 D_003BE834;
extern s32 func_0020DF68();
extern M2C_UNK D_003FB4A8;
extern s32 func_00211DF0();
extern M2C_UNK D_003FB278;
extern s32 func_00211E60();
extern M2C_UNK D_003FB288;
extern s32 func_00211EB8();
extern M2C_UNK D_003FB4C0;
extern s32 func_00211F70();
extern M2C_UNK D_003FB4D8;
extern s32 func_00211F78();
extern s32 func_0020DCB0();
extern M2C_UNK D_00492210;
extern s32 func_0020DCF8();
extern s32 func_0020DD88();
extern s32 D_003BE820;
extern s32 func_0020DF90();
extern s32 func_0020E0C8();
extern s32 func_0020DD48();
extern s32 func_0020DF30();

s32 func_00211AC0(s32 arg0) {
    func_00211D10();
    func_0020E068(arg0, (s32) &D_003FB490, (s32) &D_003BE82C);
    func_0020E068(arg0, (s32) &D_003FB218, (s32) &D_003BE830);
    func_0020E068(arg0, (s32) &D_003FB228, (s32) &D_003BE834);
    func_0020DF68(arg0, (s32) &D_003FB4A8, (s32) func_00211DF0);
    func_0020DF68(arg0, (s32) &D_003FB278, (s32) func_00211E60);
    func_0020DF68(arg0, (s32) &D_003FB288, (s32) func_00211EB8);
    func_0020DF68(arg0, (s32) &D_003FB4C0, (s32) func_00211F70);
    func_0020DF68(arg0, (s32) &D_003FB4D8, (s32) func_00211F78);
    func_0020DCB0((s32) &D_00492210);
    func_0020DCF8((s32) &D_00492210, (s32) "FONT_TEST_STRING");
    func_0020DD88((s32) &D_00492210);
    D_003BE820 = 0;
    return 1;
}

s32 func_00211BD8(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB4A8);
    func_0020DF90(arg0, (s32) &D_003FB278);
    func_0020DF90(arg0, (s32) &D_003FB288);
    func_0020DF90(arg0, (s32) &D_003FB4C0);
    func_0020DF90(arg0, (s32) &D_003FB4D8);
    func_0020E0C8(arg0, (s32) &D_003FB490);
    func_0020E0C8(arg0, (s32) &D_003FB218);
    func_0020E0C8(arg0, (s32) &D_003FB228);
    func_0020DD48((s32) &D_00492210);
    func_0020DF30((s32) &D_00492210);
    return 1;
}
