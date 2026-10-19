#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK D_003E23C8;
extern s32 func_003870E0(s32 *, s32);
extern s32 func_00387090(s32 *, s32);
extern s32 func_00387100(s32 *, s32);
extern s32 func_00387120(s32 *, s32);
extern s32 func_00387140(s32 *, s32);
extern s32 func_00387180(s32 *);
extern s32 func_00387170(s32 *);
extern s32 func_00387DC0(void *, s32 *);
extern void * D_003BE8E0;
extern s32 func_00387058(s32 *, s32);

s32 * func_00386EC8(s32 *arg0, s32 arg1) {
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E23C8;
    func_003870E0(arg0, arg1);
    func_00387090(arg0, 0);
    func_00387100(arg0, 1);
    func_00387120(arg0, 0);
    func_00387140(arg0, 0);
    M2C_FIELD(arg0, s32 *, 0) |= 0x20;
    if ((arg1 == 0x1C) || (arg1 == 0x2B) || (arg1 == 0x2C)) {
        func_00387180(arg0);
    } else {
        func_00387170(arg0);
        func_00387DC0(D_003BE8E0, arg0);
    }
    func_00387058(arg0, 0);
    return arg0;
}

s32 * func_00386F98(s32 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E23C8;
    func_003870E0(arg0, arg1);
    func_00387090(arg0, 0);
    func_00387100(arg0, 1);
    func_00387120(arg0, 0);
    func_00387140(arg0, 0);
    M2C_FIELD(arg0, s32 *, 0) &= ~0x20;
    func_00387058(arg0, 0);
    func_00387180(arg0);
    return arg0;
}
