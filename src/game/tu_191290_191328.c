#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_0018E458();
extern void func_00191360();

void func_00191328(void *arg0) {
    func_0018E458();
    M2C_FIELD(arg0, s8 *, 0x15) = 0;
    func_00191360(arg0);
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s8 *, 0xD24) = 0;
}
