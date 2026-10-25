#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001B37C8();
extern s32 D_0040F4D8;
extern s32 func_00165AE0();
extern s32 func_00165BC8();
extern s32 func_00165B98();
extern void func_00169BF0();
extern s32 func_00165BC8(void *, s32);
extern s32 func_00169EB8();

void func_00149AC8(void *arg0) {
    s32 var_16;
    u16 *temp_3;

    var_16 = 0;
    if (M2C_FIELD(arg0, u8 *, 0x1F6) != 0) {
        do {
            temp_3 = (var_16 * 2) + M2C_FIELD(arg0, s32 *, 0x1B0);
            if (*temp_3 != 0xFFFF) {
                func_001B37C8(D_0040F4D8 + 0x33C40, *temp_3);
            }
            var_16 += 1;
        } while (var_16 < (s32) M2C_FIELD(arg0, u8 *, 0x1F6));
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00149B60);

void func_00149BE8(s32 arg0, s32 arg1, s32 arg2)
{
  u8 *temp_7;
  s32 new_var;
  u8 var_2;
  arg1 = arg1;
  arg1 = arg1 * 2;
  temp_7 = arg1 + (M2C_FIELD(arg0, s32 *, 0x1AC));
  var_2 = *temp_7;
  new_var = M2C_FIELD(arg0, s32 *, 0x1AC);
  if (var_2 == 0)
  {
    *temp_7 = 1;
    ;
    *((s8 *) ((arg1 + (M2C_FIELD(arg0, s32 *, 0x1AC))) + 1)) = (s8) arg2;
  }
  return (s32) (arg1 + new_var);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00149C18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00149CA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00149D58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A438);

s32 func_0014A560(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014A6A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014BD58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014CDB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014CE00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014CE68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014D358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DA80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DB90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DC18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DC78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DE58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014DF68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014E018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014EC10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014EC40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014EC90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014F7F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014F838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014F888);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014FDA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_0014FEE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001507E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00150B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00152A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00153448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001534A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001550C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001550F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155B08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155E48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00155F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00156110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00158E88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00161DF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001621A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162600);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001626D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001627D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001628E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162960);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162A60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00162F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001630E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001631B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001634D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001635D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163AB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163B50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163DB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00163FD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001640D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001641A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00164F50);

void func_001650B8(void *arg0, s32 arg1) {
    func_00165AE0();
    func_00165BC8(arg0, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001650F8);

s32 func_00165148(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00165168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00165170);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001651D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00165210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00165268);

s32 func_001652B8(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001652D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001652F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00165330);

s32 func_00165380(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001653A0);

void func_001653F0(void *arg0, s32 arg1) {
    func_00169BF0();
    func_00165BC8(arg0, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_00165430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1448c8_149ac8", func_001656F0);

s32 func_00165A38(void) {
    func_00169EB8();
    return 1;
}
