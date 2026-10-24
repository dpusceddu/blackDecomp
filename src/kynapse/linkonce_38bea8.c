#include "ps2/prelude.h"

extern s32 func_002E34B8();
extern s32 (*D_003C87E0)();
extern s32 D_0049B050;
extern s32 func_0038C898();
extern s32 func_00370168();
extern M2C_UNK D_0049B080;
extern s32 D_0049B060;

s32 func_0038BEA8(s32 arg0, s32 arg1) {
    s32 var_2;

    var_2 = func_002E34B8(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

s32 * func_0038BEF8(void) {
    if (D_0049B050 == 0) {
        func_0038C898();
        func_00370168(&D_0049B050, "Q24Kaim17CEntityDefinition", &D_0049B080);
    }
    return &D_0049B050;
}

s32 func_0038BF48(s32 arg0, s32 arg1) {
    s32 var_2;

    var_2 = func_002E34B8(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

s32 * func_0038BF98(void) {
    if (D_0049B060 == 0) {
        func_0038C898();
        func_00370168(&D_0049B060, "Q24Kaim15CTeamDefinition", &D_0049B080);
    }
    return &D_0049B060;
}
