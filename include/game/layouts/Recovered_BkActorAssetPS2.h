/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_BKACTORASSETPS2_H
#define RECOVERED_BKACTORASSETPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_BkActorAssetPS2 {
    u8 opaque_0[72];
    s32 field_48; /* PS2 +0x48 */
} Recovered_BkActorAssetPS2;
typedef char assert_Recovered_BkActorAssetPS2_48[(((int)&((Recovered_BkActorAssetPS2 *)0)->field_48) == 72) ? 1 : -1];
#endif
