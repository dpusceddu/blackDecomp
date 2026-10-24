#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_003D6340;
extern s32 func_0035C308(void *);
extern s32 func_003566F0(s32);
extern s32 func_0035C470(s32);

s32 func_003554F8(void *arg0, s32 arg1) {
    s32 temp_2;

    if (D_003D6340 == 0) {
        return 0x81018001;
    }
    if (((u32) (M2C_FIELD(arg0, s32 *, 4) - 2) >= 2U) || (M2C_FIELD(arg0, s32 *, 8) != 0)) {
        return 0x81010016;
    }
    temp_2 = func_0035C308(arg0);
    if (temp_2 < 0) {
        return 0x81010017;
    }
    func_003566F0(temp_2);
    return func_0035C470(temp_2);
}
