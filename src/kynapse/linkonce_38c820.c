#include "ps2/prelude.h"

extern char D_00406280[];
extern char D_00406290[];
const char rodata_00406280[16] __asm__("D_00406280") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000";
const char rodata_00406290[40] __asm__("D_00406290") __attribute__((aligned(8))) = "Q24Kaim12CTraceResult" "\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049B0B0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_0038C820(void) {
    if (D_0049B0B0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_00406280);
        }
        func_00370168(&D_0049B0B0, D_00406290, &D_0040EBC0);
    }
    return &D_0049B0B0;
}
