#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0036B970();
extern void func_003678A0(); /* WaitSema */
extern s32 D_003D71FC;

s32 func_0036B9C8(s32 arg0) {
    func_0036B970();
    func_003678A0(D_003D71FC);
    return 0;
}
