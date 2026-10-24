/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_RWREGISTRYPS2_H
#define RECOVERED_RWREGISTRYPS2_H
#include "ps2/prelude.h"

typedef struct Recovered_RwRegistryPS2 {
    u8 opaque_0[20];
    void * field_14; /* PS2 +0x14 */
} Recovered_RwRegistryPS2;
typedef char assert_Recovered_RwRegistryPS2_14[(((int)&((Recovered_RwRegistryPS2 *)0)->field_14) == 20) ? 1 : -1];
#endif
