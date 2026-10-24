#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00291130(void *, void *);
extern s32 func_002918E0(void *, void *);

s32 func_002919F8(s32 arg0, s32 arg1) {
    u8 sp[72] __attribute__((aligned(16)));

    *(s64 *)(sp + 64) = (s64) arg0;
    *(s64 *)(sp + 72) = (s64) arg1;
    func_00291130((sp + 64), sp);
    func_00291130((sp + 72), (sp + 32));
    return func_002918E0(sp, (sp + 32));
}
