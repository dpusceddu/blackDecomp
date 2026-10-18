#include "auto/prelude.h"

extern s32 func_00193988();
extern s32 func_001825B0();
extern s32 func_00188148();

void func_00197F68(void **arg0) {
    func_00193988();
    func_001825B0(*arg0 + 0x810);
    M2C_FIELD(*arg0, s8 *, 0x849) = 0;
    M2C_FIELD(*arg0, s8 *, 0x845) = 0;
    M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), s8 *, 0x30) = 0;
    M2C_FIELD(*arg0, s8 *, 0x6D8) = 0;
    func_00188148(*arg0 + 0x290, 0U);
}
