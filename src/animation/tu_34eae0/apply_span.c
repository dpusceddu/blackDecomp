#ifdef NONMATCHING
// Unmatched: flag condition scheduling and float argument allocation differ.
#include "auto/prelude.h"
#define TYPES_GHIDRA_NO_PROTOTYPES
#include "recovered/Recovered_AnimationGraphNode.h"
#include "recovered/Recovered_AnimationParameters.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

extern s32 func_0034ED88(f32);
extern f32 * func_003500E0(Recovered_AnimationParameters *, s32);

f32 func_0034EDB8(f32 fparg0, f32 fparg1, f32 fparg2, s32 *arg0, Recovered_AnimationGraphNode *arg1, Recovered_AnimationParameters *arg2, u32 arg3) {
    f32 var_f21;
    s32 temp_16;
    s32 var_2;

    var_f21 = fparg2;
    if (fparg0 != fparg1) {
        temp_16 = arg3 & 1;
        var_2 = arg3 & 2;
        if (temp_16 != 0) {
            func_0034ED88(fparg1 - fparg0);
            var_2 = arg3 & 2;
        }
        if (var_2 != 0) {
            if ((temp_16 ^ 1) == 0) {

            } else {
                goto block_7;
            }
        } else if (temp_16 != 0) {
block_7:
            var_f21 = fparg0 - 1.0f;
        }
        *arg0 |= 0x14;
        *func_003500E0(arg2, (s32) arg1->field_2) = fparg0;
    }
    return var_f21;
}
#endif
