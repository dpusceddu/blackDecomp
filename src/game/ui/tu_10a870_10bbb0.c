#include "include_asm.h"
#include "ps2/prelude.h"

#include "game/partial/Recovered_FrontendResourceCache.h"
#include "ps2/recovered_types.h"
extern s32 func_0010BAE0(void *, s32 *, s32);
extern void func_001084A8(Recovered_FrontendResourceCache *, s32, s16);
extern Recovered_FrontendResourceCache * D_0040F4C4;

void func_0010BBB0(void *arg0) {
    func_0010BAE0(arg0, NULL, 0);
    func_001084A8(D_0040F4C4, 0xD, 0);
}
