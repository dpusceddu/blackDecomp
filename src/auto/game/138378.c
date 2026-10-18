#include "auto/prelude.h"

extern unsigned char D_004147C0;

void *func_00138378(s32 arg0)
{
  int new_var;
  new_var = arg0 & 0xFFFFFFFFFFFFFFFF;
  return (new_var << 6) + (&D_004147C0);
}
