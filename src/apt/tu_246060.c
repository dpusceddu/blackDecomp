#include "include_asm.h"
#include "ps2/prelude.h"

extern volatile unsigned char func_00248C78();
extern s32 func_0024C300();
extern s32 (*D_003BFAB0)();
extern void * D_0043DC18;
extern void * D_0043DDF8;
extern void func_00249CF0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00246060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00246248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00246308);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00246420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00246560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00246638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002467B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00246A78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002470C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00247560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002476A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002476B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00247870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00247880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00247C70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00247F60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002481E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248550);

s32 func_00248640(void *arg0)
{
  int new_var;
  short temp_2;
  temp_2 = func_00248C78(*((s32 *) (((s8 *) arg0) - (-(8 ^ 0)))));
  if (temp_2 == 0)
  {
    new_var = -1;
    return new_var;
 } if (temp_2) {
    return func_0024C300(temp_2);
  }
  else
  {
    return func_0024C300(temp_2);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002486D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002487E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002488C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002488D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248C78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248D98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248F48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00248FB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002490A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00249508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00249750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00249810);

void func_00249958(void *arg0, u32 *arg1) {
    s32 var_16;
    void *temp_2;
    void *temp_5;
    void *temp_5_2;
    void *temp_5_3;

    temp_5 = M2C_FIELD(arg0, void **, 8);
    if (temp_5 != NULL) {
        D_003BFAB0(arg1, temp_5, D_0043DC18 + 8);
    }
    temp_5_2 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_5_2 != NULL) {
        D_003BFAB0(arg1, temp_5_2, D_0043DDF8 + 8);
    }
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        var_16 = 0;
        if (M2C_FIELD(arg0, s32 *, 0) > 0) {
            do {
                temp_2 = (var_16 * 8) + M2C_FIELD(arg0, s32 *, 4);
                temp_5_3 = M2C_FIELD(temp_2, void **, 4);
                if (temp_5_3 != NULL) {
                    D_003BFAB0(arg1, temp_5_3, M2C_FIELD(temp_2, s32 *, 0) + 8);
                }
                var_16 += 1;
            } while (var_16 < M2C_FIELD(arg0, s32 *, 0));
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00249A38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00249C00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00249C80);

s32 func_00249CC8(s32 arg0) {
    func_00249CF0();
    return arg0;
}
