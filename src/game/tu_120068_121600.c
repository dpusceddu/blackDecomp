#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0013C950(void *, s32);
extern M2C_UNK * D_0040F4D0;
extern s32 func_001F2838(s32, s32, s32);
extern s32 D_0040F51C;

s32 func_00121600(void) {
    func_0013C950((void *) (((s8 *) D_0040F4D0) + 0x30), 1);
    func_001F2838(D_0040F51C, 0, 5);
    return 1;
}
