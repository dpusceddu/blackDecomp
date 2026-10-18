#include "auto/prelude.h"

extern s32 func_0020DF68();
extern M2C_UNK D_003FBA80;
extern s32 func_00214B90();
extern M2C_UNK D_003FBA98;
extern s32 func_002145E0();
extern M2C_UNK D_003FBAB8;
extern s32 func_00214A20();
extern s32 func_0020DCB0();
extern M2C_UNK D_00492420;
extern M2C_UNK D_00492430;
extern M2C_UNK D_00492440;
extern M2C_UNK D_00492450;
extern s32 func_0020DCF8();
extern M2C_UNK D_003FB980;
extern s32 func_0020DD48();
extern s32 func_0020DF30();
extern s32 func_0020DF90();

s32 func_00214408(s32 arg0) {
    func_0020DF68(arg0, (s32) &D_003FBA80, (s32) func_00214B90);
    func_0020DF68(arg0, (s32) &D_003FBA98, (s32) func_002145E0);
    func_0020DF68(arg0, (s32) &D_003FBAB8, (s32) func_00214A20);
    func_0020DCB0((s32) &D_00492420);
    func_0020DCB0((s32) &D_00492430);
    func_0020DCB0((s32) &D_00492440);
    func_0020DCB0((s32) &D_00492450);
    func_0020DCF8((s32) &D_00492420, (s32) "FE_MEDALAWARDED");
    func_0020DCF8((s32) &D_00492430, (s32) "FE_CHALLENGERESULTS");
    func_0020DCF8((s32) &D_00492440, (s32) &D_003FB980);
    func_0020DCF8((s32) &D_00492450, (s32) "FE_CHALLENGERESULT");
    return 1;
}

s32 func_00214508(s32 arg0) {
    func_0020DD48((s32) &D_00492420);
    func_0020DD48((s32) &D_00492430);
    func_0020DD48((s32) &D_00492440);
    func_0020DD48((s32) &D_00492450);
    func_0020DF30((s32) &D_00492420);
    func_0020DF30((s32) &D_00492430);
    func_0020DF30((s32) &D_00492440);
    func_0020DF30((s32) &D_00492450);
    func_0020DF90(arg0, (s32) &D_003FBA80);
    func_0020DF90(arg0, (s32) &D_003FBA98);
    func_0020DF90(arg0, (s32) &D_003FBAB8);
    return 1;
}
