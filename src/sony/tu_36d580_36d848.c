#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_00367910(); /* GetOsdConfigParam */
extern void func_00367900(); /* SetOsdConfigParam */

s32 func_0036D848(void) {
    u8 sp[8] __attribute__((aligned(16)));

    func_00367910(sp);
    *(u32 *)(sp + 4) = (*(s32 *)(sp + 0) & 0xFFFF1FFF) | 0x2000;
    func_00367900((sp + 4));
    func_00367910((sp + 4));
    func_00367900(sp);
    return ((*(u32 *)(sp + 4) >> 0xD) & 7) == 0;
}
