#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0049A968;
extern s32 * func_0038BA88();
extern void func_00370168(void *, char *, void *); /* __rtti_si */
extern M2C_UNK D_0049A948;

s32 func_00389500(void) {
    if (D_0049A968 == 0) {
        func_0038BA88();
        func_00370168(&D_0049A968, "Q24Kaim10CGotoAgent\0\0\0\0\0Q24Kaimt10CMetaClass2ZQ24Kaim6CAgentZPFPQ24Kaim6CBrain_PQ24Kaim6CAgent\0\0bad_alloc\0\x01\x02", &D_0049A948);
    }
    return (s32) &D_0049A968;
}
