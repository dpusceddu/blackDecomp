#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00312C70(s32 *);
extern void func_003676B0(); /* TerminateThread */
extern void func_00367670(); /* DeleteThread */

void func_0031D130(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xC) == 0) {
        func_00312C70(M2C_FIELD(arg0, s32 **, 0x10));
    }
    func_003676B0(M2C_FIELD(arg0, s32 *, 0));
    func_00367670(M2C_FIELD(arg0, s32 *, 0));
}
