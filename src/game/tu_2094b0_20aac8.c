#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_001092F8();
extern s32 func_00286DB8();
extern s32 func_00108540();
extern s32 D_0040F4C4;

s32 func_0020AAC8(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = func_001092F8(arg0);
    func_00286DB8(temp_2);
    return func_00108540(D_0040F4C4, 7, temp_2, (s32) (s16) arg1);
}
