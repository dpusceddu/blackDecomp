#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0020DF68(void *, s32, s32);
extern M2C_UNK D_003FAB48;
extern s32 func_0020E630(s32);
extern M2C_UNK D_003FAB50;
extern s32 func_0020E678(s32);
extern M2C_UNK D_003FAB60;
extern s32 func_0020E720();
extern s32 func_0020E6C8();
extern M2C_UNK D_003FAB88;
extern s32 func_0020E768(s32);
extern M2C_UNK D_003FAB90;
extern s32 func_0020E7A8(s32);
extern M2C_UNK D_003FABA0;
extern s32 func_0020E7F8();
extern M2C_UNK D_003FABB0;
extern s32 func_0020E840();
extern M2C_UNK D_003FABC0;
extern s32 func_0020E8C0();
extern M2C_UNK D_003FABD8;
extern s32 func_0020E880();
extern s32 func_0020DCB0(s32 *);
extern s32 D_00491FA0;
extern s32 func_0020DCF8(void *, void *);
extern M2C_UNK D_003FABF0;
extern s32 D_003BE7A8;

s32 func_0020E200(void *arg0) {
    func_0020DF68(arg0, (s32) &D_003FAB48, (s32) func_0020E630);
    func_0020DF68(arg0, (s32) &D_003FAB50, (s32) func_0020E678);
    func_0020DF68(arg0, (s32) &D_003FAB60, (s32) func_0020E720);
    func_0020DF68(arg0, (s32) "Unset480pAndFinish", (s32) func_0020E6C8);
    func_0020DF68(arg0, (s32) &D_003FAB88, (s32) func_0020E768);
    func_0020DF68(arg0, (s32) &D_003FAB90, (s32) func_0020E7A8);
    func_0020DF68(arg0, (s32) &D_003FABA0, (s32) func_0020E7F8);
    func_0020DF68(arg0, (s32) &D_003FABB0, (s32) func_0020E840);
    func_0020DF68(arg0, (s32) &D_003FABC0, (s32) func_0020E8C0);
    func_0020DF68(arg0, (s32) &D_003FABD8, (s32) func_0020E880);
    func_0020DCB0(&D_00491FA0);
    func_0020DCF8(&D_00491FA0, &D_003FABF0);
    D_003BE7A8 = 1;
    return 1;
}
