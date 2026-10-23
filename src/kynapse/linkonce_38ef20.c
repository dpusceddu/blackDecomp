#include "auto/prelude.h"

extern char D_00406F90[];
extern char D_00407028[];
const char rodata_00406F90[152] __asm__("D_00406F90") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000" "Q24Kaimt8CVarList1ZPQ24Kaim7CEntity" "\000\000\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator" "\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim5CTeam9CIterator" "\000\000\000\000\000";
const char rodata_00407028[64] __asm__("D_00407028") __attribute__((aligned(8))) = "Q24Kaim5CTeam" "\000\000\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity5CCell" "\000\000\000\000\000\000\000";
extern s32 D_0049BAB0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_0038EF20(void) {
    if (D_0049BAB0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_00406F90);
        }
        func_00370168(&D_0049BAB0, D_00407028, &D_0040EBC0);
    }
    return &D_0049BAB0;
}
