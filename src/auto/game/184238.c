#include "auto/prelude.h"

extern s32 func_00173610();

void * func_00184238(void *arg0, void *arg1) {
    return (void *) ((func_00173610(arg0 + (((s32) arg1 * 4) + 0x34)) ^ 1) & 0xFF);
}
