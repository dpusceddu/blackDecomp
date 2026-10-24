#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001D8BC0(s32, s32, s32, s32, f32);
extern void * D_0040F510;

void func_00163580(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x20);
    func_001D8BC0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x34), M2C_FIELD(temp_3, s32 *, 0x20), M2C_FIELD(temp_3, u8 *, 0x29) != 0, M2C_FIELD(temp_3, u8 *, 0x28) != 0, M2C_FIELD(temp_3, f32 *, 0x24));
}
