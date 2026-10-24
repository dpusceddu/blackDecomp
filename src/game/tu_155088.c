#include "ps2/prelude.h"
#include "game/weapons/inventory.h"
extern s32 func_00107D20();
void func_00155088(BkModInventoryPS2 *arg0, s8 arg1)
{
  arg0->count=arg1;
  if (1)
  {
  }
  do { arg0->entries=(void*)func_00107D20(arg1,arg1); } while (0);
}
