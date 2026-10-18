#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_0036D518();
extern s32 (*D_003D113C)();
extern s32 func_0036D568();
extern void func_00329710();
extern M2C_UNK D_0045C120;

void func_00328E60(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    func_0036D518();
    if (D_003D113C != NULL) {
        D_003D113C(*(s32 *)(sp + 0));
        func_0036D568();
        return;
    }
    func_00329710(&D_0045C120, sp);
    func_0036D568();
}
