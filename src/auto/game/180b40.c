#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00180AA0(void *, s128, M2C_UNK, f32);

void func_00180B40(void *arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x140);
    func_00180AA0(temp_2 + 0xB30, M2C_FIELD(M2C_FIELD(temp_2, void **, 0x7C), s128 *, 0xA0), 2, M2C_FIELD(temp_2, f32 *, 0));
}
