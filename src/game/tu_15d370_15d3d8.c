/* Translation unit tu_15d370 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "mod/weapons/shot.h"

extern s32 func_0015D620();

void func_0015D3D8(void *arg0) {
    BkModShotDeactivatePS2(arg0);
}

/* Assembly between the functions: func_0015D3E0 (96 bytes), func_0015D440 (480 bytes), func_0015D620 (304 bytes), func_0015D750 (8 bytes), func_0015D758 (192 bytes), func_0015D818 (56 bytes) */

void func_0015D850(void *arg0, s128 arg1) {
    ((BkModMovingShotPS2*)arg0)->endpoint = arg1;
    func_0015D620();
}
