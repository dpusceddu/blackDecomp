#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_001A24B8();
extern s32 func_00173690();

s32 func_001A44F8(s32 arg0) {
    s32 temp_16;
    s32 temp_17;

    temp_16 = arg0;
    func_001A24B8(arg0);
    temp_17 = temp_16 + 0x70;
    func_00173690(temp_17);
    M2C_FIELD(temp_17, f32 *, 4) = -1.0f;
    func_00173690(temp_16 + 0x78);
    return 1;
}
