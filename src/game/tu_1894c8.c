#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00188F10(s32 *);
extern f32 func_001891A8(s32 *);
extern s8 * func_00189B90(s32 *, void *);
extern void * func_00188F58(s32 *);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_001894C8(s32 *arg0) {
    if ((func_00188F10(arg0) != 0) && (func_001891A8(arg0) > 30.0f)) {
        func_00189B90(arg0, func_00188F58(arg0));
    }
    return func_00181F48(M2C_FIELD(arg0, s32 *, 0x130) + 0xC80, 0, 0x17, 0.0f, 1.0f);
}
