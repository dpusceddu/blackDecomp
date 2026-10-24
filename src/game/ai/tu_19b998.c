#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_001880D8(void *);
extern s32 func_001880D8();
extern s32 func_00181028();
extern s32 func_00180FE0();
extern s32 func_00193A28();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019B998);

void func_0019BAC0(s32 *arg0) {
    func_00193988();
    func_001880D8(*arg0 + 0x290);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019BAF0);

void func_0019BC28(void **arg0)
{
  unsigned char new_var2;
  void *temp_3;
  s8 *new_var;
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
  new_var2 = func_00181028((*arg0) + 0x140) != 0;
  if (new_var2)
  {
    func_00180FE0((*arg0) + 0x140);
  }
  func_00193A28(arg0, 3, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019BC90);
