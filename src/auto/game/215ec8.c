#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_004924E0;
extern s32 func_0020DD48(void *);
extern s32 func_0020DF30(s32 *);
extern s32 D_004924C0;
extern s32 D_004924D0;
extern s32 func_0020DF90(s32, s32);
extern M2C_UNK D_003FBE10;
extern M2C_UNK D_003FBE20;

s32 func_00215EC8(s32 arg0) {
    s32 *var_16;

    var_16 = &D_004924E0;
    do {
        func_0020DD48(var_16);
        func_0020DF30(var_16);
        var_16 = (s32 *) (((s8 *) var_16) + 0xC);
    } while ((s32) var_16 < (s32) ((s32 *) (((s8 *) &D_004924E0) + 0x18)));
    func_0020DD48(&D_004924C0);
    func_0020DF30(&D_004924C0);
    func_0020DD48(&D_004924D0);
    func_0020DF30(&D_004924D0);
    func_0020DF90(arg0, (s32) &D_003FBE10);
    func_0020DF90(arg0, (s32) &D_003FBE20);
    return 1;
}
