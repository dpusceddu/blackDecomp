#include "ps2/prelude.h"

extern char D_00406E48[];
extern char D_00406E58[];
const char rodata_00406E48[16] __asm__("D_00406E48") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000";
const char rodata_00406E58[296] __asm__("D_00406E58") __attribute__((aligned(8))) = "Q24Kaim6CWorld" "\000\000" "Q24Kaimt8CVarList1ZPQ24Kaim7CEntity" "\000\000\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator" "\000\000\000" "Q24Kaimt8CVarList1ZPQ24Kaim5CTeam" "\000\000\000\000\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim5CTeam9CIterator" "\000\000\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity5CCell" "\000\000\000\000\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim5CTeam5CCell" "\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BAA0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_0038EE08(void) {
    if (D_0049BAA0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_00406E48);
        }
        func_00370168(&D_0049BAA0, D_00406E58, &D_0040EBC0);
    }
    return &D_0049BAA0;
}
