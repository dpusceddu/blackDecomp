#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK D_003F6540;

s32 func_00183C80(s32 *arg0, s32 arg1, s32 arg2, f32 fparg0) {
    switch (arg1) {
    case 1:
    case 2:
    case 3:
    case 7:
    case 11:
        if (M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) != M2C_FIELD(arg2, s32 *, 0x3A4)) {
            return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
        }
        return 0;
    case 5:
        if ((M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) != M2C_FIELD(arg2, s32 *, 0x3A4)) && (M2C_FIELD(arg0, s32 *, 0x64) >= 2)) {
            /* Duplicate return node #6. Try simplifying control flow for better match */
            return 0;
        }
        /* Duplicate return node #3. Try simplifying control flow for better match */
        return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
    default:
        return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
    }
}
