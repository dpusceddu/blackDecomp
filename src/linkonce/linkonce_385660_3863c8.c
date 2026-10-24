#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_003E1E78;
extern s32 func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern void *D_0043DEE4;

void func_003863C8(void *arg0, s32 arg1)
{
  s32 new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
  new_var = arg1;
  do
  {
    *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
 do { func_002486D8(arg0 + 8, 2); } while (0);
  }
  while (0);
  func_00387020(arg0, 0);
  if ((new_var & 1) != 0U)
  {
    func_0024FA98(D_0043DEE4, arg0, 0x20);
  }
}

void func_00386438(void *arg0, s32 arg1)
{
  s32 new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
  new_var = arg1;
  do
  {
    *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
 do { func_002486D8(arg0 + 8, 2); } while (0);
  }
  while (0);
  func_00387020(arg0, 0);
  if ((new_var & 1) != 0U)
  {
    func_0024FA98(D_0043DEE4, arg0, 0x20);
  }
}

void func_003864A8(void *arg0, s32 arg1)
{
  s32 new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
  new_var = arg1;
  do
  {
    *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
 do { func_002486D8(arg0 + 8, 2); } while (0);
  }
  while (0);
  func_00387020(arg0, 0);
  if ((new_var & 1) != 0U)
  {
    func_0024FA98(D_0043DEE4, arg0, 0x20);
  }
}

void func_00386518(void *arg0, s32 arg1)
{
  s32 new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
  new_var = arg1;
  do
  {
    *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
 do { func_002486D8(arg0 + 8, 2); } while (0);
  }
  while (0);
  func_00387020(arg0, 0);
  if ((new_var & 1) != 0U)
  {
    func_0024FA98(D_0043DEE4, arg0, 0x20);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00386588);
