#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049B508;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406398;
extern s32 func_00370168();

s32 * func_0038CCB0(void) {
    if (D_0049B508 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406398);
        }
        func_00370168(&D_0049B508, "Q34Kaimt8CVarList1ZPQ24Kaim5CTeam5CCell", &D_0040EBC0);
    }
    return &D_0049B508;
}
