#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_001092F8(void *);
extern s32 func_00288A38(s32 *);
extern s32 func_00108668(void *, s32);
extern void * D_0040F4C4;

s32 func_00143FD8(void *arg0, void *arg1) {
    s32 *temp_2_2;
    s32 temp_16;
    s32 temp_2;

    temp_2_2 = func_001092F8(arg0);
    temp_16 = *M2C_FIELD(arg1, s32 **, 0x80);
    func_00288A38(temp_2_2);
    temp_2 = func_00108668(D_0040F4C4, temp_16);
    M2C_FIELD(arg1, s32 **, 0x78) = temp_2_2;
    return temp_2;
}
