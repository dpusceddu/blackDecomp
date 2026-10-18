#include "auto/prelude.h"

extern volatile unsigned char func_00248C78();
extern s32 func_0024C300();

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
