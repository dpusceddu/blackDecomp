/* Translation unit tu_19a930 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00193988();
extern s32 func_00181028();
extern s32 func_00180FE0();
extern s32 func_001880D8();
extern s32 func_00185F00();
extern s32 func_00193A28();

void func_0019A9C0(void **arg0)
{
  s8 *new_var;
  void *temp_3;
  func_00193988();
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    temp_3 = (*arg0) + 0x140;
    func_00180FE0(temp_3);
  }
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
}

/* Assembly between the functions: func_0019AA20 (240 bytes), func_0019AB10 (264 bytes) */

void func_0019AC18(void **arg0)
{
  void *temp_3;
  void *new_var;
  if (temp_3)
  {
    temp_3 = *arg0;
  }
  else
  {
    temp_3 = *arg0;
  }
  new_var = temp_3 + 0x290;
  if ((M2C_FIELD(temp_3, u8 *, 0x290)) != 0)
  {
    func_001880D8(new_var);
  }
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    func_00180FE0((*arg0) + 0x140);
  }
  if (!((((u8) (*((u8 *) (((s8 *) (*arg0)) + 0xD60)))) >> 4) & 1))
  {
    goto block_9;
  }
  if (func_00185F00((*arg0) + 0x90) != 0)
  {
    func_00193A28(arg0, 0xA, (void *) 0);
    return;
  }
  block_9:
  func_00193A28(arg0, 3, (void *) 0);

}
