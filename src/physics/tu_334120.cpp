#include "auto/prelude.h"

extern "C" {
void func_00334120(int, int);
extern void *D_0048F6F0[6];
extern u8 D_003D1368[], D_003D1468[], D_003D1430[], D_003D14A0[], D_003D13A0[];

// Unmatched: 00334120 guarded vector initialization; temporary lifetime and small-data scheduling differ.
// Unmatched: 00334268 shape initialization; method-table access and identity-copy scheduling differ.
// Unmatched: 003342D0 placement wrapper; pointer-wrapper lifetime and inline initialization differ.

/* Register the six inferred shape-kind method tables. */
int func_00334340(void)
{
    D_0048F6F0[0] = 0;
    D_0048F6F0[1] = D_003D1468;
    D_0048F6F0[2] = D_003D1430;
    D_0048F6F0[3] = D_003D14A0;
    D_0048F6F0[4] = D_003D13A0;
    D_0048F6F0[5] = D_003D1368;
    return 1;
}

void func_00334390(void)
{
    func_00334120(1, 65535);
}

void func_003343B0(void)
{
    func_00334120(0, 65535);
}
}
