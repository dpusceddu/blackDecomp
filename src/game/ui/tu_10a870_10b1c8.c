#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/frontend_save_dialog.h"
#include "ps2/recovered_types.h"

s32 func_0010B1C8(Recovered_FrontendSaveDialog *arg0) {
    s32 var_3;
    u8 *var_2;

    var_3 = 2;
    var_2 = &arg0->unk_52B;
    do {
        M2C_FIELD(var_2, s8 *, -3) = 0;
        var_3 -= 1;
        M2C_FIELD(var_2, u8 *, 0) = 0;
        var_2 = (u8 *) (((s8 *) var_2) + 1);
    } while (var_3 >= 0);
    arg0->unk_515 = 0;
    arg0->unk_C = 2;
    arg0->unk_20 = 0;
    return 2;
}

#include "game/frontend_save_dialog.h"
#include "ps2/recovered_types.h"

s32 func_0010B200(Recovered_FrontendSaveDialog *arg0) {
    s32 var_3;
    u8 *var_2;

    var_3 = 2;
    var_2 = &arg0->unk_52B;
    do {
        M2C_FIELD(var_2, s8 *, -3) = 0;
        var_3 -= 1;
        M2C_FIELD(var_2, u8 *, 0) = 0;
        var_2 = (u8 *) (((s8 *) var_2) + 1);
    } while (var_3 >= 0);
    arg0->unk_515 = 0;
    arg0->unk_C = 8;
    arg0->unk_24 = 0;
    return 8;
}

#include "game/frontend_save_dialog.h"
#include "ps2/recovered_types.h"

s32 func_0010B238(Recovered_FrontendSaveDialog *arg0) {
    s32 var_3;
    u8 *var_2;

    var_3 = 2;
    var_2 = &arg0->unk_52B;
    do {
        M2C_FIELD(var_2, s8 *, -3) = 0;
        var_3 -= 1;
        M2C_FIELD(var_2, u8 *, 0) = 0;
        var_2 = (u8 *) (((s8 *) var_2) + 1);
    } while (var_3 >= 0);
    arg0->unk_515 = 0;
    arg0->unk_C = 3;
    arg0->unk_18 = 0;
    return 3;
}
