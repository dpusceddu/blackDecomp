#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035C6EC();
extern s32 func_003680A0();

void func_001CFCF8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = 0x01000103;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s64 *, 0) = 0x6000006C;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0x6C3C8000;
    func_0035C6EC(arg0 + 0x20, 0, 0x3C0);
    M2C_FIELD(arg0, s32 *, 0x3E8) = 0x01000103;
    M2C_FIELD(arg0, s32 *, 0x3E0) = 0;
    M2C_FIELD(arg0, s32 *, 0x3E4) = 0;
    M2C_FIELD(arg0, s32 *, 0x3EC) = 0x6D3C8001;
    func_0035C6EC(arg0 + 0x3F0, 0, 0x1E0);
    M2C_FIELD(arg0, s32 *, 0x5D8) = 0x01000103;
    M2C_FIELD(arg0, s32 *, 0x5D0) = 0;
    M2C_FIELD(arg0, s32 *, 0x5D4) = 0;
    M2C_FIELD(arg0, s32 *, 0x5DC) = 0x6E3CC002;
    func_0035C6EC(arg0 + 0x5E0, 0, 0xF0);
    func_003680A0(arg0, arg0 + 0x6CF);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1cfcf8", func_001CFDC0);
