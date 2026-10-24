#include "ps2/prelude.h"

extern s32 func_00217818();
extern s32 func_0020E068();
extern M2C_UNK D_003FC2E8;
extern M2C_UNK D_0040EB48;
extern M2C_UNK D_003FC300;
extern M2C_UNK D_0040EB4C;
extern s32 func_0020DF68();
extern M2C_UNK D_003FC318;
extern s32 func_00217A08();
extern s32 func_0020DCB0();
extern M2C_UNK D_00492648;
extern s32 func_0020DCF8();
extern M2C_UNK D_00492658;
extern M2C_UNK D_00492668;
extern M2C_UNK D_00492678;
extern s32 func_0020E0C8();
extern s32 func_0020DF90();
extern s32 func_0020DD48();
extern s32 func_0020DF30();

s32 func_00217670(s32 arg0) {
    func_00217818(0);
    func_0020E068(arg0, (s32) &D_003FC2E8, (s32) &D_0040EB48);
    func_0020E068(arg0, (s32) &D_003FC300, (s32) &D_0040EB4C);
    func_0020DF68(arg0, (s32) &D_003FC318, (s32) func_00217A08);
    func_0020DCB0((s32) &D_00492648);
    func_0020DCF8((s32) &D_00492648, (s32) "FE_CURRENTUNLOCKLEVEL");
    func_0020DCB0((s32) &D_00492658);
    func_0020DCF8((s32) &D_00492658, (s32) "FE_WHATYOUHAVEDONE");
    func_0020DCB0((s32) &D_00492668);
    func_0020DCF8((s32) &D_00492668, (s32) "FE_YOUHAVEUNLOCKED");
    func_0020DCB0((s32) &D_00492678);
    func_0020DCF8((s32) &D_00492678, (s32) "FE_CONGRATULATIONS");
    return 1;
}

s32 func_00217768(s32 arg0) {
    func_0020E0C8(arg0, (s32) &D_003FC2E8);
    func_0020E0C8(arg0, (s32) &D_003FC300);
    func_0020DF90(arg0, (s32) &D_003FC318);
    func_0020DD48((s32) &D_00492648);
    func_0020DF30((s32) &D_00492648);
    func_0020DD48((s32) &D_00492658);
    func_0020DF30((s32) &D_00492658);
    func_0020DD48((s32) &D_00492668);
    func_0020DF30((s32) &D_00492668);
    func_0020DD48((s32) &D_00492678);
    func_0020DF30((s32) &D_00492678);
    return 1;
}
