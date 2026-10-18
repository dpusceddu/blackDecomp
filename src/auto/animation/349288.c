#include "auto/prelude.h"

extern s32 func_00348E30();
extern s32 func_00349278();

void func_00349288(void *arg0)
{
  int var_16;
  void *temp_2;
  var_16 = 0;
 do { loop_1: temp_2 = func_00348E30(arg0, var_16); } while (0);
  if (temp_2 != NULL)
  {
    var_16 += 1;
    func_00349278(temp_2);
    goto loop_1;
  }
}
