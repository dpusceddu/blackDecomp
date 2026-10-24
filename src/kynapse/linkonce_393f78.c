#include "include_asm.h"

#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0049BDC0;
extern s32 * func_00389100();
extern void func_00370168(void *, char *, void *); /* __rtti_si */
extern M2C_UNK D_0040EBC0;

s32 func_00393F78(void) {
    if (D_0049BDC0 == 0) {
        func_00389100();
        func_00370168(&D_0049BDC0, "Q24Kaim17IDynamicAvoidance\0\0\0\0\0\0bad_alloc", &D_0040EBC0);
    }
    return (s32) &D_0049BDC0;
}
