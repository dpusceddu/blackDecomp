#include "auto/prelude.h"

extern int D_003E0040;
extern void (*D_003C87E0)(void *);

void func_003901C0(void **arg0, int arg1)
{
    *arg0 = &D_003E0040;
    if (arg1 & 1) D_003C87E0(arg0);
}
