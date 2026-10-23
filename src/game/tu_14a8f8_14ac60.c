#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0014B8A0(s32 *);

s32 func_0014AC60(s32 *arg0) {
    func_0014B8A0(arg0);
    M2C_FIELD(arg0, s8 *, 0x118) = 0;
    M2C_FIELD(arg0, s32 *, 0xC4) = 5;
    M2C_FIELD(arg0, s8 *, 0x117) = 0;
    return 5;
}
