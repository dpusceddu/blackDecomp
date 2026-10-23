#include "auto/prelude.h"

void func_00395890(s32 **arg0, s32 **arg1)
{
  s32 *temp_2;
  s32 *temp_2_2;
  s32 *temp_2_3;
  s32 *temp_3;
  s32 *temp_3_2;
  s32 *temp_3_3;
  s32 *temp_6;
  s32 *temp_7;
  s32 *temp_9;
  s32 var_10;
  s32 var_2;
  s32 var_2_2;
  s32 var_8;
  temp_2 = *arg1;
  temp_6 = *((s32 **) (((s8 *) temp_2) + 0xC));
  temp_9 = *((s32 **) (((s8 *) temp_2) + 4));
  *((s32 **) (((s8 *) temp_2) + 0xC)) = (s32 *) (*((s32 **) (((s8 *) temp_6) + 8)));
  temp_3 = *((s32 **) (((s8 *) temp_6) + 8));
  if (temp_3 != NULL)
  {
    *((s32 **) (((s8 *) temp_3) + 4)) = (s32 *) (*arg1);
  }
  *((s32 **) (((s8 *) temp_6) + 8)) = (s32 *) (*arg1);
  *((s32 **) (((s8 *) (*arg1)) + 4)) = temp_6;
  temp_7 = *arg1;
  temp_2_2 = *((s32 **) (((s8 *) temp_7) + 8));
  var_10 = -1;
  if (temp_2_2 != NULL)
  {
    var_10 = *temp_2_2;
  }
  temp_3_2 = *((s32 **) (((s8 *) temp_7) + 0xC));
  var_2 = -1;
  if (temp_3_2 != NULL)
  {
    var_2 = *temp_3_2;
  }
  M2C_FIELD(temp_7, s32 *, 0) = ((var_10 >= var_2) ? (var_10) : (var_2)) + 1;
  temp_2_3 = *((s32 **) (((s8 *) temp_6) + 0xC));
  var_8 = -1;
  if (temp_2_3 != NULL)
  {
    var_8 = *temp_2_3;
  }
  temp_3_3 = *arg1;
  var_2_2 = -1;
  if (temp_3_3 != NULL)
  {
    var_2_2 = M2C_FIELD(temp_3_3, s32 *, 0);
  }
  *((s32 **) (((s8 *) temp_6) + 4)) = temp_9;
  M2C_FIELD(temp_6, s32 *, 0) = ((var_8 >= var_2_2) ? (var_8) : (var_2_2)) + 1;
  if (temp_9 != NULL)
  {
    if (!((*((s32 **) (((s8 *) temp_9) + 8))) != (*arg1)))
    {
      *((s32 **) (((s8 *) temp_9) + 8)) = temp_6;
    }
    else
    {
      *((s32 **) (((s8 *) temp_9) + 0xC)) = temp_6;
    }
  }
  else
  {
    *arg0 = temp_6;
  }
  *arg1 = temp_6;
}
