#include "ps2/prelude.h"

extern s32 D_0049BE20;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00408888;
extern s32 func_00370168();

s32 * func_00394370(void) {
    if (D_0049BE20 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00408888);
        }
        func_00370168(&D_0049BE20, "Q34Kaimt8CVarList1ZQ34Kaim20CGapDynamicAvoidance16CCandidateTarget5CCell", &D_0040EBC0);
    }
    return &D_0049BE20;
}
