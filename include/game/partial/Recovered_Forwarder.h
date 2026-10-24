/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FORWARDER_H
#define RECOVERED_FORWARDER_H
#include "ps2/prelude.h"

typedef struct Recovered_Forwarder {
    u8 opaque_0[24];
    void * field_18; /* PS2 +0x18 */
} Recovered_Forwarder;
typedef char assert_Recovered_Forwarder_18[(((int)&((Recovered_Forwarder *)0)->field_18) == 24) ? 1 : -1];
#endif
