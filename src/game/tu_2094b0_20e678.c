#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s8 D_0040EAE8;
extern s32 func_001C5B48(void *, s32);
extern s32 * D_0040F4C0;
extern s32 func_00125060(s32);
extern void * D_0040F0E0;
extern s32 func_0020A220(void *);
extern void * D_0040F544;
extern s32 D_003BE7A8;

s32 func_0020E678(s32 arg0) {
    D_0040EAE8 = 0;
    func_001C5B48(D_0040F4C0, 0);
    func_00125060((s32) D_0040F0E0);
    func_0020A220(D_0040F544);
    D_003BE7A8 = 1;
    return 1;
}
