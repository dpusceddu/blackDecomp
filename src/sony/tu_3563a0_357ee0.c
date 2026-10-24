#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_00356508();
extern s32 func_003561C0();
extern s32 func_00356150();

s32 func_00357EE0(s32 arg0, s32 arg1, M2C_UNK *arg2) {
    if ((func_00356508() == 0) || (func_003561C0(arg2) == 0)) {
        return 0x81010016;
    }
    return (func_00356150(arg2) != 0) ? 0 : 0x8101005B;
}
