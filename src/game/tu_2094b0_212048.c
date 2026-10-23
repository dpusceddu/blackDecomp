#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * D_0040F0E0;
extern s32 D_003BE83C;
extern s32 D_003BE840;

s32 func_00212048(void) {
    s32 temp_2;

    temp_2 = M2C_FIELD(D_0040F0E0, s32 *, 0x20150);
    D_003BE83C = temp_2;
    D_003BE840 = (s32) (M2C_FIELD(D_0040F0E0, f32 *, 0x20158) * 100.0f);
    return temp_2;
}
