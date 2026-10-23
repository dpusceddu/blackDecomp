#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
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
