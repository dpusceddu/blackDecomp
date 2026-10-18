#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_003678A0(); /* WaitSema */
extern void func_00367880(); /* SignalSema */

s32 func_0028FA60(void *arg0) {
    s32 temp_17;

    func_003678A0(M2C_FIELD(arg0, s32 *, 0x40));
    temp_17 = (M2C_FIELD(arg0, s32 *, 0x10) << 0x10) + M2C_FIELD(arg0, s32 *, 0x14);
    func_00367880(M2C_FIELD(arg0, s32 *, 0x40));
    return temp_17;
}
