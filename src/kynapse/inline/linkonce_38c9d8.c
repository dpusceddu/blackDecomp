#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00406350[];
const char rodata_00406350[64] __asm__("D_00406350") __attribute__((aligned(8))) = "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity5CCell" "\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049B0D0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_004062E8;
extern s32 func_00370168();

s32 * func_0038C9D8(void) {
    if (D_0049B0D0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_004062E8);
        }
        func_00370168(&D_0049B0D0, D_00406350, &D_0040EBC0);
    }
    return &D_0049B0D0;
}
