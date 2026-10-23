#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00209760(void *, s32);
extern void * D_0040F544;
extern M2C_UNK D_003FBC50;
extern M2C_UNK D_003FBC60;
extern M2C_UNK D_003FBC78;
extern M2C_UNK D_003FBC90;
extern M2C_UNK D_003FBCA8;
extern M2C_UNK D_003FBCC0;
extern M2C_UNK D_003FBCD8;
extern M2C_UNK D_003FBCF0;
extern M2C_UNK D_003FBD08;
extern M2C_UNK D_003FBD20;
extern M2C_UNK D_003FBD30;
extern M2C_UNK D_003FBD40;
extern M2C_UNK D_003FBD50;
extern s32 func_0020E0C8(s32, s32);
extern M2C_UNK D_003FBB80;
extern M2C_UNK D_003FBBA0;
extern M2C_UNK D_003FBBB8;
extern M2C_UNK D_003FBBD0;
extern s32 func_0020E020(s32, s32);
extern M2C_UNK D_003FBBE8;
extern s32 func_0020DD48(void *);
extern s32 D_00492460;
extern s32 func_0020DF30(s32 *);
extern s32 D_00492470;
extern s32 D_004924A0;
extern s32 D_004924B0;

s32 func_00215058(s32 arg0) {
    s32 *var_16;

    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBC50);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBC60);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBC78);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBC90);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBCA8);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBCC0);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBCD8);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBCF0);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD08);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD20);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD30);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD40);
    func_00209760((void *) (((s8 *) D_0040F544) + 4), (s32) &D_003FBD50);
    func_0020E0C8(arg0, (s32) &D_003FBB80);
    func_0020E0C8(arg0, (s32) &D_003FBBA0);
    func_0020E0C8(arg0, (s32) &D_003FBBB8);
    func_0020E0C8(arg0, (s32) &D_003FBBD0);
    func_0020E020(arg0, (s32) &D_003FBBE8);
    func_0020DD48(&D_00492460);
    func_0020DF30(&D_00492460);
    var_16 = &D_00492470;
    do {
        func_0020DD48(var_16);
        func_0020DF30(var_16);
        var_16 = (s32 *) (((s8 *) var_16) + 0xC);
    } while ((s32) var_16 < (s32) ((s32 *) (((s8 *) &D_00492470) + 0x30)));
    func_0020DD48(&D_004924A0);
    func_0020DF30(&D_004924A0);
    func_0020DD48(&D_004924B0);
    func_0020DF30(&D_004924B0);
    return 1;
}
