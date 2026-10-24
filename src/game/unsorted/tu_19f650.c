#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193980();
extern s32 func_00187FE0(s32, M2C_UNK);
extern s32 func_001825B0(void *);

void func_0019F650(void **arg0) {
    func_00193980();
    func_00187FE0(*arg0 + 0x290, 2);
    M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), s8 *, 0x30) = 1;
    func_001825B0(*arg0 + 0x810);
}
