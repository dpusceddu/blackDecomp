/* Translation unit kynapse/tu_305538 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern char D_00408630[];
const char rodata_00408630[96] __asm__("D_00408630") __attribute__((aligned(8))) = "CRepulsorDynamicAvoidance" "\000\000\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q34Kaimt8CVarList1ZPQ24Kaim7CEntity9CIterator" "\000\000\000";
extern s32 func_0030D0E0();
extern M2C_UNK D_00455AD0;
extern M2C_UNK func_00305538;
extern M2C_UNK * D_00455BE0;
extern M2C_UNK D_003F07A0;
extern int D_003E0040;
extern void (*D_003C87E0)(void *);

void func_003063A8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_0030D0E0(&D_00455AD0, D_00408630, &func_00305538);
            return;
        }
        D_00455BE0 = &D_003F07A0;
    }
}

void func_00306400(void **arg0, int arg1)
{
    *arg0 = &D_003E0040;
    if (arg1 & 1) D_003C87E0(arg0);
}

void func_00306438(void) {

}

void func_00306440(void) {

}

/* Assembly between the functions: func_00306448 (240 bytes), func_00306538 (336 bytes), func_00306688 (216 bytes) */

void func_00306760(void) {
    func_003063A8(1, 0xFFFF);
}

void func_00306780(void) {
    func_003063A8(0, 0xFFFF);
}
