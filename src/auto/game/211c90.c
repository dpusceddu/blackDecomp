#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001D5DA8(s32, f32);
extern void * D_0040F510;
extern s32 D_0040F0E0;
extern s32 func_001D5D40(s32, f32);
extern s32 func_00283200(s32, u32);
extern s32 func_00211F10(s32);

s32 func_00211C90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001D5DA8((s32) D_0040F510, M2C_FIELD(D_0040F0E0, f32 *, 0x2015C));
    func_001D5D40((s32) D_0040F510, M2C_FIELD(D_0040F0E0, f32 *, 0x20160));
    return func_00283200((s32) D_0040F510, func_00211F10(M2C_FIELD(D_0040F0E0, s32 *, 0x20154)));
}
