#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001EF7B0();
extern void * D_0040F510;
extern s32 D_003BE820;
extern s32 D_003BE830;
extern s32 func_0035E750();
extern s32 func_00211D78();
extern s32 D_003BE834;
extern s32 func_0020E068();
extern M2C_UNK D_003FB500;
extern s32 D_003BE83C;
extern s32 D_003BE840;
extern s32 func_0020DF68();
extern M2C_UNK D_003FB528;
extern s32 func_002120F0();
extern M2C_UNK D_003FB540;
extern s32 func_00212140();
extern s32 func_0020DF90();
extern s32 func_0020E0C8();
extern s32 func_002122A0();
extern M2C_UNK D_003FB550;
extern M2C_UNK D_003BE844;
extern M2C_UNK D_003FB560;
extern M2C_UNK D_003BE848;
extern M2C_UNK D_003FB578;
extern s32 func_002122F0();
extern M2C_UNK D_003FB590;
extern s32 func_00212318();
extern M2C_UNK D_003FB5A8;
extern s32 func_00212338();

void func_00211E60(s32 arg0) {
    func_001EF7B0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x38), D_003BE820);
    D_003BE830 = func_0035E750(arg0);
    func_00211D78();
}

void func_00211EB8(s32 arg0) {
    func_001EF7B0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x38), D_003BE820);
    D_003BE834 = func_0035E750(arg0);
    func_00211D78();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00211F10);

void func_00211F70(void) {

}

void func_00211F78(void) {

}

s32 func_00211F80(s32 arg0) {
    func_00212048();
    func_0020E068(arg0, (s32) &D_003FB500, (s32) &D_003BE83C);
    func_0020E068(arg0, (s32) "FEGammaLevel", (s32) &D_003BE840);
    func_0020DF68(arg0, (s32) &D_003FB528, (s32) func_002120F0);
    func_0020DF68(arg0, (s32) &D_003FB540, (s32) func_00212140);
    return 1;
}

s32 func_00212008(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB528);
    func_0020E0C8(arg0, (s32) &D_003FB500);
    return 1;
}

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * D_0040F0E0;
extern s32 D_003BE83C;
extern s32 D_003BE840;

s32 func_00212048(void) {
    s32 temp_2;

    temp_2 = M2C_FIELD(D_0040F0E0, s32 *, 0x20150);
    D_003BE83C = temp_2;
    D_003BE840 = (s32) (M2C_FIELD(D_0040F0E0, f32 *, 0x20158) * 100.0f);
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00212088);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002120F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00212140);

s32 func_00212190(s32 arg0) {
    func_002122A0();
    func_0020E068(arg0, (s32) &D_003FB550, (s32) &D_003BE844);
    func_0020E068(arg0, (s32) &D_003FB560, (s32) &D_003BE848);
    func_0020DF68(arg0, (s32) &D_003FB578, (s32) func_002122F0);
    func_0020DF68(arg0, (s32) &D_003FB590, (s32) func_00212318);
    func_0020DF68(arg0, (s32) &D_003FB5A8, (s32) func_00212338);
    return 1;
}

s32 func_00212230(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FB578);
    func_0020DF90(arg0, (s32) &D_003FB590);
    func_0020DF90(arg0, (s32) &D_003FB5A8);
    func_0020E0C8(arg0, (s32) &D_003FB550);
    func_0020E0C8(arg0, (s32) &D_003FB560);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002122A0);
