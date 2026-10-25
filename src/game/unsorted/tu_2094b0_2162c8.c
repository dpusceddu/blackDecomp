#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0020DF90();
extern M2C_UNK D_003FBF20;
extern s32 func_0020DD48();
extern M2C_UNK D_004924F8;
extern M2C_UNK D_00492508;
extern M2C_UNK D_00492518;
extern M2C_UNK D_00492528;
extern M2C_UNK D_00492538;
extern M2C_UNK D_00492548;
extern M2C_UNK D_00492558;
extern M2C_UNK D_00492568;
extern s32 func_0020DF30();
extern s32 func_0020DF68();
extern M2C_UNK D_003FC038;
extern s32 func_002169F8();
extern M2C_UNK D_003FC0C8;
extern s32 func_00216B00();
extern s32 D_003BE8B8;
extern s32 func_00122900();
extern s32 D_0040F4E8;
extern void * D_0040F0E0;
extern s32 func_0012FB48();
extern s32 D_0040F4D0;
extern s32 func_0012F880();
extern s32 func_0020DEC8();
extern M2C_UNK D_00492638;
extern s32 func_001087C8();
extern s32 D_0040F4C4;
extern M2C_UNK D_003FC250;

#include "ps2/recovered_types.h"
extern s32 func_0020DF68(void *, s32, s32);
extern M2C_UNK D_003FBF20;
extern s32 func_00216438();
extern s32 func_0020DCB0(s32 *);
extern s32 D_004924F8;
extern s32 D_00492508;
extern s32 D_00492518;
extern s32 D_00492528;
extern s32 D_00492538;
extern s32 D_00492548;
extern s32 D_00492558;
extern s32 D_00492568;
extern s32 func_0020DCF8(void *, void *);

s32 func_002162C8(void *arg0) {
    func_0020DF68(arg0, (s32) &D_003FBF20, (s32) func_00216438);
    func_0020DCB0(&D_004924F8);
    func_0020DCB0(&D_00492508);
    func_0020DCB0(&D_00492518);
    func_0020DCB0(&D_00492528);
    func_0020DCB0(&D_00492538);
    func_0020DCB0(&D_00492548);
    func_0020DCB0(&D_00492558);
    func_0020DCB0(&D_00492568);
    func_0020DCF8(&D_004924F8, "FE_PLAYERNAME");
    func_0020DCF8(&D_00492508, "FE_RANK");
    func_0020DCF8(&D_00492518, "FE_COMPLETIONRESULTS");
    func_0020DCF8(&D_00492528, "FE_GAMETIMERESULTS");
    func_0020DCF8(&D_00492538, "FE_TOTALENEMYCOUNTRESULTS");
    func_0020DCF8(&D_00492548, "FE_HEADSHOTSRESULTS");
    func_0020DCF8(&D_00492558, "FE_TOTALBULLETSFIREDRESULTS");
    func_0020DCF8(&D_00492568, "FE_WEAPONOFCHOICERESULTS");
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2162c8", func_00216438);

s32 func_00216878(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FBF20);
    func_0020DD48((s32) &D_004924F8);
    func_0020DD48((s32) &D_00492508);
    func_0020DD48((s32) &D_00492518);
    func_0020DD48((s32) &D_00492528);
    func_0020DD48((s32) &D_00492538);
    func_0020DD48((s32) &D_00492548);
    func_0020DD48((s32) &D_00492558);
    func_0020DD48((s32) &D_00492568);
    func_0020DF30((s32) &D_004924F8);
    func_0020DF30((s32) &D_00492508);
    func_0020DF30((s32) &D_00492518);
    func_0020DF30((s32) &D_00492528);
    func_0020DF30((s32) &D_00492538);
    func_0020DF30((s32) &D_00492548);
    func_0020DF30((s32) &D_00492558);
    func_0020DF30((s32) &D_00492568);
    return 1;
}

s32 func_002169A0(s32 arg0) {
    func_0020DF68(arg0, (s32) &D_003FC038, (s32) func_002169F8);
    return 1;
}

s32 func_002169D0(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FC038);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2162c8", func_002169F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2162c8", func_00216A90);

s32 func_00216A98(s32 arg0) {
    func_0020DF68(arg0, (s32) &D_003FC0C8, (s32) func_00216B00);
    return 1;
}

s32 func_00216AC8(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FC0C8);
    return 1;
}

void func_00216AF0(s32 arg0) {
    D_003BE8B8 = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2162c8", func_00216B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2162c8", func_00216B58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2162c8", func_00216B68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2162c8", func_00216F08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_2162c8", func_00217010);

void func_00217408(void) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 temp_18;
    s32 temp_20;

    temp_18 = func_00122900(D_0040F4E8, M2C_FIELD(D_0040F0E0, u8 *, 0x2020C));
    *(s32 *)(sp + 0) = 0;
    temp_20 = func_0012FB48(D_0040F4D0 + 0x910, temp_18, M2C_FIELD(D_0040F0E0, s32 *, 0x2014C));
    func_0012F880(D_0040F4D0 + 0x910, temp_18, M2C_FIELD(D_0040F0E0, s32 *, 0x2014C), sp);
    func_0020DEC8(&D_00492638, func_001087C8(D_0040F4C4, &D_003FC250), *(s32 *)(sp + 0), temp_20);
}

#include "ps2/recovered_types.h"
extern s32 func_0020DD48(void *);
extern s32 D_00492588;
extern s32 D_00492598;
extern s32 D_004925A8;
extern s32 D_004925B8;
extern s32 D_004925C8;
extern s32 D_004925D8;
extern s32 D_004925E8;
extern s32 D_004925F8;
extern s32 D_00492608;
extern s32 D_00492618;
extern s32 D_00492628;
extern s32 D_00492638;
extern s32 func_0020DF30(s32 *);

s32 func_002174E0(s32 arg0) {
    func_0020DD48(&D_00492588);
    func_0020DD48(&D_00492598);
    func_0020DD48(&D_004925A8);
    func_0020DD48(&D_004925B8);
    func_0020DD48(&D_004925C8);
    func_0020DD48(&D_004925D8);
    func_0020DD48(&D_004925E8);
    func_0020DD48(&D_004925F8);
    func_0020DD48(&D_00492608);
    func_0020DD48(&D_00492618);
    func_0020DD48(&D_00492628);
    func_0020DD48(&D_00492638);
    func_0020DF30(&D_00492588);
    func_0020DF30(&D_00492598);
    func_0020DF30(&D_004925A8);
    func_0020DF30(&D_004925B8);
    func_0020DF30(&D_004925C8);
    func_0020DF30(&D_004925D8);
    func_0020DF30(&D_004925E8);
    func_0020DF30(&D_004925F8);
    func_0020DF30(&D_00492608);
    func_0020DF30(&D_00492618);
    func_0020DF30(&D_00492628);
    func_0020DF30(&D_00492638);
    return 1;
}
