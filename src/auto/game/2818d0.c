#include "auto/prelude.h"

extern s32 func_00284298(void *arg0);
extern s32 func_00285190(void *arg0);

void func_002818D0(s32 arg0, void *arg1) {
    func_00284298(arg1);
    M2C_FIELD(arg1, u16 *, 0x30) = (u16) (M2C_FIELD(arg1, u16 *, 0x30) & 0xFFFE);
}

void func_00281908(s32 arg0, void *arg1) {
    func_00285190(arg1);
    M2C_FIELD(arg1, u16 *, 0x30) = (u16) (M2C_FIELD(arg1, u16 *, 0x30) & 0xFFFE);
}
