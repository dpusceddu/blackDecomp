#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0049BEA0;
extern s32 * func_0038AFB8();
extern void func_00370168(void *, char *, void *); /* __rtti_si */
extern M2C_UNK D_0049AB88;

s32 func_00394BC0(void) {
    if (D_0049BEA0 == 0) {
        func_0038AFB8();
        func_00370168(&D_0049BEA0, "Q24Kaim13CSoundManager", &D_0049AB88);
    }
    return (s32) &D_0049BEA0;
}
