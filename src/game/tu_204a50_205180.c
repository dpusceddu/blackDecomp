#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00205D40(void *);
extern s32 func_002058F0(void *);
extern s32 func_00205B68(void *);
extern s32 func_00204D80(void *);
extern s32 func_00205798();

void func_00205180(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 4);
    switch (temp_2) {
    case 1:
        func_00205D40(M2C_FIELD(arg0, void **, 0xC));
        return;
    case 2:
        func_002058F0(M2C_FIELD(arg0, void **, 8));
        return;
    case 3:
        func_00205B68(M2C_FIELD(arg0, void **, 0x10));
        return;
    case 4:
        func_00204D80(M2C_FIELD(arg0, void **, 0x14));
        return;
    case 5:
        func_00205798(M2C_FIELD(arg0, s32 *, 0x18), arg0);
        /* fallthrough */
    default:
        return;
    }
}
