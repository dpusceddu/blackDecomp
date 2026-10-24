/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CENTITY_H
#define RECOVERED_CENTITY_H
#include "ps2/prelude.h"

typedef struct Recovered_CEntity {
    u8 opaque_0[44];
    void * field_2C; /* PS2 +0x2C */
} Recovered_CEntity;
typedef char assert_Recovered_CEntity_2C[(((int)&((Recovered_CEntity *)0)->field_2C) == 44) ? 1 : -1];
#endif
