#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00184DE0(s32 *);

void func_00184D78(s32 *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, f32 *, 8) = 3.4028235e38f;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) == 1) {
        func_00184DE0(arg0);
    }
    M2C_FIELD((void *) M2C_FIELD(arg0, s32 *, 0), s8 *, 0x284) = 1;
}
