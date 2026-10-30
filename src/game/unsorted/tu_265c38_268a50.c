#include "include_asm.h"
#include "ps2/prelude.h"

extern u8 D_0040E597;
extern void func_00268928(void);
extern u8 D_0040E598;
extern u8 D_0040E599;

void func_00268A50(unsigned int arg0)
{
  if (arg0 != D_0040E597)
  {
    D_0040E597 = arg0;
    func_00268928();
  }
}

void func_00268A78(unsigned int arg0)
{
  if (arg0 != D_0040E598)
  {
    D_0040E598 = arg0;
    func_00268928();
  }
}

void func_00268AA0(unsigned int arg0)
{
  if (arg0 != D_0040E599)
  {
    D_0040E599 = arg0;
    func_00268928();
  }
}
