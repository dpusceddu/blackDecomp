#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 D_0049BE00;
extern s32 func_00393F78();
extern void func_00370168(void *, char *, void *); /* __rtti_si */
extern M2C_UNK D_0049BDC0;

s32 func_003941D0(void) {
    if (D_0049BE00 == 0) {
        func_00393F78();
        func_00370168(&D_0049BE00, "Q24Kaim20CGapDynamicAvoidance", &D_0049BDC0);
    }
    return (s32) &D_0049BE00;
}
