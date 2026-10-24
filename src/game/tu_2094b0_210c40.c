#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0020DF90(s32, s32);
extern M2C_UNK D_003FB238;
extern M2C_UNK D_003FB250;
extern M2C_UNK D_003FB268;
extern M2C_UNK D_003FB348;
extern M2C_UNK D_003FB368;
extern M2C_UNK D_003FB380;
extern M2C_UNK D_003FB398;
extern M2C_UNK D_003FB3A8;
extern M2C_UNK D_003FB3B8;
extern s32 func_0020E0C8(s32, s32);
extern M2C_UNK D_003FB1D8;
extern M2C_UNK D_003FB1F0;
extern M2C_UNK D_003FB208;
extern M2C_UNK D_003FB2F8;
extern M2C_UNK D_003FB310;
extern M2C_UNK D_003FB330;
extern s32 func_0020DD48(void *);
extern s32 D_004920D0;
extern s32 func_0020DF30(s32 *);
extern s32 D_004920E0;
extern s32 D_004920F0;

s32 func_00210C40(s32 arg0) {
    s32 *var_16;

    func_0020DF90(arg0, (s32) &D_003FB238);
    func_0020DF90(arg0, (s32) &D_003FB250);
    func_0020DF90(arg0, (s32) &D_003FB268);
    func_0020DF90(arg0, (s32) &D_003FB348);
    func_0020DF90(arg0, (s32) &D_003FB368);
    func_0020DF90(arg0, (s32) &D_003FB380);
    func_0020DF90(arg0, (s32) &D_003FB398);
    func_0020DF90(arg0, (s32) &D_003FB3A8);
    func_0020DF90(arg0, (s32) &D_003FB3B8);
    func_0020E0C8(arg0, (s32) &D_003FB1D8);
    func_0020E0C8(arg0, (s32) &D_003FB1F0);
    func_0020E0C8(arg0, (s32) &D_003FB208);
    func_0020E0C8(arg0, (s32) &D_003FB2F8);
    func_0020E0C8(arg0, (s32) &D_003FB310);
    func_0020E0C8(arg0, (s32) &D_003FB330);
    func_0020DD48(&D_004920D0);
    func_0020DF30(&D_004920D0);
    func_0020DD48(&D_004920E0);
    func_0020DF30(&D_004920E0);
    var_16 = &D_004920F0;
    do {
        func_0020DD48(var_16);
        func_0020DF30(var_16);
        var_16 = (s32 *) (((s8 *) var_16) + 0xC);
    } while ((s32) var_16 < (s32) ((s32 *) (((s8 *) &D_004920F0) + 0xD8)));
    return 1;
}
