#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_00367870(); /* DeleteSema */

void func_00377CD0(void *arg0) {
    func_00367870(M2C_FIELD(arg0, s32 *, 0xC));
}
