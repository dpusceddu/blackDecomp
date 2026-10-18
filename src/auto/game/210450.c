#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * D_0040F4D0;
extern s32 D_003BE7E4;
extern s32 * D_0040F0E0;
extern s32 D_003BE7E8;
extern s32 D_003BE7D8;
extern s32 D_003BE7DC;
extern s32 D_003BE7E0;
extern s32 func_0020E068(void *, s32, s32);
extern M2C_UNK D_003FB1D8;
extern M2C_UNK D_003FB1F0;
extern M2C_UNK D_003FB208;
extern M2C_UNK D_003FB218;
extern M2C_UNK D_003FB228;
extern s32 func_0020DF68(void *, s32, s32);
extern M2C_UNK D_003FB238;
extern s32 func_002107D8();
extern M2C_UNK D_003FB250;
extern s32 func_00210850();
extern M2C_UNK D_003FB268;
extern s32 func_002108C8();
extern M2C_UNK D_003FB278;
extern s32 func_002106B8();
extern M2C_UNK D_003FB288;
extern s32 func_00210748();
extern s32 D_003BE7EC;

s32 func_00210450(void *arg0) {
    void *temp_7;

    temp_7 = D_0040F4D0 + 0x520;
    D_003BE7E4 = (s32) (M2C_FIELD(D_0040F0E0, f32 *, 0x2015C) * 100.0f);
    D_003BE7E8 = (s32) (M2C_FIELD(D_0040F0E0, f32 *, 0x20160) * 100.0f);
    D_003BE7D8 = (s32) M2C_FIELD(temp_7, u8 *, 0xF1);
    D_003BE7DC = (s32) M2C_FIELD(temp_7, u8 *, 0xF2);
    D_003BE7E0 = (s32) M2C_FIELD(D_0040F0E0, u8 *, 0x20168);
    func_0020E068(arg0, (s32) &D_003FB1D8, (s32) &D_003BE7D8);
    func_0020E068(arg0, (s32) &D_003FB1F0, (s32) &D_003BE7DC);
    func_0020E068(arg0, (s32) &D_003FB208, (s32) &D_003BE7E0);
    func_0020E068(arg0, (s32) &D_003FB218, (s32) &D_003BE7E4);
    func_0020E068(arg0, (s32) &D_003FB228, (s32) &D_003BE7E8);
    func_0020DF68(arg0, (s32) &D_003FB238, (s32) func_002107D8);
    func_0020DF68(arg0, (s32) &D_003FB250, (s32) func_00210850);
    func_0020DF68(arg0, (s32) &D_003FB268, (s32) func_002108C8);
    func_0020DF68(arg0, (s32) &D_003FB278, (s32) func_002106B8);
    func_0020DF68(arg0, (s32) &D_003FB288, (s32) func_00210748);
    D_003BE7EC = 0;
    return 1;
}
