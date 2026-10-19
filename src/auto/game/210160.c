#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001F2838(s32, s32, s32);
extern s32 D_0040F51C;
extern void * D_0040F544;
extern s32 func_0020B988(void *, s32);
extern s32 func_0020AFF8(void *);
extern s32 func_00103818(void *);
extern s32 D_0040F0E0;
extern s64 func_00122A48(s32);
extern s32 D_0040F4E8;
extern s32 func_0016C380(s32);
extern void * D_0040F4D0;
extern s32 func_001035D0(s32);

s32 func_00210160(void) {
    func_001F2838(D_0040F51C, 0, M2C_FIELD(D_0040F544, s32 *, 0x3928));
    func_0020B988(D_0040F544, 4);
    func_0020AFF8(D_0040F544);
    return func_00103818((void *) D_0040F0E0);
}

s32 func_002101B8(void) {
    func_001F2838(D_0040F51C, 0, 1);
    func_00122A48(D_0040F4E8);
    func_0020B988(D_0040F544, 4);
    func_0020AFF8(D_0040F544);
    func_0016C380((s32) ((void *) (((s8 *) D_0040F4D0) + 0x3F0)));
    return func_001035D0(D_0040F0E0);
}
