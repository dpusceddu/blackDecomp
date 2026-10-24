#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_0021E960();
extern s32 func_00240700();
extern void * D_0043DF40;

s32 func_00234DE0(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 var_4;
    u32 temp_3;

    *(void * *)(sp + 0) = NULL;
    func_0021E960(arg0, 0, arg0, (s32) sp);
    if (*(void * *)(sp + 0) != NULL) {
        temp_3 = M2C_FIELD(*(void * *)(sp + 0), u32 *, 0);
        var_4 = 0;
        if ((u32) ((temp_3 >> 0x19) - 0xC) < 8U) {
            var_4 = ((s32) temp_3 >> 4) & 1;
        }
        if (var_4 & 0xFF) {
            func_00240700(M2C_FIELD(M2C_FIELD(*(void * *)(sp + 0), void **, 0x44), s32 *, 0x48) + 0x24, (s32) *(void * *)(sp + 0));
        }
    }
    return (s32) D_0043DF40;
}

s32 func_00234E58(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 var_4;
    u32 temp_3;

    *(void * *)(sp + 0) = NULL;
    func_0021E960(arg0, 0, arg0, (s32) sp);
    if (*(void * *)(sp + 0) != NULL) {
        temp_3 = M2C_FIELD(*(void * *)(sp + 0), u32 *, 0);
        var_4 = 0;
        if ((u32) ((temp_3 >> 0x19) - 0xC) < 8U) {
            var_4 = ((s32) temp_3 >> 4) & 1;
        }
        if (var_4 & 0xFF) {
            func_00240700(M2C_FIELD(M2C_FIELD(*(void * *)(sp + 0), void **, 0x44), s32 *, 0x48) + 0x24, (s32) *(void * *)(sp + 0));
        }
    }
    return (s32) D_0043DF40;
}
