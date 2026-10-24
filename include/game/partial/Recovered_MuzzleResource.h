/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_MUZZLERESOURCE_H
#define RECOVERED_MUZZLERESOURCE_H
#include "ps2/prelude.h"

typedef struct Recovered_MuzzleResource {
    u8 opaque_0[16];
    void * field_10; /* PS2 +0x10 */
} Recovered_MuzzleResource;
typedef char assert_Recovered_MuzzleResource_10[(((int)&((Recovered_MuzzleResource *)0)->field_10) == 16) ? 1 : -1];
#endif
